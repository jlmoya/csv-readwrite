// Copyright (C) 2008 - 2010 - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//
// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 350 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/350/
//
// <-- Short Description -->
// The csv_stringtodouble function always returns complex doubles.

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));

r = csv_stringtodouble("12");
myassert_checkequal ( isreal(r) , %t );


