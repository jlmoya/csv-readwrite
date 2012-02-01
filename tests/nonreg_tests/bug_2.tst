//
//  Copyright (C) 2010 - 2012 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

// =============================================================================
r_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_2.csv", ",", [], "string");
r_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_2.csv", ",", ".", "double");
// =============================================================================
assert_checkequal(size(r_string, "c"), size(r_double, "c"));
assert_checkequal(size(r_string, "r"), size(r_double, "r"));
assert_checkequal(size(r_string, "c"), 100);
assert_checkequal(size(r_string, "r"), 100);
assert_checkequal(r_string(100, 100), '1');
assert_checkequal(and(r_double == eye(100,100)), %T);
// =============================================================================
