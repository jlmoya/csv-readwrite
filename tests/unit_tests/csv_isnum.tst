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
// <-- JVM NOT MANDATORY -->
// =============================================================================
assert_checkequal (csv_isnum('%pi'), %t);
assert_checkequal (csv_isnum('1'), %t);
assert_checkequal (csv_isnum('1.2'), %t);
assert_checkequal (csv_isnum('+1.2'), %t);
assert_checkequal (csv_isnum('-1.2'), %t);
assert_checkequal (csv_isnum('1e2'), %t);
assert_checkequal (csv_isnum('1d2'), %t);
assert_checkequal (csv_isnum('1E2'), %t);
assert_checkequal (csv_isnum('1D2'), %t);
assert_checkequal (csv_isnum('1e+2'), %t);
assert_checkequal (csv_isnum('1e-2'), %t);
assert_checkequal (csv_isnum('+1e+2'), %t);
assert_checkequal (csv_isnum('-1e+2'), %t);
assert_checkequal (csv_isnum('-12e+3'), %t);
assert_checkequal (csv_isnum('-1.2e+3'), %t);
assert_checkequal (csv_isnum('-1.2e+345'), %t);
assert_checkequal (csv_isnum('a'), %f);
assert_checkequal (csv_isnum('e'), %f);
assert_checkequal (csv_isnum('d'), %f);
assert_checkequal (csv_isnum('E'), %f);
assert_checkequal (csv_isnum('e'), %f);
assert_checkequal (csv_isnum('-1.2a+345'), %f);
assert_checkequal (csv_isnum('-1.2e+3+45'), %f);
assert_checkequal (csv_isnum('-1.2e+3-45'), %f);
// =============================================================================



