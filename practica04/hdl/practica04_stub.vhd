-------------------------------------------------------------------------------
-- practica04_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity practica04_stub is
  port (
    rst : in std_logic;
    rx : in std_logic;
    tx : out std_logic;
    leds : inout std_logic_vector(0 to 7);
    switches : inout std_logic_vector(0 to 7);
    clk : in std_logic;
    hsyncb : out std_logic;
    vsyncb : out std_logic;
    rgb : out std_logic_vector(0 to 8)
  );
end practica04_stub;

architecture STRUCTURE of practica04_stub is

  component practica04 is
    port (
      rst : in std_logic;
      rx : in std_logic;
      tx : out std_logic;
      leds : inout std_logic_vector(0 to 7);
      switches : inout std_logic_vector(0 to 7);
      clk : in std_logic;
      hsyncb : out std_logic;
      vsyncb : out std_logic;
      rgb : out std_logic_vector(0 to 8)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of practica04 : component is "user_black_box";

begin

  practica04_i : practica04
    port map (
      rst => rst,
      rx => rx,
      tx => tx,
      leds => leds,
      switches => switches,
      clk => clk,
      hsyncb => hsyncb,
      vsyncb => vsyncb,
      rgb => rgb
    );

end architecture STRUCTURE;

