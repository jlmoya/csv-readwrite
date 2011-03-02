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
// <-- LONG TIME EXECUTION -->
//
// <-- Non-regression test for bug 194 -->
//
// <-- URL -->
// http://forge.scilab.org/index.php/p/csv-readwrite/issues/194/
//
// <-- Short Description -->
// csv_read may fail on large files.

filename = fullfile(TMPDIR, "prices.csv");
mprintf("File=%s\n",filename);
fd = mopen(filename,"w");
imax=1800000;
for i= 1:imax
  if ( modulo(i,10000)==0 ) then
    mprintf("i=%d, p=%.1f%%\n",i,i/imax*100)
  end
  mputl("02/05/10 00:00:02,1.32453,1.32491",fd); 
end
mclose(fd);

if execstr("M = csv_read(filename,[],[],""string"");", "errcatch") <> 17 then pause, end
stacksize('max');
if execstr("M = csv_read(filename,[],[],""string"");", "errcatch") <> 0 then pause, end
clear M
