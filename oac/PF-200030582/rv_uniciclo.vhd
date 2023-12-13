library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;	
use work.riscv_pkg.all;

entity rv_uniciclo is
  port(
    clk : in std_logic
  );
end entity rv_uniciclo;

architecture RTL of rv_uniciclo is
  -- Clock
  signal aux_clk : std_logic;

  -- Program Counter (PC)
  signal pc_in  : std_logic_vector(WSIZE-1 downto 0);
  signal pc_out : std_logic_vector(WSIZE-1 downto 0); -- aux_output_pc

  -- Memória de Instruções (ROM)
  alias  rom_address : std_logic_vector(IMEM_ADDR-1 downto 0) is pc_out(9 downto 2);
  signal instruction : std_logic_vector(WSIZE-1 downto 0);

  -- Gerador de Imediatos
  signal imm32 : std_logic_vector(WSIZE-1 downto 0);

  -- Instrucoes
  signal data   : std_logic_vector(WSIZE-1 downto 0) := (others => '0');
  signal opcode : std_logic_vector(6 downto 0) := (others => '0');
  signal funct3 : std_logic_vector(2 downto 0) := (others => '0');
  signal funct7 : std_logic;

  -- Controle
  signal branch     : std_logic;
  signal mem_read   : std_logic;
  signal mem_to_reg : std_logic;
  signal alu_op     : std_logic_vector(2 downto 0);
  signal mem_write  : std_logic;
  signal alu_src    : std_logic;
  signal reg_write  : std_logic;
  signal is_lui     : std_logic;
  signal is_auipc   : std_logic;
  signal is_jal     : std_logic;
  signal is_jalr    : std_logic;

  -- Banco de Registradores
  signal rs1, rs2, rd : std_logic_vector(4 downto 0) := (others => '0');
  signal ro1, ro2     : std_logic_vector(WSIZE-1 downto 0) := (others => '0');

  -- Unidade Logica Aritmetica (ULA)
  signal ula_opcode : std_logic_vector(3 downto 0);
  signal inB_ula    : std_logic_vector(WSIZE-1 downto 0);
  signal saida_ula  : std_logic_vector(WSIZE-1 downto 0);
  signal zero       : std_logic;

  -- Memoria de Dados (RAM)
  alias  ram_address : std_logic_vector(IMEM_ADDR-1 downto 0) is saida_ula(9 downto 2);
  alias  ram_datain  : std_logic_vector is ro2;
  signal ram_dataout : std_logic_vector(WSIZE-1 downto 0);

  -- Branch
  signal escolhe_pc : std_logic;

  -- Somadores
  signal soma_pc_4   : std_logic_vector(WSIZE-1 downto 0); -- PC + 4
  signal soma_pc_imm : std_logic_vector(WSIZE-1 downto 0); -- PC + Imm

  -- Multiplexadores 
  signal pc_somado        : std_logic_vector(WSIZE-1 downto 0); -- PC
  signal select_rs1_final : std_logic_vector(4 downto 0); -- LUI
  signal mux_ram_out      : std_logic_vector(WSIZE-1 downto 0); -- RAM
  signal mux_auipc_out    : std_logic_vector(WSIZE-1 downto 0); -- AUIPC

begin
  ipc : pc port map(aux_clk, pc_in, pc_out);

  mi : rom_rv port map(rom_address, instruction);

  opcode <= instruction(6 downto 0);
  rs1    <= instruction(19 downto 15);
  rs2    <= instruction(24 downto 20);
  rd     <= instruction(11 downto 7);
  funct3 <= instruction(14 downto 12);
  funct7 <= instruction(30);

  escolhe_pc <= branch and zero;

  somador_pc_4 : somador port map(pc_out, x"00000004", soma_pc_4);
  somador_pc_imm : somador port map(pc_out, imm32, soma_pc_imm);

  mux_somadores : mux_2 port map(escolhe_pc, soma_pc_4, soma_pc_imm, pc_somado);

  genimm : genImm32 port map(instruction, imm32);

  ctrl : controle port map(opcode, branch, mem_read, mem_to_reg, alu_op, mem_write, alu_src, reg_write, is_lui, is_auipc, is_jal, is_jalr);

  bregs : XREGS port map(aux_clk, reg_write, select_rs1_final, rs2, rd, data, ro1, ro2);

  mux_ula : mux_2 port map(alu_src, ro2, imm32, inB_ula);

  ctrl_ula : controle_ula port map(alu_op, funct3, funct7, ula_opcode);

  ula : ula_rv port map(ula_opcode, ro1, inB_ula, saida_ula, zero);

  md : ram_rv port map(aux_clk, mem_write, ram_address, ram_datain, ram_dataout);

  mux_ram   : mux_2 port map(mem_to_reg, saida_ula, ram_dataout, mux_ram_out);
  mux_lui   : mux_2_5bits port map(is_lui, rs1, "00000", select_rs1_final);
  mux_auipc : mux_2 port map(is_auipc, mux_ram_out, soma_pc_imm, mux_auipc_out);
  mux_jal   : mux_2 port map(is_jal, mux_auipc_out, soma_pc_4, data);
  mux_jalr  : mux_2 port map(is_jalr, pc_somado, saida_ula, pc_in);
    
  process begin
    aux_clk <= '0';
    wait for 1 ns;
    aux_clk <= '1';
    wait for 1 ns;
  end process;
  
end RTL;