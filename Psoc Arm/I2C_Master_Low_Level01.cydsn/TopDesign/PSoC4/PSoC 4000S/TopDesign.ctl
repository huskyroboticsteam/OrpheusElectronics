-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-041-41XX or CY8CKIT-041-40XX kits.
-- =============================================================================

-- === I2C Master ===
attribute port_location of \mI2C:scl(0)\ : label is "PORT(3,0)";
attribute port_location of \mI2C:sda(0)\ : label is "PORT(3,1)";