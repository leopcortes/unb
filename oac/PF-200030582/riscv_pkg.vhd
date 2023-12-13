library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package riscv_pkg is
  constant WSIZE     : natural := 32;
  constant IMEM_ADDR : integer := 8;

  component rv_uniciclo is
    port (
      clk : in std_logic
    );
  end component;

  component pc is
    port (
      clk   : in  std_logic;
      pc_in  : in  std_logic_vector(WSIZE-1 downto 0);
      pc_out : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;

  component mux_2 is
    port (
      sel      : in  std_logic;
      inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
      m_out    : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;
  
  component mux_2_5bits is
    port (
      sel      : in  std_logic;
      inA, inB : in  std_logic_vector(4 downto 0);
      m_out    : out std_logic_vector(4 downto 0)
    );
  end component;  

  component somador is
    port (
      inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
      s_out    : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;

  component rom_rv is
    port (
      address : in  std_logic_vector(7 downto 0);
      dataout : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;

  component ram_rv is
    port (
      clk     : in  std_logic;
      wren    : in  std_logic;
      address : in  std_logic_vector;
      datain  : in  std_logic_vector;
      dataout : out std_logic_vector
    );
  end component;

  component ula_rv is
    port (
      opcode   : in  std_logic_vector(3 downto 0);
      inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
      u_out    : out std_logic_vector(WSIZE-1 downto 0);
      zero     : out std_logic
    );
  end component;

  component XREGS is
    port (
      clk, wren    : in  std_logic;
      rs1, rs2, rd : in  std_logic_vector(4 downto 0);
      data         : in  std_logic_vector(WSIZE-1 downto 0);
      ro1, ro2     : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;

  component controle is
    port (
      opcode     : in  std_logic_vector(6 downto 0);
      branch     : out std_logic;
      mem_read   : out std_logic;
      mem_to_reg : out std_logic;
      alu_op     : out std_logic_vector(2 downto 0);
      mem_write  : out std_logic;
      alu_src    : out std_logic;
      reg_write  : out std_logic;
      is_lui     : out std_logic;
      is_auipc   : out std_logic;
      is_jal     : out std_logic;
      is_jalr    : out std_logic
    );
  end component;

  component controle_ula is
    port (
      alu_op    : in  std_logic_vector(2 downto 0);
      funct3    : in  std_logic_vector(2 downto 0);
      funct7    : in  std_logic;
      opcode    : out std_logic_vector(3 downto 0)
    );
  end component;

  component genImm32 is
    port (
      instr : in  std_logic_vector(WSIZE-1 downto 0);
      imm32 : out std_logic_vector(WSIZE-1 downto 0)
    );
  end component;

end riscv_pkg;
