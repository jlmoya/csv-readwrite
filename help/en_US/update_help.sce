// Copyright (C) 2010 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

// Updates the .xml files by deleting existing files and 
// creating them again from the .sci with help_from_sci.

//
cwd = get_absolute_file_path("update_help.sce");
//
// Generate the static functions help
helpdir = fullfile(cwd);
funmat = [
  "csv_getToolboxPath"
  ];
macrosdir = fullfile(cwd,"..","..","macros");
demosdir = fullfile(cwd,"..","..","demos");
modulename = "csv_readwrite";
helptbx_helpupdate ( funmat , helpdir , macrosdir , demosdir , modulename , %t )

