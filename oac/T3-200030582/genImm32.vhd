library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity genImm32 is
  port (
    instr : in  std_logic_vector(31 downto 0); -- Entrada
    imm32 : out signed(31 downto 0) -- Saida
  );
end genImm32;

architecture a of genImm32 is
  signal opcode : std_logic_vector(6 downto 0);
  signal funct3 : std_logic_vector(14 downto 12);

begin
  opcode <= instr(6 downto 0);
  funct3 <= instr(14 downto 12);

  process (opcode, funct3, instr)
  begin
  	-- R_type
    if (opcode = "0110011") then
      imm32 <= resize("0", 32);
    
    -- I_type*
    elsif (opcode = "0010011" and funct3 = "101" and instr(30) = '1') then
      imm32 <= resize(signed(instr(24 downto 20)), 32);
    
    -- I_type
    elsif (opcode = "0000011" or opcode = "0010011" or opcode = "1100111") then
      imm32 <= resize(signed(instr(31 downto 20)), 32);
    
    -- S_type
    elsif (opcode = "0100011") then
      imm32 <= resize(signed(instr(31 downto 25) & instr(11 downto 7)), 32);
    
    -- SB_type
    elsif (opcode = "1100011") then
      imm32 <= resize(signed(instr(31) & instr(7) & instr(30 downto 25) & instr(11 downto 8) & '0'), 32);
    
    -- UJ_type
    elsif (opcode = "1101111") then
      imm32 <= resize(signed(instr(31) & instr(19 downto 12) & instr(20) & instr(30 downto 21) & '0'), 32);
    
    -- U_type  
    elsif (opcode = "0110111") then
      imm32 <= resize(signed(instr(31 downto 12) & x"000"), 32);
    
    -- Unknown  
    else
      imm32 <= resize("0", 32);
    end if;
    
  end process;
end architecture a;
