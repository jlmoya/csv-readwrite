// Copyright (C) 2010-2011 - DIGITEO - Allan Cornet
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// To compare speed (x100 faster) of csv_isnum:

// stacksize('max');  // stacksize() was removed in Scilab 6 (memory is dynamic now)

function demo_bench_csv_2()

M = string(ones(100, 1000));

// with default scilab functions:

mprintf("\nBench with isnum (Please waiting) ...\n");
tic();
R = isnum(M);
tt1 = toc();
mprintf("Time = %.2f (s)\n", tt1);

// with optimized functions:

mprintf("Bench with csv_isnum ...\n");


tic();
R = csv_isnum(M);
tt2 = toc();
mprintf("Time = %.2f (s)\n", tt2);

mprintf("\ncsv_isnum is x%d faster than isnum.\n\n", double(tt1/tt2));

//
// Load this script into the editor
//
filename = "benchmark_2.sce";
dname = get_absolute_file_path(filename);
editor ( fullfile(dname,filename) , 'readonly' );

endfunction

demo_bench_csv_2()
clear demo_bench_csv_2;
