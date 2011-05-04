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

// <-- Non-regression test for bug 360 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/360/
//
// <-- Short Description -->
// The csv_read function does not manage the range.

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));

//
// Read complex doubles with csv_textscan
Astr = mgetl(fullfile(path,"complexdata.csv"));
r = csv_textscan(Astr,[],[],"double");
expected = [
%nan
%nan
];
myassert_checkequal ( r , expected );

//
// Read complex doubles with csv_read
r = csv_read(fullfile(path,"complexdata.csv"), [], [], "double" );
expected = [
%nan
%nan
];
myassert_checkequal ( r , expected );
//
// Configure the separator
r = csv_textscan(Astr," ",[],"double");
expected = [6+3*%i 13-7*%i 20+4*%i 27-1.5*%i 34+3.14*%i 41-3*%i 48+3*%i 55-7*%i
                +0      -0    %inf     -%inf       %nan 1.D+308 1.e-308 1.e-323];
myassert_checkequal ( r , expected );

