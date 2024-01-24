LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;

ENTITY keyboard IS
  PORT (
    rst: IN std_logic;
    clk: IN std_logic;
    ps2Clk: IN std_logic;
    ps2Data: IN std_logic;
   Datap: Out std_logic_vector(7 downto 0);
	ldData:out std_logic;
	ackData: in std_logic
  );
END keyboard;

ARCHITECTURE keyboardArch OF keyboard IS
 
  COMPONENT ps2KeyboardInterface 
    PORT (
      clk: IN std_logic;
      rst: IN std_logic;
      ps2Clk: IN std_logic;
      ps2Data: IN std_logic;        
      data: OUT std_logic_vector (7 DOWNTO 0);
      newData: OUT std_logic;
      newDataAck: IN std_logic
    );
  END COMPONENT;

  SIGNAL data: std_logic_vector (7 DOWNTO 0);
  SIGNAL newData, newDataAck,ldDatas: std_logic;
  
  SIGNAL scanCode: std_logic_vector(7 DOWNTO 0);
  SIGNAL loadScanCode: std_logic;
 
BEGIN

  ps2Interface: ps2KeyboardInterface
    PORT MAP (clk, rst, ps2Clk, ps2Data, data, newData, newDataAck);

  controller:
  PROCESS (rst, clk)
    TYPE states IS (waitingNewData, checkF0, waitingNewData2, acknowledgeNewData);
    VARIABLE state: states; 
  BEGIN
    newDataAck <= '0';
    loadScanCode <= '0';
    CASE state IS
      WHEN checkF0 =>
        newDataAck <= '1';
      WHEN acknowledgeNewData =>
        newDataAck <= '1';
        loadScanCode <='1';				
      WHEN OTHERS => NULL;							
    END CASE;
    IF (rst='0') THEN 
      state := waitingNewData;
    ELSIF (clk'EVENT AND clk='1') THEN
      CASE state IS
        WHEN waitingNewData => 
          IF (newData='1') THEN
            state := checkF0;
          END IF;
        WHEN checkF0 =>	  			
          IF (data="11110000") THEN
            state := waitingNewData2;
          ELSE
            state := waitingNewData;        
          END IF;
        WHEN waitingNewData2 =>
          IF (newData='1') THEN
            state := acknowledgeNewData;
          END IF; 					
        WHEN OTHERS => 
          state := waitingNewData;
      END CASE;    
    END IF;
  END PROCESS;
  
  scanCodeReg:
  PROCESS(rst, clk)
  BEGIN
    IF (rst='0') THEN
      scanCode <= (OTHERS=>'0');
		ldDatas<='0';
    ELSIF (clk'EVENT AND clk='1') THEN
      IF (loadScanCode='1') THEN
        scanCode <= data;
		  ldDatas<='1';
		  else
		  if ackData='1' then
		  ldDatas<='0';
		  end if;
      END IF;
    END IF;
  END PROCESS scanCodeReg;
  
 datap<=scanCode;
 ldData<=ldDatas;
      
END keyboardArch;
