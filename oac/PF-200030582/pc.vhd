library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.riscv_pkg.all;

entity pc is
  port(
    clk   : in  std_logic;
    d_in  : in  std_logic_vector(WSIZE-1 downto 0);
    d_out : out std_logic_vector(WSIZE-1 downto 0)
  );
end pc;

architecture RTL of pc is
  signal pc_value : std_logic_vector(WSIZE-1 downto 0) := x"00000000";

begin
  d_out <= pc_value;
  process (clk)
    begin
      if (rising_edge(clk)) then
        pc_value <= d_in;
      end if;
  end process;
end RTL;
