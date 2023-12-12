library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use std.textio.all;

entity ram_rv_tb is
end ram_rv_tb;

architecture RTL of ram_rv_tb is
	component ram_rv is
		port (
			clock   : in std_logic;
			we      : in std_logic;
			address : in std_logic_vector;
			datain  : in std_logic_vector;
			dataout : out std_logic_vector
		);
	end component ram_rv;

	signal clock   : std_logic;
	signal we      : std_logic;
	signal address : std_logic_vector(7 downto 0);
	signal datain  : std_logic_vector(31 downto 0);
	signal dataout : std_logic_vector(31 downto 0);

begin
	ram : ram_rv port map(
		clock => clock,
		we => we,
		address => address,
		datain => datain,
		dataout => dataout
	);

  process begin
    for i in 0 to 255 loop
      address <= std_logic_vector(to_unsigned(i, 8));
      datain <= std_logic_vector(to_unsigned(i, 30)) & "00";

      clock <= '0';
      we <= '1';
      wait for 1 ns;
      clock <= '1';
      wait for 1 ns;
      assert (dataout = datain) report "Erro no write. Dataout = " & to_hstring(dataout) severity error;

      datain <= std_logic_vector(to_unsigned(i+1, 30)) & "00";
      clock <= '0';
      wait for 1 ns;
      assert (dataout /= datain) report "Erro na descida do clock. Dataout = " & to_hstring(dataout) severity error;

      we <= '0';
      clock <= '1';
      datain <= std_logic_vector(to_unsigned(i+2, 30)) & "00";
      wait for 1 ns;
      assert (dataout /= datain) report "Erro em !write. Dataout = " & to_hstring(dataout) severity error;
    end loop;
    
    report "Testes do RAM concluidos." severity note;
    wait for 1 ns;
	
  end process;
end RTL;