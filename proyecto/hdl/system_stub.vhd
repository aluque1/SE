-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    clk : in std_logic;
    rx : in std_logic;
    tx : out std_logic;
    rst : in std_logic;
    col_serial_out : out std_logic;
    col_clk : out std_logic;
    row_serial_out : out std_logic;
    row_clk : out std_logic;
    reset_out : out std_logic;
    reset2_out : out std_logic;
    ps2Clk : in std_logic;
    ps2Data : in std_logic;
    zumba : inout std_logic;
    s : out std_logic_vector(3 downto 0);
    r : in std_logic_vector(3 downto 0);
    red : out std_logic;
    green : out std_logic;
    blue : out std_logic
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      clk : in std_logic;
      rx : in std_logic;
      tx : out std_logic;
      rst : in std_logic;
      col_serial_out : out std_logic;
      col_clk : out std_logic;
      row_serial_out : out std_logic;
      row_clk : out std_logic;
      reset_out : out std_logic;
      reset2_out : out std_logic;
      ps2Clk : in std_logic;
      ps2Data : in std_logic;
      zumba : inout std_logic;
      s : out std_logic_vector(3 downto 0);
      r : in std_logic_vector(3 downto 0);
      red : out std_logic;
      green : out std_logic;
      blue : out std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      clk => clk,
      rx => rx,
      tx => tx,
      rst => rst,
      col_serial_out => col_serial_out,
      col_clk => col_clk,
      row_serial_out => row_serial_out,
      row_clk => row_clk,
      reset_out => reset_out,
      reset2_out => reset2_out,
      ps2Clk => ps2Clk,
      ps2Data => ps2Data,
      zumba => zumba,
      s => s,
      r => r,
      red => red,
      green => green,
      blue => blue
    );

end architecture STRUCTURE;

