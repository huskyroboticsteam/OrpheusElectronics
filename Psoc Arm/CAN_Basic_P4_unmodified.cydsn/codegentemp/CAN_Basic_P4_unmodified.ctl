-- ======================================================================
-- CAN_Basic_P4_unmodified.ctl generated from CAN_Basic_P4_unmodified
-- 12/22/2018 at 16:17
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-046 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(3,0)";
attribute port_location of \UART:tx(0)\ : label is "PORT(3,1)";

-- === CAN ===
attribute port_location of RX(0) : label is "PORT(0,0)";
attribute port_location of TX(0) : label is "PORT(0,1)";

-- === USER SWITCH ===
attribute port_location of Switch1(0) : label is "PORT(0,7)";

attribute port_location of PWM_OUT(0) : label is "PORT(0,2)";
attribute port_location of V1(0) : label is "PORT(2,0)";
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
