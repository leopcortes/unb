library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity XREGS_tb is
end entity XREGS_tb;

architecture RTL of XREGS_tb is
  component XREGS is
    generic (WSIZE : natural := 32);
    port(
      clk, wren           : in std_logic;
      rs1, rs2, rd        : in std_logic_vector(4 downto 0);
      data                : in std_logic_vector(WSIZE-1 downto 0);
      ro1, ro2            : out std_logic_vector(WSIZE-1 downto 0) := (others => '0')
    );
  end component;

  constant WSIZE : natural := 32;
  signal clk, wren            : std_logic;
  signal rs1, rs2, rd         : std_logic_vector(4 downto 0);
  signal data                 : std_logic_vector(WSIZE-1 downto 0);
  signal ro1, ro2             : std_logic_vector(WSIZE-1 downto 0) := (others => '0');
  
  signal seq_val              : std_logic_vector(WSIZE-1 downto 0) := x"00000000";

begin
  i_XREGS: XREGS generic map (WSIZE => WSIZE)
  port map (
    clk => clk,
    wren => wren,
    rs1 => rs1,
    rs2 => rs2,
    rd => rd,
    data => data,
    ro1 => ro1,
    ro2 => ro2
  );

  process is begin
    -- O loop realiza 31 iteracoes para possibilitar a verificacao dos 32 regs sem gerar um erro "out of range" por rs2 ser i+1, para ser um endereco diferente de rs1
    for i in 0 to 30 loop 
      wren <= '0';
      rs1 <= std_logic_vector(to_unsigned(i, 5));
      rs2 <= std_logic_vector(to_unsigned(i+1, 5));
      clk <= '0';
      wait for 1 ns;

      wren <= '1';
      rd <= std_logic_vector(to_unsigned(i, 5));
      data <= seq_val;
      clk <= '1';
      wait for 1 ns;
        
      clk <= '0';
      wait for 1 ns;
        
      wren <= '1';
      rd <= std_logic_vector(to_unsigned(i+1, 5));
      data <= seq_val;
      clk <= '1';
      wait for 1 ns;
        
      clk <= '0';
      wait for 1 ns;
  
      assert (ro1 = seq_val) report "Erro, valor inesperado em ro1." severity error;
      assert (ro2 = seq_val) report "Erro, valor inesperado em ro2." severity error;
        
      seq_val <= std_logic_vector(unsigned(seq_val) + 1);

    end loop;
    
    -- Escrita de um valor diferente de zero em regs[0] para verificar se ele nao e alterado
    rs1 <= 5x"0";
    clk <= '0';
    wait for 1 ns;

    wren <= '1';
    rd <= 5x"0";
    data <= x"FACACAFE";
    clk <= '1';
    wait for 1 ns;

    assert (ro1 = x"00000000") report "Erro, valor diferente de zero em regs[0]." severity error;
    
    report "Testes do XREGS concluidos." severity note;
    wait for 1 ns;

  end process;  
end RTL;