LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE std.textio.ALL; -- Imports the standard textio package.

ENTITY xregsTestbench IS
END xregsTestbench;

ARCHITECTURE xregsTestbench OF xregsTestbench IS
  COMPONENT xregs IS
    PORT (
      clk, wren : IN std_logic;
      rs1, rs2, rd : IN std_logic_vector(4 DOWNTO 0);
      data : IN std_logic_vector(32 - 1 DOWNTO 0);
      ro1, ro2 : OUT std_logic_vector(32 - 1 DOWNTO 0)
    );
  END COMPONENT;
  SIGNAL clk, wren : std_logic;
  SIGNAL rs1, rs2, rd : std_logic_vector(4 DOWNTO 0);
  SIGNAL data : std_logic_vector(32 - 1 DOWNTO 0);
  SIGNAL ro1, ro2 : std_logic_vector(32 - 1 DOWNTO 0);
BEGIN
  dut : xregs PORT MAP(
    clk => clk, wren => wren,
    rs1 => rs1, rs2 => rs2, rd => rd,
    data => data,
    ro1 => ro1, ro2 => ro2);
  PROCESS
  BEGIN
    -- write in rs1 and rs2
    rs1 <= 5x"01";
    rs2 <= 5x"02";
    clk <= '0';
    WAIT FOR 10 ps;
    wren <= '1';
    rd <= 5x"01";
    data <= x"AABBCCDD";
    clk <= '1';
    WAIT FOR 10 ps;
    clk <= '0';
    WAIT FOR 10 ps;
    wren <= '1';
    rd <= 5x"02";
    data <= x"DDCCBBAA";
    clk <= '1';
    WAIT FOR 10 ps;
    ASSERT (ro1 = x"AABBCCDD") REPORT "ERRO RS1";
    ASSERT (ro2 = x"DDCCBBAA") REPORT "ERRO RS2";
    -- write in zero
    rs1 <= 5x"00";
    clk <= '0';
    WAIT FOR 10 ps;
    wren <= '1';
    rd <= 5x"00";
    data <= x"01234567";
    clk <= '1';
    WAIT FOR 10 ps;
    ASSERT (ro1 = x"00000000") REPORT "ERRO na leitura do zero";
    -- disabled write;
    rs1 <= 5x"02";
    clk <= '0';
    WAIT FOR 10 ps;
    wren <= '0';
    rd <= 5x"02";
    data <= x"76543210";
    clk <= '1';
    WAIT FOR 10 ps;
    ASSERT (ro1 /= x"76543210") REPORT "ERRO ao desabilitar escrita";
    -- don't clock rise
    wren <= '1';
    clk <= '0';
    WAIT FOR 10 ps;
    ASSERT (ro1 /= x"76543210") REPORT "ERRO ao decrescer sinal do clock";
    -- END
    REPORT "Teste finalizado";
    WAIT;
  END PROCESS;
END xregsTestbench;