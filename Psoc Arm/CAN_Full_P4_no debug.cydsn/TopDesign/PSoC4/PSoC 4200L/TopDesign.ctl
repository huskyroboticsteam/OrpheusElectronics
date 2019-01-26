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