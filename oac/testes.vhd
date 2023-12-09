-- Autor: Gabriel da Silva Corvino Nogueira
-- Email: gab.nog94@gmail.com
-- Matricula: 180113330
-- Descricao: ULA RISC-V
-- Language Syntax: VHDL 1076-2008

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity ulaRV is
	generic (WSIZE : natural := 32);
	port (
		opcode : in  std_logic_vector(3 downto 0);
		A, B   : in  std_logic_vector(WSIZE-1 downto 0);
		Z      : out std_logic_vector(WSIZE-1 downto 0);
		zero   : out std_logic
	);
end ulaRV;

architecture rtl of ulaRV is
  	signal result : std_logic_vector(31 downto 0);
begin
	Z <= result;
	proc_ula :
	process (A, B, opcode, result)
	begin
		if(result = x"00000000") then
			zero <= '1';
		else
			zero <= '0';
		end if;
		case opcode is
			when "0000"   => result <= std_logic_vector(signed(A) + signed(B));
			when "0001"   => result <= std_logic_vector(signed(A) - signed(B));
			when "0010"   => result <= A and B;
			when "0011"   => result <= A or B;
			when "0100"   => result <= A xor B;
			when "0101"   => result <= std_logic_vector(shift_left(signed(A), to_integer(unsigned(B(4 downto 0)))));
			when "0110"   => result <= std_logic_vector(shift_right(unsigned(A), to_integer(unsigned(B(4 downto 0)))));
			when "0111"   => result <= std_logic_vector(shift_right(signed(A), to_integer(unsigned(B(4 downto 0)))));
			when "1000" =>
				if signed(A) < signed(B) then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when "1001" =>
				if unsigned(A) < unsigned(B) then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when "1010" =>
				if signed(A) >= signed(B) then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when "1011" =>
				if unsigned(A) >= unsigned(B) then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when "1100" =>
				if A = B then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when "1101" =>
				if A /= B then
					result <= x"00000001";
				else
					result <= x"00000000";
				end if;
			when others => result <= x"00000000";
		end case;
	end process;

end architecture rtl;