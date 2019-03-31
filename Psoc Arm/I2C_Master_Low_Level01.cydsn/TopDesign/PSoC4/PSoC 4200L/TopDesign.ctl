-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-046 kit.
-- =============================================================================

-- === I2C Master ===
attribute port_location of \mI2C:scl(0)\ : label is "PORT(4,0)";
attribute port_location of \mI2C:sda(0)\ : label is "PORT(4,1)";