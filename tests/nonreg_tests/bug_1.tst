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
r = csv_read(csv_getToolboxPath() + "tests/nonreg_tests/bug_1.csv", ",");

if size(r, "c") <> 2 then pause, end
if size(r, "r") <> 7534 then pause, end
if r(1,1) <> "Time" then pause, end
if r(1,2) <> "ecart" then pause, end
if r(7534,1) <> "0.05" then pause, end
if r(7534,2) <> "-0.000237359" then pause, end
// =============================================================================
