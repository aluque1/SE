----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:57:05 11/17/2008 
-- Design Name: 
-- Module Name:    vga - Behavioral 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity vgacore is
	port
	(
		reset: in std_logic;	-- reset
		clock: in std_logic; -- 12,5 MHz
		hsyncb: out std_logic;	-- horizontal (line) sync
		load: in std_logic;
		color: in std_logic_vector(8 downto 0); -- color
		rectangulo: in std_logic_vector(6 downto 0); -- rectangulo a borrar
		vsyncb: out std_logic;	-- vertical (frame) sync
		rgb: out std_logic_vector(8 downto 0);	-- red,green,blue colors
		buttons: in std_logic_vector(1 downto 0) -- botones
	);
end vgacore;

architecture vgacore_arch of vgacore is

	component debouncer
		port
		(
			rst: IN std_logic;
			clk: IN std_logic;
			x: IN std_logic;
			xDeb: OUT std_logic;
			xDebFallingEdge: OUT std_logic;
			xDebRisingEdge: OUT std_logic
		);
	end component;

signal hcnt: std_logic_vector(8 downto 0);	-- horizontal pixel counter
signal vcnt: std_logic_vector(9 downto 0);	-- vertical line counter
signal desp: std_logic_vector(8 downto 0); -- desplazamiento
signal cuentaDiv: std_logic_vector(23 downto 0); -- cuenta divisor
signal cuentaAux: std_logic_vector(23 downto 0); -- cuenta actual
signal clkDiv: std_logic; -- clock divisor
signal buttDeb1: std_logic; -- boton 1 debounced
signal buttDeb2: std_logic; -- boton 2 debounced
signal buttDeb1FallingEdge: std_logic; -- boton 1 debounced falling edge
signal buttDeb2FallingEdge: std_logic; -- boton 2 debounced falling edge
signal buttDeb1RisingEdge: std_logic; -- boton 1 debounced rising edge
signal buttDeb2RisingEdge: std_logic; -- boton 2 debounced rising edge
signal hdesp: std_logic_vector(8 downto 0);

type ram_type is array (0 to 127) of std_logic_vector(8 downto 0);
signal RAM : ram_type :=
(
"000000001", "000000010", "000000011", "000000100", "000000101", "000000110","000000111",
"000001001", "000001010", "000001011", "000001100", "000001101", "000001110","000001111",
"000010001", "000010010", "000010011", "000010100", "000010101", "000010110","000010111",
"000100001", "000100010", "000100011", "000100100", "000100101", "000100110","000100111",
"001000001", "001000010", "001000011", "001000100", "001000101", "001000110","001000111",
"010000001", "010000010", "010000011", "010000100", "010000101", "010000110","010000111",
"100000001", "100000010", "100000011", "100000100", "100000101", "100000110","100000111",
"110000001", "110000010", "110000011", "110000100", "110000101", "110000110","110000111",
"110001001", "110001010", "110001011", "110001100", "110001101", "110001110","110001111",
"110010001", "110010010", "110010011", "110010100", "110010101", "110010110","110010111",
"110100001", "110100010", "110100011", "110100100", "110100101", "110010110","110100111",
"111000001", "111000010", "111000011", "111000100", "111000101", "111000110","111000111",
"110000001", "110010010", "110010011", "110000100", "111010101", "110000110","011100111",
"110010001", "110000010", "110000011", "110000100", "110000101", "110010110","100011111",
"000010001", "000000010", "000000011", "000000100", "000000101", "000000110","000000111",
"000001001", "000111010", "000001011", "000001100", "000001101", "000001110","000001111",
"000010001", "000010010", "111010011", "000010100", "000010101", "000010110","000010111",
"001111111", "000100010", "000100011", "000100100", "011100101", "000100110","000100111",
"111111010", "111111111");

--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111", "111111111", "111111111", "111111111", "111111111","111111111",
--"111111111", "111111111");


signal hsyncbAux : std_logic;

begin

hsyncb <= hsyncbAux;
cuentaDiv <= "000101111101011110000100";
hdesp <= hcnt - desp;

