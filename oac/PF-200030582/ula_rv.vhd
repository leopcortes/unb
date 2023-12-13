-- Code your design here
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.riscv_pkg.all;

entity ula_rv is
	port (
    opcode   : in  std_logic_vector(3 downto 0);
    inA, inB : in  std_logic_vector(WSIZE-1 downto 0);
    u_out    : out std_logic_vector(WSIZE-1 downto 0);
    zero     : out std_logic
  );
end ula_rv;

architecture RTL of ula_rv is
  signal result : std_logic_vector(WSIZE-1 downto 0);

begin
	u_out <= result;
  
  process (inA, inB, opcode, result) begin
    if (result = x"00000000") then  
      zero <= '1'; 
    else 
      zero <= '0'; 
    end if;

    case opcode is
    	-- ADD inA, inB
      when "0000" => result <= std_logic_vector(signed(inA) + signed(inB));

      -- SUB inA, inB
      when "0001" => result <= std_logic_vector(signed(inA) - signed(inB));

      -- AND inA, inB
      when "0010" => result <= (inA and inB);

      -- OR inA, inB
      when "0011" => result <= (inA or inB);

      -- XOR inA, inB
      when "0100" => result <= (inA xor inB);

      -- SLL inA, inB
      when "0101" => result <= std_logic_vector(shift_left(unsigned(inA), to_integer(unsigned(inB))));

      -- SRL inA, inB
      when "0110" => result <= std_logic_vector(shift_right(unsigned(inA), to_integer(unsigned(inB))));

      -- SRA inA, inB
      when "0111" => result <= std_logic_vector(shift_right(signed(inA), to_integer(unsigned(inB))));

      -- SLT inA, inB
      when "1000" => if signed(inA) < signed(inB) then result <= x"00000001"; else result <= x"00000000"; end if;

      -- SLTU inA, inB
      when "1001" => if unsigned(inA) < unsigned(inB) then result <= x"00000001"; else result <= x"00000000"; end if;

      -- SGE inA, inB
      when "1010" => if signed(inA) >= signed(inB) then result <= x"00000001"; else result <= x"00000000"; end if;

      -- SGEU inA, inB
      when "1011" => if unsigned(inA) >= unsigned(inB) then result <= x"00000001"; else result <= x"00000000"; end if;

      -- SEQ inA, inB
      when "1100" => if inA = inB then result <= x"00000001"; else result <= x"00000000"; end if;

      -- SNE inA, inB
      when "1101" => if inA /= inB then result <= x"00000001"; else result <= x"00000000"; end if;
			
      -- JAL
			when "1110" => result <= std_logic_vector(resize(unsigned'("0"), 32));
			
      -- JALR
			when "1111" => result <= inA;
			  
			when others => result <= x"00000000";
		end case;
	end process;
end RTL;