// =============================================================================
// Allan CORNET - DIGITEO - 2010
// =============================================================================
tlbxs = atomsGetInstalled();
if grep(tlbxs, 'csv_readwrite') <> [] then
  atomsLoad("csv_readwrite");
else
  root_path = getenv('CSV_READWRITE_PATH', '');
  if root_path <> '' then 
    exec(root_path + 'loader.sce'); 
  end 
end
// =============================================================================
r1_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_5.csv", ",");
r1_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_5.csv", ",", ".", "double");
// =============================================================================
if size(r1_string, "c") <> size(r1_double, "c") then pause, end
if size(r1_string, "r") <> size(r1_double, "r") then pause, end
// =============================================================================
if size(r1_string, "c") <> 1 then pause, end
if size(r1_string, "r") <> 372 then pause, end
// =============================================================================
if r1_string(1) <> "0" then pause, end
if r1_double(1) <> 0 then pause, end
// =============================================================================
if r1_string(2) <> "-0" then pause, end
if r1_double(2) <> 0 then pause, end
// =============================================================================
if r1_string(3) <> "1e-308" then pause, end
if r1_double(3) <> 1e-308 then pause, end
// =============================================================================
if r1_string(4) <> "1e308" then pause, end
if r1_double(4) <> 1e308 then pause, end
// =============================================================================
if r1_string(372) <> "0.001236" then pause, end
if r1_double(372) <> 0.001236 then pause, end
// =============================================================================
