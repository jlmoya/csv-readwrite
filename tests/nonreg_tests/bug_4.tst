//
//  Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

// =============================================================================
r1_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_longline_1.csv", ",", [], "string");
r2_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_longline_2.csv", " ", [], "string");
r3_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_shortline_1.csv", ",", [], "string");
r4_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_shortline_2.csv", " ", [], "string");
// =============================================================================
r1_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_longline_1.csv", ",", ".", "double");
r2_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_longline_2.csv", " ", ".", "double");
r3_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_shortline_1.csv", ",", ".", "double");
r4_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_4_shortline_2.csv", " ", ".", "double");
// =============================================================================
if size(r1_string, "r") <> 1 then pause, end
if size(r1_string, "c") <> 8 then pause, end
// =============================================================================
if size(r2_string, "r") <> 1 then pause, end
if size(r2_string, "c") <> 8 then pause, end
// =============================================================================
if size(r3_string, "r") <> 1 then pause, end
if size(r3_string, "c") <> 7 then pause, end
// =============================================================================
if size(r4_string, "r") <> 1 then pause, end
if size(r4_string, "c") <> 7 then pause, end
// =============================================================================
if size(r1_string, "r") <> size(r1_double, "r") then pause, end
if size(r1_string, "c") <> size(r1_double, "c") then pause, end
// =============================================================================
if size(r2_string, "r") <> size(r2_double, "r") then pause, end
if size(r2_string, "c") <> size(r2_double, "c") then pause, end
// =============================================================================
if size(r3_string, "r") <> size(r3_double, "r") then pause, end
if size(r3_string, "c") <> size(r3_double, "c") then pause, end
// =============================================================================
if size(r4_string, "r") <> size(r4_double, "r") then pause, end
if size(r4_string, "c") <> size(r4_double, "c") then pause, end
// =============================================================================
ref_longline_1 = ["-2.790381273096156e-07" , "3.794290569878876e-07" , ..
                  "1.102895012074256e-06"  , "1.632322210513841e-06" , ..
                  "1.777203879921258e-06"  , "1.486206657150863e-06" , ..
                  "8.635378410712134e-07"  , "1.322840799913625e-07"];
if ~and(ref_longline_1 == r1_string) then pause, end
// =============================================================================
ref_longline_2 = ["-2.790381273096156e-07" , "3.794290569878876e-07" , ..
                  "1.102895012074256e-06"  , "1.632322210513841e-06" , ..
                  "1.777203879921258e-06"  , "1.486206657150863e-06" , ..
                  "8.635378410712134e-07"  , "1.322840799913625e-07"];
if ~and(ref_longline_2 == r2_string) then pause, end
// =============================================================================
ref_shortline_1 = ["-2.790381273096156e-07" , "3.794290569878876e-07" , ..
                   "1.102895012074256e-06"  , "1.632322210513841e-06" , ..
                   "1.777203879921258e-06"  , "1.486206657150863e-06" , ..
                   "8.635378410712134e-07"];
if ~and(ref_shortline_1 == r3_string) then pause, end
// =============================================================================
ref_shortline_2 = ["-2.790381273096156e-07" , "3.794290569878876e-07" , ..
                   "1.102895012074256e-06"  , "1.632322210513841e-06" , ..
                   "1.777203879921258e-06"  , "1.486206657150863e-06" , ..
                   "8.635378410712134e-07"];
if ~and(ref_shortline_2 == r4_string) then pause, end
// =============================================================================
