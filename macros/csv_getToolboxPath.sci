//
//  Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
function path = csv_getToolboxPath()
    // Returns the path to the current module.
    // 
    // Calling Sequence
    //   path = csv_getToolboxPath ( )
    //
    // Parameters
    //   path : a 1-by-1 matrix of strings, the path to the current module.
    //
    // Examples
    //   path = csv_getToolboxPath ( )
    //
    // Authors
    //   Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET

  [fs, path] = libraryinfo("csv_readwritelib");
  path = pathconvert(fullpath(path + "../"), %t, %t);
endfunction


