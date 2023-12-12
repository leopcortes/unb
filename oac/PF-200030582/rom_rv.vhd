library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity rom_rv is
  port (
    address : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(31 downto 0)
  );
end entity rom_rv;

architecture RTL of rom_rv is
  type rom_type is array (0 to (2**address'length)-1) of std_logic_vector(dataout'range);

  impure function init_rom_hex return rom_type is
    file text_file       : text open read_mode is "D:\Desktop\Programacao\Programas\unb\oac\PF-200030582\tests\testador_text.txt";
    variable text_line   : line;
    variable rom_content : rom_type;
    variable i           : integer;

  begin 
    i := 0;
    while not endfile(text_file) loop
        readline(text_file, text_line);
        hread(text_line, rom_content(i));
        i := i + 1;
    end loop;

    return rom_content;
  end function;

  signal rom : rom_type := init_rom_hex;

begin
  dataout <= rom(to_integer(unsigned(address)));

end architecture;
