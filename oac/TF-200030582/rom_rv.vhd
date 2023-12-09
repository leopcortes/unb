library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity rom_rv is
  port (
    address : in  std_logic_vector;
    dataout : out std_logic_vector
  );
end entity rom_rv;

architecture RTL of rom_rv is
  type mem_type is array (0 to (2**address'length)-1) of std_logic_vector(dataout'range);

  impure function init_rom_hex return mem_type is
    file text_file       : text open read_mode is "instructions.txt";
    variable text_line   : line;
    variable rom_content : mem_type;

  begin
    for i in 0 to (2**address'length)-1 loop
      readline(text_file, text_line);
      hread(text_line, rom_content(i));
    end loop;

    return rom_content;
  end function;

  signal rom : mem_type := init_rom_hex;

begin
  dataout <= rom(to_integer(unsigned(address)));

end architecture;