A: process(clock,reset)
begin
	-- reset asynchronously clears pixel counter
	if reset='1' then
		hcnt <= "000000000";
	-- horiz. pixel counter increments on rising edge of dot clock
	elsif (clock'event and clock='1') then
		-- horiz. pixel counter rolls-over after 381 pixels
		if hcnt<380 then
			hcnt <= hcnt + 1;
		else
			hcnt <= "000000000";
		end if;
	end if;
end process;

B: process(hsyncbAux,reset)
begin
	-- reset asynchronously clears line counter
	if reset='1' then
		vcnt <= "0000000000";
	-- vert. line counter increments after every horiz. line
	elsif (hsyncbAux'event and hsyncbAux='1') then
		-- vert. line counter rolls-over after 528 lines
		if vcnt<527 then
			vcnt <= vcnt + 1;
		else
			vcnt <= "0000000000";
		end if;
	end if;
end process;

C: process(clock,reset)
begin
	-- reset asynchronously sets horizontal sync to inactive
	if reset='1' then
		hsyncbAux <= '1';
	-- horizontal sync is recomputed on the rising edge of every dot clock
	elsif (clock'event and clock='1') then
		-- horiz. sync is low in this interval to signal start of a new line
		if (hcnt>=291 and hcnt<337) then
			hsyncbAux <= '0';
		else
			hsyncbAux <= '1';
		end if;
	end if;
end process;

D: process(hsyncbAux,reset)
begin
	-- reset asynchronously sets vertical sync to inactive
	if reset='1' then
		vsyncb <= '1';
	-- vertical sync is recomputed at the end of every line of pixels
	elsif (hsyncbAux'event and hsyncbAux='1') then
		-- vert. sync is low in this interval to signal start of a new frame
		if (vcnt>=490 and vcnt<492) then
			vsyncb <= '0';
		else
			vsyncb <= '1';
		end if;
	end if;
end process;

-- A partir de aqui escribir la parte de dibujar en la pantalla

-- Dibujamos rect�ngulos de 16x8
-- vcnt(8 downto 4)x hcnt(6 downto 3)
process(clock, load, rectangulo)
begin
		if clock'event and clock='1' then
			if load='1' then 
				RAM(conv_integer(rectangulo))<= color;
			end if;
		end if;
end process;

divisorFreq: process(clock, reset)
begin
	if reset = '1' then
		cuentaAux <= (others => '0');
		clkDiv <= '0';
	elsif rising_edge(clock) then
		if cuentaAux = cuentaDiv then
			cuentaAux <= (others => '0');
			clkDiv <= not(clkDiv);
		else
			cuentaAux <= cuentaAux + 1;
		end if;
	end if;
end process;

debouncer1: debouncer 
	port map
	(
		rst => not(reset),
		clk => clock,
		x => not(buttons(0)),
		xDeb => buttDeb1,
		xDebFallingEdge => buttDeb1FallingEdge,
		xDebRisingEdge => buttDeb1RisingEdge
	);

debouncer2: debouncer
	port map
	(
		rst => not(reset),
		clk => clock,
		x => not(buttons(1)),
		xDeb => buttDeb2,
		xDebFallingEdge => buttDeb2FallingEdge,
		xDebRisingEdge => buttDeb2RisingEdge
	);


desplazamiento: process(clkDiv, reset)
begin
	if reset = '1' then
		desp <= "000000000";
	elsif rising_edge(clkDiv) then
		if buttDeb1 = '1' then
			desp <= desp + 1;
		elsif buttDeb2 = '1' and desp > 0 then
			desp <= desp - 1;
		end if;
	end if;
end process;

process (hcnt, vcnt, desp)
begin
	if (vcnt(9 downto 8) = "00" and (hcnt >= desp and hcnt < desp + 63)) then
		rgb <= RAM(conv_integer(hdesp(5 downto 3)&vcnt(7 downto 4)));
	else
		rgb <= "000000000";
	end if;
end process;

---------------------------------------------------------------------
end vgacore_arch;
