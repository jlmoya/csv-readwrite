// Copyright (C) 2008 - 2011 - Allan CORNET
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//
// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 299 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/299/
//
// <-- Short Description -->
// extends format to digit in csv_default and csv_write


 assert_checkequal(csv_default("precision"), "%.17lg");
 assert_checkequal(csv_default("precision","%.17lg") , %T);
 
 assert_checkequal(csv_default("precision",4), %T);
 assert_checkequal(csv_default("precision"), "%.4lg");
 
 M = rand(2,3);
 filename = fullfile(TMPDIR, "datas.csv");
 csv_write(M, filename,[],[],"%.8e");
 csv_write(M, filename,[],[],8);
 
 assert_checkequal(execstr("csv_write(M, filename,[],[],19)", "errcatch"), 999);
 