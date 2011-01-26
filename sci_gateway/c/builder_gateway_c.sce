// CORNET Allan - DIGITEO - 2010

function builder_gateway()

  if getos() == "Windows" then
    // to manage long pathname
    includes_src_c = "-I""" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c""";
  else
    includes_src_c = "-I" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c";
 end

  WITHOUT_AUTO_PUTLHSVAR = %t;

  table_functions = ["csv_read","sci_csv_read"; ..
                     "csv_write","sci_csv_write"; ..
                     "csv_textscan","sci_csv_textscan"; ..
                     "csv_stringtodouble","sci_csv_stringtodouble"; ..
                     "csv_default","sci_csv_default"];

  src_functions = ["sci_csv_read.c", ..
                   "sci_csv_write.c", ..
                   "sci_csv_textscan.c", ..
                   "sci_csv_stringtodouble.c", ..
                   "sci_csv_default.c", ..
                   "gw_csv_helpers.c"];

  tbx_build_gateway("csvreadwrite_c", ..
                  table_functions, ..
                  src_functions, ..
                  get_absolute_file_path("builder_gateway_c.sce"), ..
                  ["../../src/c/libcsv_readwrite"], ..
                  "", ..
                  includes_src_c);

endfunction

builder_gateway()
clear builder_gateway