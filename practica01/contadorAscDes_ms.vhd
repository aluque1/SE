library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.ALL;

entity contadorAscDes_ms is
    Port (
        rst: IN STD_LOGIC;
        clk: IN STD_LOGIC;
        cae: IN STD_LOGIC;
        cde: IN STD_LOGIC;
        cuenta_fin: OUT STD_LOGIC);
end contadorAscDes_ms;

architecture contadorAscDes_ms_arch of contadorAscDes_ms is
signal cuenta_aux: std_logic_vector(19 downto 0);
signal cuenta: std_logic_vector(15 downto 0);
  
begin
    process(rst, clk, cuenta_aux, cuenta)
    begin
        if (rst='1') then
            cuenta_aux<= (OTHERS=>'0');
            cuenta<= (OTHERS=>'0');
        elsif rising_edge(clk) then
            if (cuenta_aux = "00011000011010100000") then
                cuenta_aux <= (OTHERS=>'0');
                if (cae = '1') then
                    cuenta <= cuenta + 1;
                elsif (cde = '1') then
                    cuenta <= cuenta - 1;
                else 
                    cuenta <= cuenta;
                end if;
                if (cuenta = "0000000000000000") then
                    cuenta_fin <= '1';
                else
                    cuenta_fin <= '0';
                end if;
            else
                cuenta_aux <= cuenta_aux + 1;
            end if;
        end if;
    end process;

end contadorAscDes_ms_arch;
