library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux_2_5bits is
  port (
    sel      : in  std_logic;
    inA, inB : in  std_logic_vector(4 downto 0);
    m_out    : out std_logic_vector(4 downto 0)
  );
end mux_2_5bits;

architecture RTL of mux_2_5bits is
begin
  m_out <= inA when (sel = '0') else inB;
end RTL;