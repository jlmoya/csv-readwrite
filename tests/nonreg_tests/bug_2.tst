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
r_string = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_2.csv", ",");
r_double = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_2.csv", ",", ".", "double");
if size(r_string, "c") <> size(r_double, "c") then pause, end
if size(r_string, "r") <> size(r_double, "r") then pause, end
if size(r_string, "c") <> 100 then pause, end
if size(r_string, "r") <> 100 then pause, end
if r_string(100, 100) <> '1' then pause,end
if ~and(r_double == eye(100,100)) then pause,end
// =============================================================================
