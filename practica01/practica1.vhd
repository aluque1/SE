----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:24:57 11/04/2023 
-- Design Name: 
-- Module Name:    practica1 - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity practica1 is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           button : in  STD_LOGIC;
           led : out  STD_LOGIC);
end practica1;

architecture Behavioral of practica1 is

type ESTADOS is (S0, S1, S2);
signal ESTADO, SIG_ESTADO: ESTADOS;

signal buttonDeb, buttonDebFallingEdge, buttonDebRisingEdge: std_logic;
signal cae, cde, cuenta_fin: std_logic;


component contadorAscDes_ms is
    Port (
        rst: IN STD_LOGIC;
        clk: IN STD_LOGIC;
        cae: IN STD_LOGIC;
        cde: IN STD_LOGIC;
        cuenta_fin: OUT STD_LOGIC);
end component;

component debouncer is
    Port (
        rst: IN std_logic;
        clk: IN std_logic;
        x: IN std_logic;
        xDeb: OUT std_logic;
        xDebFallingEdge: OUT std_logic;
        xDebRisingEdge: OUT std_logic);
end component;

begin

boton: debouncer
    Port map(
        rst => rst,
        clk => clk,
        x => not(button),
        xDeb => buttonDeb,
        xDebFallingEdge => buttonDebFallingEdge,
        xDebRisingEdge => buttonDebRisingEdge
);

contador: contadorAscDes_ms
    Port map(
        rst => rst,
        clk => clk,
        cae => cae,
        cde => cde,
        cuenta_fin => cuenta_fin
);

SYNC: process(clk, rst)
begin
    if rst = '1' then
        ESTADO <= S0;
    elsif rising_edge(clk) then
        ESTADO <= SIG_ESTADO;
    end if;
end process;

--FSM mientras el boton este presionado, cae = 1, cde = 0. Cuando se suelta, cae = 0, cde = 1 y cambiar de estado. cuando cuenta fin = 1, vuelve al estado inicial
FSM: process(ESTADO, buttonDebFallingEdge, buttonDebRisingEdge, cuenta_fin)
begin
    led <= '0';
    cae <= '0';
    cde <= '0';
    case ESTADO is
        when S0 =>
            if buttonDebRisingEdge = '1' then
                SIG_ESTADO <= S1;
            else
                SIG_ESTADO <= S0;
            end if;
        when S1 =>
            cae <= '1';
            if buttonDebFallingEdge = '1' then
                SIG_ESTADO <= S2;
            else
                SIG_ESTADO <= S1;
            end if;
        when S2 =>
            cde <= '1';
            led <= '1';
            if cuenta_fin = '1' then
                SIG_ESTADO <= S0;
            else
                SIG_ESTADO <= S2;
            end if;
        when others =>
            SIG_ESTADO <= S0;
    end case;
end process;

end Behavioral;