//
//  Copyright (C) 2010 - 2012 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

mode(-1);
lines(0);

TOOLBOX_NAME  = "csv_readwrite";
TOOLBOX_TITLE = "CSV read write files";
toolbox_dir   = get_absolute_file_path("builder.sce");

// Check Scilab's version
// =============================================================================

try
    v = getversion("scilab");
catch
    error(gettext("Scilab 5.4 or more is required."));
end

// Scilab 2027+ uses a year-based major version (v(1)=2027, v(2)=minor), so
// comparing v(2) against the old "5.4" scheme (v(1)=5, v(2)=4) misfires here
// (v(2)=0 < 4) and incorrectly rejects a perfectly modern Scilab. Compare
// against v(1) instead: this still rejects genuinely old Scilab (<5.x) while
// accepting both the legacy 5.x/6.x scheme and the new year-based scheme.
if v(1) < 5 then
    error(gettext('Scilab 5.4 or more is required.'));
end
clear v;

// Check modules_manager module availability
// =============================================================================

if ~isdef('tbx_build_loader') then
  error(msprintf(gettext('%s module not installed.'), 'modules_manager'));
end

// Action
// =============================================================================
tbx_builder_src(toolbox_dir);
tbx_builder_gateway(toolbox_dir);
tbx_builder_macros(toolbox_dir);
tbx_builder_help(toolbox_dir);
tbx_build_loader(TOOLBOX_NAME, toolbox_dir);
tbx_build_cleaner(TOOLBOX_NAME, toolbox_dir);

// Clean variables
// =============================================================================

clear toolbox_dir TOOLBOX_NAME TOOLBOX_TITLE;

