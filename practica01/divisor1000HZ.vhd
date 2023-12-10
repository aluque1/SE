----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:41:54 11/22/2023 
-- Design Name: 
-- Module Name:    divisor1000HZ - divisor1000 
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

entity divisor1000HZ is
    port (
        rst: in STD_LOGIC;
        clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC);
end divisor1000HZ;

architecture Behavioral of divisor1000HZ is

signal cuenta: std_logic_vector(19 downto 0);
signal clk_aux: std_logic;
  
begin

    process( rst, clk_in )
    begin
        if (rst='1') then
            cuenta<= (OTHERS=>'0');
        elsif rising_edge(clk_in) then
            if (cuenta="00011000011010100000") then
      	        clk_aux <= not clk_aux;
                cuenta<= (OTHERS=>'0');
            else
                cuenta <= cuenta + 1;
            end if;
        end if;
    end process;

clk_out <= clk_aux;

end Behavioral;