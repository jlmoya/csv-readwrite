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

// <-- Non-regression test for bug 352 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/352/
//
// <-- Short Description -->
// The csv_textscan function always returned complex matrices.

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));

//
// Read only rows/columns in range
Astr = [
"1,8,15,22,29,36,43,50"
"2,9,16,23,30,37,44,51"
"3,10,17,6,31,38,45,52"
"4,11,18,25,32,39,46,53"
"5,12,19,26,33,40,47,54"
"6,13,20,27,34,41,48,55"
"+0,-0,Inf,-Inf,Nan,1.D+308,1.e-308,1.e-323"
];
A = csv_textscan ( Astr,[],[],"double" );
expected = [
1 8 15 22 29 36 43 50
2 9 16 23 30 37 44 51
3 10 17 6 31 38 45 52
4 11 18 25 32 39 46 53
5 12 19 26 33 40 47 54
6 13 20 27 34 41 48 55
+0 -0 %inf -%inf %nan 1.D+308 1.e-308 1.e-323
];
myassert_checkequal ( isreal(A) , %t );

//
// Read only rows/columns in range
Astr = [
"1,8,15,22,29,36,43,50"
"2,9,16,23,30,37,44,51"
"3,10,17,6,31,38,45,52"
"4,11,18,25,32,39,46,53"
"5,12,19,26,33,40,47,54"
"6,13,20,27,34,41,48,55"
"+0,-0,Inf,-Inf,Nan,1.D+308,1.e-308,1.e-323"
];
A = csv_textscan ( Astr,[],[],"double",[2 3 5 6]' );
expected = [
 16 23 30 37
 17 6  31 38
 18 25 32 39
 19 26 33 40
];
myassert_checkequal ( isreal(A) , %t );

