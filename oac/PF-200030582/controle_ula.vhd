library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;	
use work.riscv_pkg.all;
	
entity controle_ula is
  port(
    alu_op : in  std_logic_vector(2 downto 0);
    funct3 : in  std_logic_vector(2 downto 0);
    funct7 : in  std_logic;
    opcode : out std_logic_vector(3 downto 0)
  );
end entity controle_ula;

architecture RTL of controle_ula is
begin
  process (alu_op, funct3, funct7) begin
    case alu_op is
      -- ADD (SW, LW, LUI, AUIPC)
      when "000" => opcode <= "0000";         
      
      -- Branch
      when "001" =>
        -- BEQ (SNE)
        if funct3 = "000" then opcode <= "1101"; end if;
        
        -- BNE (SEQ)
        if funct3 = "001" then opcode <= "1100"; end if;
        
        -- BLT (SGE)
        if funct3 = "100" then opcode <= "1010"; end if;
        
        -- BGE (SLT)
        if funct3 = "101" then opcode <= "1000"; end if;
        
      -- R-Type
      when "010" =>
        -- ADD ou SUB
        if funct3 = "000" then 
          if funct7 = '1' then
            opcode <= "0001"; -- SUB
          else
            opcode <= "0000"; -- ADD
          end if;
        end if;
        
        -- SLL
        if funct3 = "001" then opcode <= "0101"; end if;
        
        -- SLT
        if funct3 = "010" then opcode <= "1000"; end if;
        
        -- SLTU
        if funct3 = "011" then opcode <= "1001"; end if;
        
        -- XOR
        if funct3 = "100" then opcode <= "0100"; end if;
        
        -- SRL ou SRA
        if funct3 = "101" then 
          if funct7 = '1' then
            opcode <= "0111"; -- SRA
          else
            opcode <= "0110"; -- SRL
          end if;
        end if;
        
        -- OR
        if funct3 = "110" then opcode <= "0011"; end if;
        
        -- AND
        if funct3 = "111" then opcode <= "0010"; end if;
        
      when "011" => -- I Type
        -- ADDi
        if funct3 = "000" then opcode <= "0000"; end if;
        
        -- SLTi
        if funct3 = "010" then opcode <= "1000"; end if;
        
        --SLTUi
        if funct3 = "011" then opcode <= "1001"; end if;
        
        -- XORi
        if funct3 = "100" then opcode <= "0100"; end if;
        
        -- SLLi
        if funct3 = "001" then opcode <= "0101"; end if;
        
        -- SRLi ou SRAi
        if funct3 = "101" then 
          if funct7 = '1' then
            opcode <= "0111"; -- SRAi
          else
            opcode <= "0110"; -- SRLi
          end if;
        end if;
        
        -- ORi
        if funct3 = "110" then opcode <= "0011"; end if;
        
        -- ANDi
        if funct3 = "111" then opcode <= "0010"; end if;
        
      -- JAL
      when "100" => opcode <= "1110";
      
      -- JALR
      when "110" => opcode <= "1111";

      -- Unknown
      when others => opcode <= "0000";
      
    end case;
  end process;
end RTL;