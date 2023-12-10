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

architecture RTL of ulaRV is
  signal result : std_logic_vector(31 downto 0);

begin
  Z <= result;
  ulaRV : process (A, B, opcode, result) begin
    if (result = x"00000000") then  
      zero <= '1'; 
    else 
      zero <= '0'; 
    end if;

    case opcode is
      -- ADD A, B
      when "0000" => result <= std_logic_vector(signed(A) + signed(B));

      -- SUB A, B
      when "0001" => result <= std_logic_vector(signed(A) - signed(B));

      -- AND A, B
      when "0010" => result <= (A and B);

      -- OR A, B
      when "0011" => result <= (A or B);

      -- XOR A, B
      when "0100" => result <= (A xor B);

      -- SLL A, B
      when "0101" => result <= std_logic_vector(shift_left(unsigned(A), to_integer(unsigned(B))));

      -- SRL A, B
      when "0110" => result <= std_logic_vector(shift_right(unsigned(A), to_integer(unsigned(B))));

      -- SRA A, B
      when "0111" => result <= std_logic_vector(shift_right(signed(A), to_integer(unsigned(B))));

      -- SLT A, B
      when "1000" =>
        if signed(A) < signed(B) then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- SLTU A, B
      when "1001" =>
        if unsigned(A) < unsigned(B) then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- SGE A, B
      when "1010" =>
        if signed(A) >= signed(B) then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- SGEU A, B
      when "1011" =>
        if unsigned(A) >= unsigned(B) then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- SEQ A, B
      when "1100" =>
        if A = B then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- SNE A, B
      when "1101" =>
        if A /= B then
          result <= x"00000001";
        else
          result <= x"00000000";
        end if;

      -- Unknown
      when others => result <= x"00000000";
      
    end case;
  end process;
end RTL;
