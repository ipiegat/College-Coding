----------------------------------------------------------------------------------
-- ECE 3401 2026: Arrays and Matrices Definition
-- University of Connecticut
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package array_pkg is

  --Size of the arrays (DO NOT MODIFY)
  constant DIM : integer := 3;

  --Our custom array data types (DO NOT MODIFY)
  type matrix is array(0 to DIM-1, 0 to DIM-1) of integer;
  
end package array_pkg;