LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY xregs IS
  GENERIC (WSIZE : natural := 32);
  PORT (
    clk, wren : IN std_logic;
    rs1, rs2, rd : IN std_logic_vector(4 DOWNTO 0);
    data : IN std_logic_vector(WSIZE - 1 DOWNTO 0);
    ro1, ro2 : OUT std_logic_vector(WSIZE - 1 DOWNTO 0)
  );
END ENTITY;

ARCHITECTURE arch OF xregs IS
  TYPE REGS_TYPE IS ARRAY (31 DOWNTO 0) OF std_logic_vector(WSIZE - 1 DOWNTO 0);
  SIGNAL regs : REGS_TYPE;
BEGIN
  ro1 <= regs(conv_integer(rs1));
  ro2 <= regs(conv_integer(rs2));
  write_process : PROCESS (clk)
  BEGIN
    IF (wren = '1' AND clk = '1') THEN
      regs(conv_integer(rd)) <= data;
      regs(0) <= 32x"0";
    END IF;
  END PROCESS;
END arch;