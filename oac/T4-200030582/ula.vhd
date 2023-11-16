library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package meu_pack is
    constant WSIZE : natural := 8;
    constant ZERO_K : std_logic_vector(WSIZE-1 downto 0) := (others => '0');
end meu_pack;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.meu_pack.all;
  
entity ulaRV is
	generic(WSIZE : natural := 32);
	port (
      	opcode    : in  std_logic_vector(3 downto 0);       -- Operacao
		A, B      : in  std_logic_vector(WSIZE-1 downto 0); -- Operandos
		Z		  : out std_logic_vector(WSIZE-1 downto 0); -- Saida
		zero	  : out std_logic);							-- Indicacao de zero na saida
end ulaRV;

architecture behavioral of ulaRV is
	signal a32 : std_logic_vector(WSIZE-1 downto 0);
begin
	Z <= a32;
ulaRV: process (A, B, opcode, a32) begin
	if (a32 = x"00000000") then zero <= '1'; else zero <= '0'; end if;
	case opcode is
		-- ADD A, B
		when "0000" => a32 <= std_logic_vector(signed(A) + signed(B));

		-- SUB A, B
		when "0001" => a32 <= std_logic_vector(signed(A) - signed(B));

		-- AND A, B
		when "0010" => a32 <= (A and B);

		-- OR A, B
		when "0011" => a32 <= (A or B);

		-- XOR A, B
		when "0100" => a32 <= (A xor B);

		-- SLL A, B
		when "0101" => a32 <= std_logic_vector(shift_left(unsigned(A), to_integer(unsigned(B))));

		-- SRL A, B
		when "0110" => a32 <= std_logic_vector(shift_right(unsigned(A), to_integer(unsigned(B))));

		-- SRA A, B
		when "0111" => a32 <= std_logic_vector(shift_right(signed(A), to_integer(unsigned(B))));

		-- SLT A, B
		when "1000" => a32 <= x"00000001" when (signed(A) < signed(B)) else x"00000000";

		-- SLTU A, B
		when "1001" => a32 <= x"00000001" when (unsigned(A) < unsigned(B)) else x"00000000";

		-- SGE A, B
		when "1010" => a32 <= x"00000001" when (signed(A) >= signed(B)) else x"00000000";

		-- SGEU A, B
		when "1011" => a32 <= x"00000001" when (unsigned(A) >= unsigned(B)) else x"00000000";

		-- SEQ A, B
		when "1100" => a32 <= x"00000001" when (A = B) else x"00000000";

		-- SNE A, B
		when "1101" => a32 <= x"00000001" when (A /= B) else x"00000000";

		-- Unknown
		when others => a32 <= std_logic_vector(resize(signed(ZERO_K), 32));
  	end case;
    
end process;
end behavioral;