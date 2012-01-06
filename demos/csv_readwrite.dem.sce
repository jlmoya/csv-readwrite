// Copyright (C) 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2010-2011 - DIGITEO - Allan Cornet
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// =============================================================================
stacksize('max');

function csv_demo_basic()

// =============================================================================
M = eye(5, 5);
disp("Initial data:");
disp(M);
csv_write(M, TMPDIR + "/csv_write_M_1.csv", " ", ".");
disp("file result:");
disp(mgetl(TMPDIR + "/csv_write_M_1.csv"));
// =============================================================================
r1 = csv_read(TMPDIR + "/csv_write_M_1.csv",  " ", ".", "string");
disp("result as string by csv_read:");
disp(r1);
// =============================================================================
r2 = csv_read(TMPDIR + "/csv_write_M_1.csv",  " ", ".", "double");
disp("result as double by csv_read:");
disp(r2);
// =============================================================================
S = ['Allan', '2', 'CORNET';
     'csv read/write toolbox', '3','for scilab'];
disp("Initial data:");
disp(S);     
csv_write(S, TMPDIR + "/csv_write_S_1.csv", ";", ".");
disp("file result:");
disp(mgetl(TMPDIR + "/csv_write_S_1.csv"));
// =============================================================================
s1 = csv_read(TMPDIR + "/csv_write_S_1.csv",  ";", ".", "string");
disp("result as string by csv_read:");
disp(s1);
// =============================================================================
s2 = csv_read(TMPDIR + "/csv_write_S_1.csv",  ";", ".", "double");
disp("result as double by csv_read:");
disp(s2);
// =============================================================================
//
// Load this script into the editor
//
filename = "csv_readwrite.dem.sce";
dname = get_absolute_file_path(filename);
editor ( fullfile(dname,filename) , 'readonly' );
// =============================================================================
endfunction

csv_demo_basic()
clear csv_demo_basic;
