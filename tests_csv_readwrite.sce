// ====================================================================
// Allan CORNET
// DIGITEO 2010
// ====================================================================
create_refs = %f;
// ====================================================================
current_path = pwd(); 
root_path = get_absolute_file_path('tests_csv_readwrite.sce'); 
exec (root_path + 'loader.sce'); 
setenv('CSV_READWRITE_PATH', root_path); 
// ====================================================================
if create_refs then
  tests = [findfiles(csv_getToolboxPath() + '/tests/nonreg_tests', '*.tst'); ..
           findfiles(csv_getToolboxPath() + '/tests/unit_tests', '*.tst')];
  tests = strsubst(tests, ".tst", "");
  
  for i = 1: size(tests, "*");
    test_run(root_path, tests(i), "create_ref");
  end
else
  test_run(root_path);
end
cd(current_path);
// ====================================================================
clear current_path;
clear root_path;
// ====================================================================
