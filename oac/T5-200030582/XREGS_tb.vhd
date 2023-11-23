library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity XREGS_tb is
end entity XREGS_tb;

architecture a of XREGS_tb is

    component XREGS is
        generic (WSIZE : natural := 32);
        port(
            clk, wren           : in std_logic;
            rs1, rs2, rd        : in std_logic_vector(4 downto 0);
            data                : in std_logic_vector(WSIZE-1 downto 0);
            ro1, ro2            : out std_logic_vector(WSIZE-1 downto 0);
        );
    end component;

    constant WSIZE : natural := 32;
    signal clk, wren            : std_logic;
    signal rs1, rs2, rd         : std_logic_vector(4 downto 0);
    signal data                 : std_logic_vector(WSIZE-1 downto 0);
    signal ro1, ro2             : std_logic_vector(WSIZE-1 downto 0);

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

    process is
    begin
        for i in 0 to 31 loop
            -- Escrever valores nos registradores
            wren <= '1';
            rs1 <= std_logic_vector(to_unsigned(i, 5));
            rs2 <= (others => '0');
            rd <= std_logic_vector(to_unsigned(i, 5));
            data <= std_logic_vector(to_unsigned(i * 2, WSIZE));
            wait for 1 ns;
            wren <= '0'; -- Desativar a escrita
            
            wait for 1 ns; -- Aguardar um ciclo de clock para garantir a escrita
            
            -- Ler valores dos registradores
            rs1 <= std_logic_vector(to_unsigned(i, 5));
            rs2 <= (others => '0');
            rd <= (others => '0');
            wait for 1 ns;
            
            assert ro1 = std_logic_vector(to_unsigned(i * 2, WSIZE))
                report "Valor lido em ro1 não corresponde ao valor escrito"
                severity error;
            
            assert ro2 = (others => '0')
                report "Valor lido em ro2 deveria ser 0"
                severity error;
        end loop;
    
        -- Escrever um valor diferente de zero no registrador zero
        wren <= '1';
        rs1 <= (others => '0');
        rs2 <= (others => '0');
        rd <= (others => '0');
        data <= std_logic_vector(to_unsigned(999, WSIZE));
        wait for 1 ns;
        wren <= '0'; -- Desativar a escrita
        
        wait for 1 ns; -- Aguardar um ciclo de clock para garantir a escrita
        
        -- Ler o valor do registrador zero
        rs1 <= (others => '0');
        rs2 <= (others => '0');
        rd <= (others => '0');
        wait for 1 ns;
        
        assert ro1 = (others => '0')
            report "O valor do registrador zero foi alterado indevidamente"
            severity error;
    
        assert ro2 = std_logic_vector(to_unsigned(999, WSIZE))
            report "O valor lido em ro2 não corresponde ao valor escrito no registrador zero"
            severity error;
        
        wait;
    end process;                       
end a;