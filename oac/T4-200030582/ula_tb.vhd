LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all; 

entity ula_tb is
end ula_tb; 

architecture tb_arch of ula_tb is
    component ulaRV is
        generic(WSIZE : natural := 32);
        port (
            opcode    : in  std_logic_vector(3 downto 0);       -- Operacao
            A, B      : in  std_logic_vector(WSIZE-1 downto 0); -- Operandos
            Z		  : out std_logic_vector(WSIZE-1 downto 0); -- Saida
            zero	  : out std_logic);							-- Indicacao de zero na saida
    end component ulaRV;

    signal A_in: std_logic_vector(31 downto 0);
    signal B_in: std_logic_vector(31 downto 0);
    signal Z_out: std_logic_vector(31 downto 0);
    signal opcode_in: std_logic_vector(3 downto 0);
    signal zero_out: std_logic;

begin
  	DUT: ulaRV port map(A => A_in, B => B_in, Z => Z_out, opcode => opcode_in, zero => zero_out);

process begin
    report "* Inicio da simulacao *"; -- Incio dos testes
    
    -- Teste 0: 1 + FFFFFFFF = 0
    A_in <= x"00000001";
    B_in <= x"ffffffff";
    opcode_in <= "0000";
    wait for 1 ns;
    assert(Z_out= x"00000000") report "Erro no Teste 0 (ADD)" severity error;

	-- Teste 1: 1 - 2 = FFFFFFFF
    A_in <= x"00000001";
    B_in <= x"00000002";
    opcode_in <= "0001";
    wait for 1 ns;
    assert(Z_out= x"ffffffff") report "Erro no Teste 1 (SUB)" severity error;

	-- Teste 2: 1000 & FFFFFFFF = 1000
    A_in <= x"00001000";
    B_in <= x"ffffffff";
    opcode_in <= "0010";
    wait for 1 ns;
    assert(Z_out= x"00001000") report "Erro no Teste 2 (AND)" severity error;   

	-- Teste 3: 1 | FFFFFFFE = FFFFFFFF
    A_in <= x"00000001";
    B_in <= x"fffffffe";
    opcode_in <= "0011";
    wait for 1 ns;
    assert(Z_out= x"ffffffff") report "Erro no Teste 3 (OR)" severity error;

	-- Teste 4: FFFFFFFF ^ A1B2C3D4 = 5E4D3C2B
    A_in <= x"ffffffff";
    B_in <= x"a1b2c3d4";
    opcode_in <= "0100";
    wait for 1 ns;
    assert(Z_out= x"5e4d3c2b") report "Erro no Teste 4 (XOR)" severity error;

	-- Teste 5: FF << 8 = FF00
    A_in <= x"000000ff";
    B_in <= x"00000008";
    opcode_in <= "0101";
    wait for 1 ns;
    assert(Z_out= x"0000ff00") report "Erro no Teste 5 (SLL)" severity error;

	-- Teste 6: FF00 >> 8 = FF
    A_in <= x"0000ff00";
    B_in <= x"00000008";
    opcode_in <= "0110";
    wait for 1 ns;
    assert(Z_out= x"000000ff") report "Erro no Teste 6 (SRL)" severity error;

	-- Teste 7: FF000000 >> 8 = FFFF0000
    A_in <= x"ff000000";
    B_in <= x"00000008";
    opcode_in <= "0111";
    wait for 1 ns;
    assert(Z_out= x"ffff0000") report "Erro no Teste 7 (SRA)" severity error;

	-- Teste 8: 1 < FFFFFFFF = 0
    A_in <= x"00000001";
    B_in <= x"ffffffff";
    opcode_in <= "1000";
    wait for 1 ns;
    assert(Z_out= x"00000000") report "Erro no Teste 8 (SLT)" severity error;

	-- Teste 9: 1 < FFFFFFFF = 1
    A_in <= x"00000001";
    B_in <= x"ffffffff";
    opcode_in <= "1001";
    wait for 1 ns;
    assert(Z_out= x"00000001") report "Erro no Teste 9 (SLTU)" severity error;

	-- Teste 10: 1 >= 1 = 1
  	A_in <= x"00000001";
    B_in <= x"00000001";
    opcode_in <= "1010";
    wait for 1 ns;
    assert(Z_out= x"00000001") report "Erro no Teste 10 (SGE)" severity error;

	-- Teste 11: 1 >= FFFFFFFF = 0
    A_in <= x"00000001";
    B_in <= x"ffffffff";
    opcode_in <= "1011";
    wait for 1 ns;
    assert(Z_out= x"00000000") report "Erro no Teste 11 (SGEU)" severity error;

	-- Teste 12: FFFFFFFF == FFFFFFFF = 1
    A_in <= x"ffffffff";
    B_in <= x"ffffffff";
    opcode_in <= "1100";
    wait for 1 ns;
    assert(Z_out= x"00000001") report "Erro no Teste 12 (SEQ)" severity error;

	-- Teste 13: 1 != FFFFFFFF = 1
    A_in <= x"00000001";
    B_in <= x"ffffffff";
    opcode_in <= "1101";
  	wait for 1 ns;
    assert(Z_out= x"00000001") report "Erro no Teste 13 (SNE)" severity error;

    assert false report "* Fim da simulacao *" severity note; -- Fim dos testes
    wait;
    
end process;
end tb_arch;