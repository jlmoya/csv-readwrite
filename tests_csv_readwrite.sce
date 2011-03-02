// ====================================================================
// Allan CORNET
// DIGITEO 2010
// ====================================================================
create_refs = %f;
// ====================================================================
if create_refs then
  tests = [findfiles(csv_getToolboxPath() + '/tests/nonreg_tests', '*.tst'); ..
           findfiles(csv_getToolboxPath() + '/tests/unit_tests', '*.tst')];
  tests = strsubst(tests, ".tst", "");
  
  for i = 1: size(tests, "*");
    test_run(csv_getToolboxPath(), tests(i), "create_ref");
  end
else
  test_run(csv_getToolboxPath());
end
// ====================================================================
