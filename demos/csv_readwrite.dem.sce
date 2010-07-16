stacksize('max');
// =============================================================================
M = eye(5, 5);
disp("Initial data:");
disp(M);
csv_write(M, TMPDIR + "/csv_write_M_1.csv", " ", ".");
disp("file result:");
disp(mgetl(TMPDIR + "/csv_write_M_1.csv"));
// =============================================================================
r1 = csv_read(TMPDIR + "/csv_write_M_1.csv",  " ", ".", "string");
disp("result as string by csv_read:");
disp(r1);
// =============================================================================
r2 = csv_read(TMPDIR + "/csv_write_M_1.csv",  " ", ".", "double");
disp("result as double by csv_read:");
disp(r2);
// =============================================================================
S = ['Allan', '2', 'CORNET';
     'csv read/write toolbox', '3','for scilab'];
disp("Initial data:");
disp(S);     
csv_write(S, TMPDIR + "/csv_write_S_1.csv", ";", ".");
disp("file result:");
disp(mgetl(TMPDIR + "/csv_write_S_1.csv"));
// =============================================================================
s1 = csv_read(TMPDIR + "/csv_write_S_1.csv",  ";", ".", "string");
disp("result as string by csv_read:");
disp(s1);
// =============================================================================
s2 = csv_read(TMPDIR + "/csv_write_S_1.csv",  ";", ".", "double");
disp("result as string by csv_read:");
disp(s2);
// =============================================================================

