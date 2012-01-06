//  Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET
//  Copyright (C) 2011 - DIGITEO - Michael Baudin
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
demopath = get_absolute_file_path("csv_readwrite.dem.gateway.sce");
subdemolist = [
"csv_readwrite basic demos", "csv_readwrite.dem.sce"; ..
"benchmark csv read/write", "benchmark_1.sce"; ..
"benchmark csv_isnum", "benchmark_2.sce"; ..
];
subdemolist(:,2) = demopath + subdemolist(:,2)
