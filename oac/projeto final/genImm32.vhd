library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity genImm32 is
  port (
    instr : in  std_logic_vector(31 downto 0);
    imm32 : out signed (31 downto 0)
  );
end genImm32;

architecture RTL of genImm32 is
  signal opCode : std_logic_vector(6 downto 0);
  signal funct3 : std_logic_vector(14 downto 12);

begin
  opCode <= instr(6 downto 0);
  funct3 <= instr(14 downto 12);

  process (opCode, funct3, instr)
    begin
      -- R_type
      if (opCode = "0110011") then
        imm32 <= resize("0", imm32'length);

      -- I_type*
      elsif (opCode = "0010011" and funct3 = "101" and instr(30) = '1') then
        imm32 <= resize(signed(instr(24 downto 20)), imm32'length);

      -- I_type
      elsif (opCode = "0000011" or opCode = "0010011" or opCode = "1100111") then
        imm32 <= resize(signed(instr(31 downto 20)), imm32'length);

      -- S_type
      elsif (opCode = "0100011") then
        imm32 <= resize(signed(instr(31 downto 25) & instr(11 downto 7)), imm32'length);

      -- SB_type
      elsif (opCode = "1100011") then
        imm32 <= resize(signed(instr(31) & instr(7) & instr(30 downto 25) & instr(11 downto 8) & '0'), imm32'length);

      -- UJ_type
      elsif (opCode = "1101111") then
        imm32 <= resize(signed(instr(31) & instr(19 downto 12) & instr(20) & instr(30 downto 21) & '0'), imm32'length);

      -- U_type  
      elsif (opCode = "0110111" or opCode = "0010111") then
        imm32 <= resize(signed(instr(31 downto 12) & x"000"), imm32'length);

      -- Unknown  
      else
        imm32 <= resize("0", imm32'length);
      end if;
  end process;
end RTL;
