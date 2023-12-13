library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.riscv_pkg.all;

entity pc is
  port ( 
    clk   : in  std_logic;
    pc_in  : in  std_logic_vector(WSIZE-1 downto 0);
    pc_out : out std_logic_vector(WSIZE-1 downto 0) :=  x"00000000"
  );
end pc;

architecture RTL of pc is
begin
  process (clk) is
    begin
      if rising_edge(clk) then
        pc_out <= pc_in;
      end if;
  end process;
end RTL;
