// Copyright (C) 2011 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//
// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 351 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/351/
//
// <-- Short Description -->
// The csv_read function always returns complex entries.

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");

r = csv_read(fullfile(path,"K_1.csv"), [], [], "double");
assert_checkequal ( isreal(r) , %t );

