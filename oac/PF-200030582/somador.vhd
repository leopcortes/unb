library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.riscv_pkg.all;

entity somador is
  port (
    inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
    s_out    : out std_logic_vector(WSIZE-1 downto 0)
  );
end somador;

architecture RTL of somador is
begin
  s_out <= std_logic_vector(signed(inA) + signed(inB));
end RTL;