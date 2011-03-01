// Copyright (C) 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2010-2011 - DIGITEO - Allan Cornet
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// To compare speed (x100 faster):

// with default scilab functions:
stacksize('max');
M = ones(1000, 1000);

mprintf("Writing with write_csv...\n");
tic();
write_csv(M, TMPDIR + "/csv_write_1.csv");
tt = timer();
mprintf("Time = %.2f (s)\n",tt);

mprintf("Reading with read_csv...\n");
timer();
r = read_csv(TMPDIR + "/csv_write_1.csv")
tt = timer()
mprintf("Time = %.2f (s)\n",tt);


// with optimized functions:

mprintf("Writing with csv_write...\n");
stacksize('max');
M = ones(1000, 1000);

timer();
csv_write(M, TMPDIR + "/csv_write_1.csv");
tt = timer();
mprintf("Time = %.2f (s)\n",tt);

mprintf("Reading with csv_read...\n");
timer();
r = csv_read(TMPDIR + "/csv_write_1.csv");
tt = timer();
mprintf("Time = %.2f (s)\n",tt);

//
// Load this script into the editor
//
filename = "benchmark.sce";
dname = get_absolute_file_path(filename);
editor ( fullfile(dname,filename) );
