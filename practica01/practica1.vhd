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
use IEEE.std_logic_unsigned.ALL;

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
           led : out  STD_LOGIC;
           ledB : out  STD_LOGIC);
end practica1;

architecture Behavioral of practica1 is

type ESTADOS is (S0, S1, S2, S3, S4, S5);
signal ESTADO, SIG_ESTADO: ESTADOS;

signal buttonDeb: std_logic;
signal clk_aux, ce, cuenta_finS, ledS, clearCont, rst_aux: std_logic;
signal cuentaIn, cuenta_larga, cuenta_corta: std_logic_vector(31 downto 0);

component divisor1000HZ is
    Port (
        rst: in STD_LOGIC;
        clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC);
end component;

component contador32b is
    Port (
        rst: IN STD_LOGIC;
        clk: IN STD_LOGIC;
        ce: IN STD_LOGIC;
        cuenta_fin: OUT STD_LOGIC;
        cuenta_max: IN STD_LOGIC_VECTOR(31 downto 0));
end component;

begin

--cuenta larga = 1500ms, cuenta corta = 500ms
cuenta_larga <= "00000000000000000000011110111000";
cuenta_corta <= "00000000000000000000000111110100";
led <= ledS;
ledB <= button;
buttonDeb <= not(button);
rst_aux <= clearCont or rst;

divisor: divisor1000HZ
    Port map(
        rst => rst,
        clk_in => clk,
        clk_out => clk_aux
);

contador: contador32b
    Port map(
        rst => rst_aux,
        clk => clk_aux,
        ce => ce,
        cuenta_fin => cuenta_finS,
        cuenta_max => cuentaIn
);


SYNC: process(clk_aux, rst)
begin
    if rst = '1' then
        ESTADO <= S0;
    elsif rising_edge(clk_aux) then
        ESTADO <= SIG_ESTADO;
    end if;
end process;

--FSM mientras el boton este presionado
FSM: process(ESTADO, buttonDeb, cuenta_finS)
begin
    ledS <= '0';
    ce <= '0';
    clearCont <= '0';
    cuentaIn <= (others => '1');
    case ESTADO is
        when S0 =>
            if buttonDeb = '1' then
                SIG_ESTADO <= S1;
            else
                SIG_ESTADO <= S0;
            end if;
        when S1 =>
            ce <= '1';
            cuentaIn <= cuenta_corta;
            if buttonDeb = '0' or cuenta_finS = '1' then
                if cuenta_finS = '1' then
                    SIG_ESTADO <= S2;
                else
                    SIG_ESTADO <= S3;
                end if;
            else
                SIG_ESTADO <= S1;
            end if;
        when S2 =>
            clearCont <= '1';
            if buttonDeb = '0' then
                SIG_ESTADO <= S4;
            else
                SIG_ESTADO <= S2;
            end if;
        when S4 =>
            ledS <= '1';
            ce <= '1';
            cuentaIn <= cuenta_larga;
            if cuenta_finS = '1' then
                SIG_ESTADO <= S0;
            else
                SIG_ESTADO <= S4;
            end if;

        when S3 =>
            clearCont <= '1';
            if buttonDeb = '0' then
                SIG_ESTADO <= S5;
            else
                SIG_ESTADO <= S2;
            end if;
        when S5 =>
            ledS <= '1';
            ce <= '1';
            cuentaIn <= cuenta_corta;
            if cuenta_finS = '1' then
                SIG_ESTADO <= S0;
            else
                SIG_ESTADO <= S5;
            end if;
        when others =>
            SIG_ESTADO <= S0;
    end case;
end process;

end Behavioral;