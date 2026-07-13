// Copyright (C) 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2010-2011 - DIGITEO - Allan Cornet
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// To compare speed:

// stacksize('max');  // stacksize() was removed in Scilab 6 (memory is dynamic now)

function demo_bench_csv_1()

// with default scilab functions:
M = ones(1000, 1000);

mprintf("\nWriting with write_csv...\n");
tic();
write_csv(M, TMPDIR + "/csv_write_1.csv");
tt1 = toc();
mprintf("Time = %.2f (s)\n", tt1);

mprintf("Reading with read_csv...\n");
tic();
r = read_csv(TMPDIR + "/csv_write_1.csv")
tt2 = toc()
mprintf("Time = %.2f (s)\n", tt2);


// with optimized functions:

mprintf("Writing with csv_write...\n");

tic();
csv_write(M, TMPDIR + "/csv_write_1.csv");
tt3 = toc();
mprintf("Time = %.2f (s)\n", tt3);

mprintf("Reading with csv_read...\n");
tic();
r = csv_read(TMPDIR + "/csv_write_1.csv", [], [], 'string');
tt4 = toc();
mprintf("Time = %.2f (s)\n", tt4);

mprintf("Reading with read_csv and conversion to double...\n");
tic();
r = evstr(read_csv(TMPDIR + "/csv_write_1.csv"));
tt5 = toc()
mprintf("Time = %.2f (s)\n", tt5);

mprintf("Reading with csv_read and conversion to double...\n");
tic();
r = csv_read(TMPDIR + "/csv_write_1.csv", [], [], 'double');
tt6 = toc();
mprintf("Time = %.2f (s)\n", tt6);


mprintf("\ncsv_write is x%d faster than write_csv.\n", double(tt1/tt3));
mprintf("csv_read is x%d faster than read_csv.\n", double(tt2/tt4));
mprintf("csv_read (with conversion to double) is x%d faster than read_csv.\n\n", double(tt5/tt6));


//
// Load this script into the editor
//
filename = "benchmark_1.sce";
dname = get_absolute_file_path(filename);
editor ( fullfile(dname,filename) , 'readonly' );

endfunction

demo_bench_csv_1();
clear demo_bench_csv_1;
