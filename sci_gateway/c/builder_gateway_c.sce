//
//  Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

function builder_gateway()

  if getos() == "Windows" then
    // to manage long pathname
    includes_src_c = "-I""" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c""";
  else
    includes_src_c = "-I" + get_absolute_file_path("builder_gateway_c.sce") + "../../src/c";
    includes_src_c = includes_src_c + " -I" + get_absolute_file_path("builder_gateway_c.sce");
 end

  WITHOUT_AUTO_PUTLHSVAR = %t;

  table_functions = ["csv_read","sci_csv_read"; ..
                     "csv_write","sci_csv_write"; ..
                     "csv_textscan","sci_csv_textscan"; ..
                     "csv_stringtodouble","sci_csv_stringtodouble"; ..
                     "csv_default","sci_csv_default"; ..
					 "csv_isnum", "sci_csv_isnum"];

  src_functions = ["sci_csv_read.c", ..
                   "sci_csv_write.c", ..
                   "sci_csv_textscan.c", ..
                   "sci_csv_stringtodouble.c", ..
                   "sci_csv_default.c", ..
				   "sci_csv_isnum.c", ..
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
