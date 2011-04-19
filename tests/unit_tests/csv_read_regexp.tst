//
//  Copyright (C) 2011 - DIGITEO - Michael Baudin
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//


// <-- JVM NOT MANDATORY -->

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));
exec(fullfile(path,"myassert_checkfilesequal.sci"));

filename = fullfile(path, "csv_regexp.csv");
[y, x] = csv_read(filename, [], [], [], [], "/\/\//");
ref_x = ["// tata"; ..
         "// titi"; ..
         "// toto"; ..
         "// tutu"];
ref_y = [    1.    0.    0.    0.    0.  ; ..
             0.    1.    0.    0.    0.  ; ..
             0.    0.    1.    0.    0.];

Myassert_checkequal (ref_x , x);
Myassert_checkequal (ref_y , y);