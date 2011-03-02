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

// <-- Non-regression test for bug 353 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/353/
//
// <-- Short Description -->
// The csv_read function does not manage the range.

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));

//
// Read only rows/columns in range
r = csv_read(fullfile(path,"K_1.csv"), [], [], "double" , [] , [2 1 3 2] );
expected = [
0.10000000000000001 1.1000000000000001
0.10000000000000001 0.10000000000000001
];
myassert_checkequal ( A , expected );

