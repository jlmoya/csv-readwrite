// Copyright (C) 2010 - DIGITEO - Allan CORNET
//

demopath = get_absolute_file_path("csv_readwrite.dem.gateway.sce");

subdemolist = ["demo csv read/write"             ,"csv_readwrite.dem.sce"];

subdemolist(:,2) = demopath + subdemolist(:,2);
