library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity genImm32_tb is
end entity genImm32_tb;

architecture a of genImm32_tb is
  component genImm32 is
    port (
      instr : in  std_logic_vector(31 downto 0); -- Entrada
      imm32 : out signed(31 downto 0)); -- Saida
  end component genImm32;

  signal instr_in  : std_logic_vector(31 downto 0); -- Entrada
  signal imm32_out : signed(31 downto 0); -- Saida

begin
  gen : genImm32 port map(instr_in, imm32_out);

  process
  begin
    -- Teste 1: 0x000002b3 -> 0x00000000
    instr_in <= x"000002b3";
    wait for 1 ns;
    assert(imm32_out = x"00000000") report "Erro no Teste 1" severity error;

    -- Teste 2: 0x01002283 -> 0x00000010
    instr_in <= x"01002283";
    wait for 1 ns;
    assert(imm32_out = x"00000010") report "Erro no Teste 2" severity error;

    -- Teste 3: 0xF9C00313 -> 0xFFFFFF9C
    instr_in <= x"f9c00313";
    wait for 1 ns;
    assert(imm32_out = x"FFFFFF9C") report "Erro no Teste 3" severity error;

    -- Teste 4: 0xFFF2C293 -> 0xFFFFFFFF
    instr_in <= x"fff2c293";
    wait for 1 ns;
    assert(imm32_out = x"FFFFFFFF") report "Erro no Teste 4" severity error;

    -- Teste 5: 0x16200313 -> 0x00000162
    instr_in <= x"16200313";
    wait for 1 ns;
    assert(imm32_out = x"00000162") report "Erro no Teste 5" severity error;

    -- Teste 6: 0x01800067 -> 0x00000018
    instr_in <= x"01800067";
    wait for 1 ns;
    assert(imm32_out = x"00000018") report "Erro no Teste 6" severity error;

    -- Teste 7: 0x40A3D313 -> 0x0000000A
	instr_in <= x"40a3d313";
  	wait for 1 ns;
    assert(imm32_out = x"0000000A") report "Erro no Teste 7" severity error;

    -- Teste 8: 0x00002437 -> 0x00002000
    instr_in <= x"00002437";
    wait for 1 ns;
    assert(imm32_out = x"00002000") report "Erro no Teste 7" severity error;

    -- Teste 9: 0x02542E23 -> 0x0000003C
    instr_in <= x"02542e23";
    wait for 1 ns;
    assert(imm32_out = x"0000003C") report "Erro no Teste 8" severity error;

    -- Teste 10: 0xFE5290E3 -> 0xFFFFFFE0
    instr_in <= x"fe5290e3";
    wait for 1 ns;
    assert(imm32_out = x"FFFFFFE0") report "Erro no Teste 9" severity error;

    -- Teste 11: 0x00C000EF -> 0x0000000C
    instr_in <= x"00c000ef";
    wait for 2 ns;
    assert(imm32_out = x"0000000C") report "Erro no Teste 10" severity error;

    assert false report "Testes concluidos com sucesso." severity note;

    wait;

  end process;
end a;