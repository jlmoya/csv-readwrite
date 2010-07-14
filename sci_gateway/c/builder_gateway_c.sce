// This file is released into the public domain

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

tbx_build_gateway("csvreadwrite_c", ..
                  ["csv_read","sci_csv_read";"csv_write","sci_csv_write"], ..
                  ["sci_csv_read.c","sci_csv_write.c"], ..
                  get_absolute_file_path("builder_gateway_c.sce"), ..
                  ["../../src/c/libcsv_readwrite"], ..
                  "", ..
                  includes_src_c);

clear WITHOUT_AUTO_PUTLHSVAR;

clear tbx_build_gateway;
