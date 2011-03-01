mode(-1)
// ====================================================================
// Copyright (C) INRIA -  Serge Steer
// 
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at    
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// ====================================================================
src_path=get_absolute_file_path('cleaner_src.sce');
exec(fullfile(src_path,"c/cleaner.sce"),-1)
clear src_path
