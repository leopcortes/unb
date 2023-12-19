library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;	

entity controle is 
  port(
    opcode     : in  std_logic_vector(6 downto 0);
    branch     : out std_logic;
    mem_read   : out std_logic;
    mem_to_reg : out std_logic;
    alu_op     : out std_logic_vector(2 downto 0);
    mem_write  : out std_logic;
    alu_src    : out std_logic;
    reg_write  : out std_logic;
    is_lui     : out std_logic;
    is_auipc   : out std_logic;
    is_jalx    : out std_logic;
    is_jalr    : out std_logic
  );
end entity controle;

architecture RTL of controle is
begin
  process (opcode) begin
    case opcode is
      -- R-Type (Logico Aritmetico)
      when "0110011" => 
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "010";
        mem_write  <= '0';
        alu_src    <= '0';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
      
      -- I-Type (Logico Aritmetico)
      when "0010011" => 
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "011";
        mem_write  <= '0';
        alu_src    <= '1';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
        
      -- S Type-(SW)
      when "0100011" => 
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "000";
        mem_write  <= '1';
        alu_src    <= '1';
        reg_write  <= '0';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
        
      -- LW
      when "0000011" =>
        branch     <= '0';
        mem_read   <= '1';
        mem_to_reg <= '1';
        alu_op     <= "000";
        mem_write  <= '0';
        alu_src    <= '1';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
      
      -- B(SB)-Type
      when "1100011" => 
        branch     <= '1';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "001";
        mem_write  <= '0';
        alu_src    <= '0';
        reg_write  <= '0';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
      
      -- U-Type (LUI)
      when "0110111" =>
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "000";
        mem_write  <= '0';
        alu_src    <= '1';
        reg_write  <= '1';
        is_lui     <= '1';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
        
      -- U-Type (AUIPC)
      when "0010111" => 
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "000";
        mem_write  <= '0';
        alu_src    <= '1';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '1';
        is_jalx    <= '0';
        is_jalr    <= '0';
        
      -- UJ-Type (JAL)
      when "1101111" => 
        branch     <= '1';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "100";
        mem_write  <= '0';
        alu_src    <= '0';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '1';
        is_jalr    <= '0';
      
      -- JALR
      when "1100111" => 
        branch     <= '1';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "110";
        mem_write  <= '0';
        alu_src    <= '1';
        reg_write  <= '1';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '1';
        is_jalr    <= '1';
        
      -- Unknown
      when others =>
        branch     <= '0';
        mem_read   <= '0';
        mem_to_reg <= '0';
        alu_op     <= "000";
        mem_write  <= '0';
        alu_src    <= '0';
        reg_write  <= '0';
        is_lui     <= '0';
        is_auipc   <= '0';
        is_jalx    <= '0';
        is_jalr    <= '0';
      
    end case;
  end process;
end RTL;