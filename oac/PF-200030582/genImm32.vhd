library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity genImm32 is
  port (
    instr : in  std_logic_vector(31 downto 0);
    imm32 : out std_logic_vector(31 downto 0)
  );
end entity genImm32;

architecture RTL of genImm32 is
  signal opcode : std_logic_vector(6 downto 0);
  signal funct3 : std_logic_vector(2 downto 0);

begin
  opcode <= instr(6 downto 0);
  funct3 <= instr(14 downto 12);

  process (opcode, instr) begin
    case opcode is
      -- R-Type
      when "0110011" =>	imm32 <= x"00000000";

      -- I-Type
      when "0000011" | "0010011" | "1100111" =>  
        -- SRAI e SRLI
        if funct3 = "101" then 
          imm32 <= std_logic_vector(resize(signed(instr(24 downto 20)), 32));
        else
          imm32 <= std_logic_vector(resize(signed(instr(31 downto 20)), 32));
        end if;

      -- S-Type
      when "0100011" => imm32 <= std_logic_vector(resize(signed(instr(31 downto 25) & instr(11 downto 7)), 32));

      -- SB-Type
      when "1100011" => imm32 <= std_logic_vector(resize(signed(instr(31) & instr(7) & instr(30 downto 25) & instr(11 downto 8) & '0'), 32));

      -- UJ-Type
      when "1101111" => imm32 <= std_logic_vector(resize(signed(instr(31) & instr(19 downto 12) & instr(20) & instr(30 downto 21) & '0'), 32));

      -- U-Type
      when "0110111" | "0010111" => imm32 <= std_logic_vector(resize(signed(instr(31 downto 12)), 32) sll 12);

      -- Unknown
      when others => imm32 <= x"00000000";

    end case;
  end process;
end RTL;