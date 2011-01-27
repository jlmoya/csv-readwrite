// =============================================================================
// Allan CORNET - DIGITEO - 2010 - 2011
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
M = eye(100, 100);
csv_write(M, TMPDIR + "/csv_write_M_1.csv");
if ~isfile(TMPDIR + "/csv_write_M_1.csv") then pause, end
// =============================================================================
csv_write(M, TMPDIR + "/csv_write_M_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_M_2.csv") then pause, end
// =============================================================================
csv_write(M, TMPDIR + "/csv_write_M_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_M_3.csv") then pause, end
// =============================================================================
csv_write(M, TMPDIR + "/csv_write_M_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_M_4.csv") then pause, end
// =============================================================================
N = [%nan , 1, %nan ; -%inf , %inf, 4];
csv_write(N, TMPDIR + "/csv_write_N_1.csv");
if ~isfile(TMPDIR + "/csv_write_N_1.csv") then pause, end
// =============================================================================
csv_write(N, TMPDIR + "/csv_write_N_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_N_2.csv") then pause, end
// =============================================================================
csv_write(N, TMPDIR + "/csv_write_N_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_N_3.csv") then pause, end
// =============================================================================
csv_write(N, TMPDIR + "/csv_write_N_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_N_4.csv") then pause, end
// =============================================================================
K = eye(100, 100) + 0.1;
csv_write(K, TMPDIR + "/csv_write_K_1.csv");
if ~isfile(TMPDIR + "/csv_write_K_1.csv") then pause, end
// =============================================================================
csv_write(K, TMPDIR + "/csv_write_K_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_K_2.csv") then pause, end
// =============================================================================
csv_write(K, TMPDIR + "/csv_write_K_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_K_3.csv") then pause, end
// =============================================================================
csv_write(K, TMPDIR + "/csv_write_K_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_K_4.csv") then pause, end
// =============================================================================
S = ['Allan', '2', 'CORNET';
     'csv read/write toolbox', '3','for scilab'];
// =============================================================================
csv_write(S, TMPDIR + "/csv_write_S_1.csv", "|");
if ~isfile(TMPDIR + "/csv_write_S_1.csv") then pause, end
// =============================================================================
csv_write(S, TMPDIR + "/csv_write_S_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_S_2.csv") then pause, end
// =============================================================================
csv_write(S, TMPDIR + "/csv_write_S_3.csv", "!", ",");
if ~isfile(TMPDIR + "/csv_write_S_3.csv") then pause, end
// =============================================================================
csv_write(S, TMPDIR + "/csv_write_S_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_S_4.csv") then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_M_1.csv");
if ~and(r == string(M)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_M_2.csv", ascii(9));
if ~and(r == string(M)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_M_3.csv", " ", ",");
if ~and(r == string(M)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_M_4.csv", ";", ",");
if ~and(r == string(M)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_N_1.csv");
if ~and(r == string(N)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_N_2.csv", ascii(9));
if ~and(r == string(N)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_N_3.csv", " ", ",");
if ~and(r == string(N)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_N_4.csv", ";", ",");
if ~and(r == string(N)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_K_1.csv");
r = csv_read(TMPDIR + "/csv_write_K_2.csv", ascii(9));
r = csv_read(TMPDIR + "/csv_write_K_3.csv", " ", ",");
r = csv_read(TMPDIR + "/csv_write_K_4.csv", ";", ",");
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_1.csv", "|");
if ~and(r == string(S)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_2.csv", ascii(9));
if ~and(r == string(S)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_3.csv", "!", ",");
if ~and(r == string(S)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_4.csv", ";", ",");
if ~and(r == string(S)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_1.csv", "|", ".", "string");
if ~and(r == string(S)) then pause, end
// =============================================================================
r = csv_read(TMPDIR + "/csv_write_S_1.csv", "|", ".", "double");
ref = [%nan , 2, %nan; %nan, 3, %nan];
if ~isnan(r(1,1)) then pause, end
if r(1,2) <> 2 then pause, end
if ~isnan(r(1,3)) then pause, end
if ~isnan(r(2,1)) then pause, end
if r(2,2) <> 3 then pause, end
if ~isnan(r(2,3)) then pause, end
// =============================================================================
M = [%inf, %nan];
filename = fullfile(TMPDIR,'datas.csv');
csv_write(M, filename);
mgetl(filename)
N = csv_read(filename,",",".","double",["Nan", "0"]);
if N(1,1) <> %inf then pause, end 
if N(1,2) <> 0 then pause, end
// =============================================================================