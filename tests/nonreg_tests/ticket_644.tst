// Copyright (C) 2012 - DIGITEO - Allan CORNET
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//
// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 644 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/644/
//
// <-- Short Description -->
// csv_read did not support empty fields

REF_str_m = ['1','','3';'4','5','6'];
csv_write(REF_str_m, TMPDIR + "/ticket_644.csv");
str_m = csv_read(TMPDIR + "/ticket_644.csv", [], [], "string");
assert_checkequal(str_m, REF_str_m);

REF_str_m = ['','2','3';'4','5','6'];
csv_write(REF_str_m, TMPDIR + "/ticket_644.csv");
str_m = csv_read(TMPDIR + "/ticket_644.csv", [], [], "string");
assert_checkequal(str_m, REF_str_m);


REF_str_m = ['','2','3';'4','','6'];
csv_write(REF_str_m, TMPDIR + "/ticket_644.csv");
str_m = csv_read(TMPDIR + "/ticket_644.csv", [], [], "string");
assert_checkequal(str_m, REF_str_m);


REF_str_m = ['1','2','3';'4','5',''];
str_m = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/ticket_644.csv", [], [], "string");
assert_checkequal(str_m, REF_str_m);

