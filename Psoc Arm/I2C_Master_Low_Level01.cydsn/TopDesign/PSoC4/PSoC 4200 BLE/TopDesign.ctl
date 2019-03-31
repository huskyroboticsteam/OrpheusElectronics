-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-042 BLE kit.
-- =============================================================================

-- === I2C Master ===
attribute port_location of \mI2C:scl(0)\ : label is "PORT(3,5)";
attribute port_location of \mI2C:sda(0)\ : label is "PORT(3,4)";