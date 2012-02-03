//
//  Copyright (C) 2010 - 2012 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

src_c_path = get_absolute_file_path("builder_c.sce");

fileio_includes = SCI + '/modules/fileio/includes';
fileio_src = SCI + '/modules/fileio/src/c';

string_includes = SCI + '/modules/string/includes';
string_src = SCI + '/modules/string/src/c';

if ~isdir(fileio_includes) | ~isdir(fileio_src) then
  error("it requires a local built of Scilab");
end

LIBS = "";

if getos() == "Windows" then
  LIBS = SCI + '/bin/fileio';
  LIBS = [LIBS;SCI + '/bin/string'];
end

CFLAGS = "-I" + src_c_path + " -I" + fileio_includes + " -I" + fileio_src + ..
         " -I" + string_includes + " -I" + string_src;

files_src = ["csv_read.c", ..
             "csv_write.c", ..
             "csv_strsubst.c", ..
             "splitLine.c", ..
             "stringToDouble.c", ..
             "stringsToDoubles.c", ..
             "stringToComplex.c", ..
             "checkCsvWriteFormat.c", ..
             "getRange.c", ..
             "csv_default.c", ..
             "nan.c", ..
             "inf.c", ..
             "csv_complex.c", ..
             "csv_isnum.c", ..
             "latintoutf.c", ..
             "utftolatin.c"];

libfunctions_c = 'csv_readwrite';

tbx_build_src(libfunctions_c, ..
              files_src, ..
              "c", ..             ..
              src_c_path,         ..
              LIBS,                 ..
              "",                 ..
              CFLAGS,             ..
              "",                 ..
              "",                 ..
              'csv_readwrite');

clear tbx_build_src;
clear src_c_path;
clear CFLAGS;
