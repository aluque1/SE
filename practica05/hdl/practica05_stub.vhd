-------------------------------------------------------------------------------
-- practica05_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity practica05_stub is
  port (
    rst : in std_logic;
    rx : in std_logic;
    tx : out std_logic;
    clk : in std_logic;
    row_serial_out : out std_logic;
    row_clk : out std_logic;
    reset_out : out std_logic;
    col_serial_out : out std_logic;
    col_clk : out std_logic;
    reset2_out : out std_logic;
    s : out std_logic_vector(3 downto 0);
    r : in std_logic_vector(3 downto 0)
  );
end practica05_stub;

architecture STRUCTURE of practica05_stub is

  component practica05 is
    port (
      rst : in std_logic;
      rx : in std_logic;
      tx : out std_logic;
      clk : in std_logic;
      row_serial_out : out std_logic;
      row_clk : out std_logic;
      reset_out : out std_logic;
      col_serial_out : out std_logic;
      col_clk : out std_logic;
      reset2_out : out std_logic;
      s : out std_logic_vector(3 downto 0);
      r : in std_logic_vector(3 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of practica05 : component is "user_black_box";

begin

  practica05_i : practica05
    port map (
      rst => rst,
      rx => rx,
      tx => tx,
      clk => clk,
      row_serial_out => row_serial_out,
      row_clk => row_clk,
      reset_out => reset_out,
      col_serial_out => col_serial_out,
      col_clk => col_clk,
      reset2_out => reset2_out,
      s => s,
      r => r
    );

end architecture STRUCTURE;

