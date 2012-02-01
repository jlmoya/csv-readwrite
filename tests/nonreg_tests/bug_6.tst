//
//  Copyright (C) 2010 - 2012 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

// =============================================================================
M = rand(4,3);
csv_write(M, TMPDIR + '/csvlist.dat');
r = csv_read(TMPDIR + '/csvlist.dat',csv_default('separator'), csv_default('decimal'), 'double');
assert_checkalmostequal(M, r);
// =============================================================================
