-------------------------------------------------------------------------------
-- practica03_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity practica03_stub is
  port (
    rst : in std_logic;
    rx : in std_logic;
    tx : out std_logic;
    clk : in std_logic;
    switches : in std_logic_vector(7 downto 0);
    leds : out std_logic_vector(7 downto 0)
  );
end practica03_stub;

architecture STRUCTURE of practica03_stub is

  component practica03 is
    port (
      rst : in std_logic;
      rx : in std_logic;
      tx : out std_logic;
      clk : in std_logic;
      switches : in std_logic_vector(7 downto 0);
      leds : out std_logic_vector(7 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of practica03 : component is "user_black_box";

begin

  practica03_i : practica03
    port map (
      rst => rst,
      rx => rx,
      tx => tx,
      clk => clk,
      switches => switches,
      leds => leds
    );

end architecture STRUCTURE;

