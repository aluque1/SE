-------------------------------------------------------------------------------
-- practica2_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity practica2_stub is
  port (
    rst : in std_logic;
    rx : in std_logic;
    tx : out std_logic;
    leds : inout std_logic_vector(0 to 7);
    switches : inout std_logic_vector(0 to 7);
    clk : in std_logic
  );
end practica2_stub;

architecture STRUCTURE of practica2_stub is

  component practica2 is
    port (
      rst : in std_logic;
      rx : in std_logic;
      tx : out std_logic;
      leds : inout std_logic_vector(0 to 7);
      switches : inout std_logic_vector(0 to 7);
      clk : in std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of practica2 : component is "user_black_box";

begin

  practica2_i : practica2
    port map (
      rst => rst,
      rx => rx,
      tx => tx,
      leds => leds,
      switches => switches,
      clk => clk
    );

end architecture STRUCTURE;

