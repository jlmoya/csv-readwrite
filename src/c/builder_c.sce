// Allan CORNET - DIGITEO - 2010 - 2011

src_c_path = get_absolute_file_path("builder_c.sce");

fileio_includes = SCI + '/modules/fileio/includes';
fileio_src = SCI + '/modules/fileio/src/c';

if ~isdir(fileio_includes) | ~isdir(fileio_src) then
  error("it requires a local built of Scilab");
end

LIBS = "";

if getos() == "Windows" then
  LIBS = SCI + '/bin/fileio';
end

CFLAGS = "-I" + src_c_path + " -I" + fileio_includes + " -I" + fileio_src;

files_src = ["csv_read.c", ..
             "csv_write.c", ..
             "csv_strsubst.c", ..
             "splitLine.c", ..
             "stringToDouble.c", ..
             "stringToComplex.c", ..
             "checkCsvWriteFormat.c", ..
             "getRange.c", ..
             "csv_default.c"];

functions_c = ["csv_read", "csv_write", "strsubst", "splitLine", "stringToDouble", ..
               "stringToComplex", "csv_default", "checkCsvWriteFormat", "getRange"];

tbx_build_src(functions_c, ..
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
