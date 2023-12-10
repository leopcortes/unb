library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity somador is
  generic (WSIZE : natural := 32);
  port (
    inA, inB : in  std_logic_vector (WSIZE-1 downto 0);
    m_out    : out std_logic_vector (WSIZE-1 downto 0)
  );
end somador;

architecture RTL of somador is
begin
  m_out <= std_logic_vector(signed(inA) + signed(inB));
end RTL;
