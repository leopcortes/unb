library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity controle_tb is
end controle_tb;

architecture RTL of controle_tb is
  component controle is
    port(
      opcode     : in  std_logic_vector(6 downto 0);
      alu_op     : out std_logic_vector(1 downto 0);
      branch     : out std_logic;
      mem_read   : out std_logic;
      mem_to_reg : out std_logic;
      mem_write  : out std_logic;
      alu_src    : out std_logic;
      reg_write  : out std_logic;
      lui        : out std_logic;
      auipc      : out std_logic;
      jal        : out std_logic;
      jalr       : out std_logic
    );
  end component;

  signal opcode     : std_logic_vector(6 downto 0);
  signal alu_op     : std_logic_vector(1 downto 0);
  signal branch     : std_logic;
  signal mem_read   : std_logic;
  signal mem_to_reg : std_logic;
  signal mem_write  : std_logic;
  signal alu_src    : std_logic;
  signal reg_write  : std_logic;
  signal lui        : std_logic;
  signal auipc      : std_logic;
  signal jal        : std_logic;
  signal jalr       : std_logic;

  begin
    control : controle port map(opcode, alu_op, branch, mem_read, mem_to_reg, mem_write, alu_src, reg_write, lui, auipc, jal, jalr);
    
    process begin
      -- Tipo R
      opcode <= "0110011";
      wait for 1 ns;
      assert alu_op     = '01' report "Erro (Tipo R) - alu_op" severity error;
      assert branch     = "0"  report "Erro (Tipo R) - branch" severity error;
      assert mem_read   = "0"  report "Erro (Tipo R) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (Tipo R) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (Tipo R) - mem_write" severity error;
      assert alu_src    = "0"  report "Erro (Tipo R) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (Tipo R) - reg_write" severity error;
      assert lui        = "0"  report "Erro (Tipo R) - lui" severity error;
      assert auipc      = "0"  report "Erro (Tipo R) - auipc" severity error;
      assert jal        = "0"  report "Erro (Tipo R) - jal" severity error;
      assert jalr       = "0"  report "Erro (Tipo R) - jalr" severity error;
      
      -- Tipo IL
      opcode <= "0000011";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (Tipo IL) - alu_op" severity error;
      assert branch     = "0"  report "Erro (Tipo IL) - branch" severity error;
      assert mem_read   = "1"  report "Erro (Tipo IL) - mem_read" severity error;
      assert mem_to_reg = "1"  report "Erro (Tipo IL) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (Tipo IL) - mem_write" severity error;
      assert alu_src    = "1"  report "Erro (Tipo IL) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (Tipo IL) - reg_write" severity error;
      assert lui        = "0"  report "Erro (Tipo IL) - lui" severity error;
      assert auipc      = "0"  report "Erro (Tipo IL) - auipc" severity error;
      assert jal        = "0"  report "Erro (Tipo IL) - jal" severity error;
      assert jalr       = "0"  report "Erro (Tipo IL) - jalr" severity error;
      
      -- Tipo S
      opcode <= "0100011";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (Tipo S) - alu_op" severity error;
      assert branch     = "0"  report "Erro (Tipo S) - branch" severity error;
      assert mem_read   = "0"  report "Erro (Tipo S) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (Tipo S) - mem_to_reg" severity error;
      assert mem_write  = "1"  report "Erro (Tipo S) - mem_write" severity error;
      assert alu_src    = "1"  report "Erro (Tipo S) - alu_src" severity error;
      assert reg_write  = "0"  report "Erro (Tipo S) - reg_write" severity error;
      assert lui        = "0"  report "Erro (Tipo S) - lui" severity error;
      assert auipc      = "0"  report "Erro (Tipo S) - auipc" severity error;
      assert jal        = "0"  report "Erro (Tipo S) - jal" severity error;
      assert jalr       = "0"  report "Erro (Tipo S) - jalr" severity error;

      -- Tipo B
      opcode <= "1100011";
      wait for 1 ns;
      assert alu_op     = "01" report "Erro (Tipo B) - alu_op" severity error;
      assert branch     = "0"  report "Erro (Tipo B) - branch" severity error;
      assert mem_read   = "0"  report "Erro (Tipo B) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (Tipo B) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (Tipo B) - mem_write" severity error;
      assert alu_src    = "1"  report "Erro (Tipo B) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (Tipo B) - reg_write" severity error;
      assert lui        = "0"  report "Erro (Tipo B) - lui" severity error;
      assert auipc      = "0"  report "Erro (Tipo B) - auipc" severity error;
      assert jal        = "0"  report "Erro (Tipo B) - jal" severity error;
      assert jalr       = "0"  report "Erro (Tipo B) - jalr" severity error;
      
      -- Tipo I
      opcode <= "0010011";
      assert alu_op     = "01" report "Erro (Tipo I) - alu_op" severity error;
      assert branch     = "0"  report "Erro (Tipo I) - branch" severity error;
      assert mem_read   = "0"  report "Erro (Tipo I) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (Tipo I) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (Tipo I) - mem_write" severity error;
      assert alu_src    = "1"  report "Erro (Tipo I) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (Tipo I) - reg_write" severity error;
      assert lui        = "0"  report "Erro (Tipo I) - lui" severity error;
      assert auipc      = "0"  report "Erro (Tipo I) - auipc" severity error;
      assert jal        = "0"  report "Erro (Tipo I) - jal" severity error;
      assert jalr       = "0"  report "Erro (Tipo I) - jalr" severity error;
      
      -- LUI
      opcode <= "0110111";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (LUI) - alu_op" severity error;
      assert branch     = "0"  report "Erro (LUI) - branch" severity error;
      assert mem_read   = "0"  report "Erro (LUI) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (LUI) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (LUI) - mem_write" severity error;
      assert alu_src    = "0"  report "Erro (LUI) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (LUI) - reg_write" severity error;
      assert lui        = "1"  report "Erro (LUI) - lui" severity error;
      assert auipc      = "0"  report "Erro (LUI) - auipc" severity error;
      assert jal        = "0"  report "Erro (LUI) - jal" severity error;
      assert jalr       = "0"  report "Erro (LUI) - jalr" severity error;
      
      -- AUIPC
      opcode <= "0010111";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (AUIPC) - alu_op" severity error;
      assert branch     = "0"  report "Erro (AUIPC) - branch" severity error;
      assert mem_read   = "0"  report "Erro (AUIPC) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (AUIPC) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (AUIPC) - mem_write" severity error;
      assert alu_src    = "0"  report "Erro (AUIPC) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (AUIPC) - reg_write" severity error;
      assert lui        = "0"  report "Erro (AUIPC) - lui" severity error;
      assert auipc      = "1"  report "Erro (AUIPC) - auipc" severity error;
      assert jal        = "0"  report "Erro (AUIPC) - jal" severity error;
      assert jalr       = "0"  report "Erro (AUIPC) - jalr" severity error;
      
      -- JALR
      opcode <= "1100111";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (JALR) - alu_op" severity error;
      assert branch     = "0"  report "Erro (JALR) - branch" severity error;
      assert mem_read   = "0"  report "Erro (JALR) - mem_read" severity error;
      assert mem_to_reg = "0"  report "Erro (JALR) - mem_to_reg" severity error;
      assert mem_write  = "0"  report "Erro (JALR) - mem_write" severity error;
      assert alu_src    = "1"  report "Erro (JALR) - alu_src" severity error;
      assert reg_write  = "1"  report "Erro (JALR) - reg_write" severity error;
      assert lui        = "0"  report "Erro (JALR) - lui" severity error;
      assert auipc      = "0"  report "Erro (JALR) - auipc" severity error;
      assert jal        = "1"  report "Erro (JALR) - jal" severity error;
      assert jalr       = "1"  report "Erro (JALR) - jalr" severity error;
      
      -- JAL
      opcode <= "1101111";
      wait for 1 ns;
      assert alu_op     = "00" report "Erro (JAL) - alu_op" severity error;
      assert branch     = "0  report "Erro (JAL) - branch" severity error;
      assert mem_read   = "0  report "Erro (JAL) - mem_read" severity error;
      assert mem_to_reg = "0  report "Erro (JAL) - mem_to_reg" severity error;
      assert mem_write  = "0  report "Erro (JAL) - mem_write" severity error;
      assert alu_src    = "0  report "Erro (JAL) - alu_src" severity error;
      assert reg_write  = "1  report "Erro (JAL) - reg_write" severity error;
      assert lui        = "0  report "Erro (JAL) - lui" severity error;
      assert auipc      = "0  report "Erro (JAL) - auipc" severity error;
      assert jal        = "1  report "Erro (JAL) - jal" severity error;
      assert jalr       = "0  report "Erro (JAL) - jalr" severity error;
      
      report "Testes do CONTROLE concluidos." severity note;
      wait for 1 ns;

    end process;
end RTL;