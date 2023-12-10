----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:30:00 11/22/2023 
-- Design Name: 
-- Module Name:    contadorAscDesc - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity contador32b is
    Port (
        rst: IN STD_LOGIC;
        clk: IN STD_LOGIC;
        ce: IN STD_LOGIC;
        cuenta_fin: OUT STD_LOGIC;
        cuenta_max: IN STD_LOGIC_VECTOR(31 downto 0));
end contador32b;

architecture contador32b_arch of contador32b is
signal cuenta: std_logic_vector(31 downto 0);
  
begin
    process(rst, clk, cuenta)
    begin
        if (rst='1') then
            cuenta<= (OTHERS=>'0');
            cuenta_fin <= '0';
        elsif rising_edge(clk) and (ce = '1') then
            if (cuenta = cuenta_max) then
                cuenta_fin <= '1';
                cuenta <= (OTHERS=>'0');
            else
                cuenta <= cuenta + 1;
                cuenta_fin <= '0';
            end if;
        end if;
    end process;

end contador32b_arch;


