// Copyright (C) 2010 - 2011 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//
// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 275 -->
//
// <-- URL -->
//  http://forge.scilab.org/index.php/p/csv-readwrite/issues/275/
//
// <-- Short Description -->
// The default precision is insufficient.

//
// assert_equal --
//   Returns 1 if the two real matrices computed and expected are equal.
// Arguments
//   computed, expected : the two matrices to compare
//   epsilon : a small number
//
function flag = assert_equal ( computed , expected )
    if computed==expected then
        flag = 1;
    else
        flag = 0;
    end
    if flag <> 1 then pause,end
endfunction


function y = writereadcycle(x,filename)
    csv_write(x,filename);
    separator = [];
    decimal=[];
    conversion ="double";
    y = csv_read(filename, separator, decimal, conversion);
endfunction

function tf = checkWriteReadCycle(x,direction,n,filename)
    tf = %t
    for k = 1 : n
        y = writereadcycle(x,filename);
        tf = (x==y);
        if ( ~tf ) then
            break
        end
        x = nearfloat(direction,x);
    end
endfunction

n=1000;
filename = fullfile(TMPDIR,"csv_write_M_1.csv");
tf = checkWriteReadCycle(1,"succ",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(1,"pred",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(0.1,"succ",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(0.1,"pred",100,filename);
assert_equal ( tf , %t );
x = number_properties("huge");
tf = checkWriteReadCycle(x,"succ",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(x,"pred",100,filename);
assert_equal ( tf , %t );
x = number_properties("tiny");
tf = checkWriteReadCycle(x,"succ",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(x,"pred",100,filename);
assert_equal ( tf , %t );
x = number_properties("tiniest");
tf = checkWriteReadCycle(x,"succ",100,filename);
assert_equal ( tf , %t );
tf = checkWriteReadCycle(x,"pred",100,filename);
assert_equal ( tf , %t );

