// =============================================================================
// Allan CORNET - DIGITEO - 2010 - 2012
// =============================================================================
r_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_3.csv", ",", [], "string");
r_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_3.csv", ",", ".", "double");
assert_checkequal(size(r_string, "c"), size(r_double, "c"));
assert_checkequal(size(r_string, "r"), size(r_double, "r"));
assert_checkequal(size(r_string, "c"), 100);
assert_checkequal(size(r_string, "r"), 400);
assert_checkequal(r_string(100, 100), 'NaN');
assert_checkequal(isnan(r_double(100, 100)), %T);
// =============================================================================
