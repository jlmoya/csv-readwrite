// CORNET Allan - DIGITEO - 2010

if getos() == "Windows" then
    // to manage long pathname
    includes_src_c = "-I""" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c""";
else
    includes_src_c = "-I" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c";
end

// PutLhsVar managed by user in sci_sum and in sci_sub
// if you do not this variable, PutLhsVar is added
// in gateway generated (default mode in scilab 4.x and 5.x)
WITHOUT_AUTO_PUTLHSVAR = %t;

table_functions = ["csv_read","sci_csv_read"; ..
                   "csv_write","sci_csv_write"; ..
                   "csv_textscan","sci_csv_textscan"; ..
                   "csv_default","sci_csv_default"];
                   
src_functions = ["sci_csv_read.c", ..
                 "sci_csv_write.c", ..
                 "sci_csv_textscan.c", ..
                 "sci_csv_default.c"];

tbx_build_gateway("csvreadwrite_c", ..
                  table_functions, ..
                  src_functions, ..
                  get_absolute_file_path("builder_gateway_c.sce"), ..
                  ["../../src/c/libcsv_readwrite"], ..
                  "", ..
                  includes_src_c);

clear WITHOUT_AUTO_PUTLHSVAR;

clear tbx_build_gateway;
