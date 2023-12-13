library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.riscv_pkg.all;

entity XREGS is
  port (
    clk, wren    : in  std_logic;
    rs1, rs2, rd : in  std_logic_vector(4 downto 0);
    data         : in  std_logic_vector(WSIZE-1 downto 0);
    ro1, ro2     : out std_logic_vector(WSIZE-1 downto 0)
  );
end XREGS;

architecture RTL of XREGS is
  type breg is array(0 to 31) of std_logic_vector(WSIZE-1 downto 0);
  signal regs : breg := (others => x"00000000");

begin
	process (clk) begin
    if rising_edge(clk) and (wren = '1') and (rd /= "00000") then
      regs(to_integer(unsigned(rd))) <= data;
    end if;
    
    ro1 <= regs(to_integer(unsigned(rs1)));
    ro2 <= regs(to_integer(unsigned(rs2)));
  end process;
end RTL;