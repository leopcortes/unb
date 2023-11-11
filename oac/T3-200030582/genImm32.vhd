use ieee.numeric_std.all;

package i_format is
	type FORMAT_RV is (R_type, I_type, S_type, SB_type, UJ_type, U_type);
end i_format;

component genImm32 is
	port (
		instr : in  std_logic_vector(31 downto 0);
		imm32 : out signed(31 downto 0));
end component genImm32;

architecture a of genImm32 is
  	signal opcode : std_logic_vector(6 downto 0);

begin
	opcode <= instr(6 downto 0);
	funct3 <= instr(14 downto 12);

	with opcode select imm32 <=
		-- R-Type:
		resize("0", 32)
		when x"33",

		-- I-Type:
		resize(signed(instr(31 downto 20)), 32)
		when x"03" | x"13" | x"67",

		-- I-Type*:
		--resize(signed(instr(24 downto 20) & instr(31 downto 25) & '0' & instr(30 downto 25) & instr(11 downto 7)), 32)
		resize(signed(instr(24 downto 20) & (others => '0')), 32)
		when x"13" and funct3 = "101" and instr(30) = '1',

		-- S-Type:
		resize(signed(instr(31 downto 25) & instr(11 downto 7)), 32)
		when x"23",

		-- SB-Type:
		resize(signed(instr(31) & instr(7) & instr(30 downto 25) & instr(11 downto 8) & '0'), 32)
		when x"63",

		-- UJ-Type:
		resize(signed(instr(31) & instr(19 downto 12) & instr(20) & instr(30 downto 21) & '0'), 32)
		when x"37",

		-- U-Type:
		resize(signed(instr(31 downto 12) & x"000"), 32)
		when x"6F",

		-- Unknown:
		resize("0", 32) when others;

end genImm32;