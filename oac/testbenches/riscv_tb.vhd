library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use std.textio.all;

entity riscv_tb is
end riscv_tb;

architecture RTL of riscv_tb is
  component rv_uniciclo is
    port (
      clock : IN std_logic
    );
    end component rv_uniciclo;
    
  signal clock : std_logic := '0';

begin
  risc : rv_uniciclo port map(
    clock => clock
  );

  process begin
    clock <= '1'; 

    report "Testes do RISCV concluidos." severity note;
    wait for 1 ns;

  end process;
end architecture RTL;