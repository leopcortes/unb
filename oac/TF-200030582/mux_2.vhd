library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux_2 is
  generic (WSIZE : natural := 32);
  port (
    sel      : in  std_logic;
    inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
    m_out    : out std_logic_vector(WSIZE-1 downto 0)
  );
end entity;

architecture RTL of mux_2 is
begin
  m_out <= inA when (sel = '0') else inB;
end RTL;