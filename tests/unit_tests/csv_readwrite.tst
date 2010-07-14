
M = eye(100, 100);
csv_write(M, TMPDIR + "/csv_write_M_1.csv");
if ~isfile(TMPDIR + "/csv_write_M_1.csv") then pause, end

csv_write(M, TMPDIR + "/csv_write_M_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_M_2.csv") then pause, end

csv_write(M, TMPDIR + "/csv_write_M_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_M_3.csv") then pause, end

csv_write(M, TMPDIR + "/csv_write_M_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_M_4.csv") then pause, end


N = [%nan , 1, %nan ; -%inf , %inf, 4];
csv_write(N, TMPDIR + "/csv_write_N_1.csv");
if ~isfile(TMPDIR + "/csv_write_N_1.csv") then pause, end

csv_write(N, TMPDIR + "/csv_write_N_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_N_2.csv") then pause, end

csv_write(N, TMPDIR + "/csv_write_N_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_N_3.csv") then pause, end

csv_write(N, TMPDIR + "/csv_write_N_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_N_4.csv") then pause, end

K = eye(100, 100) + 0.1;
csv_write(K, TMPDIR + "/csv_write_K_1.csv");
if ~isfile(TMPDIR + "/csv_write_K_1.csv") then pause, end

csv_write(K, TMPDIR + "/csv_write_K_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_K_2.csv") then pause, end

csv_write(K, TMPDIR + "/csv_write_K_3.csv", " ", ",");
if ~isfile(TMPDIR + "/csv_write_K_3.csv") then pause, end

csv_write(K, TMPDIR + "/csv_write_K_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_K_4.csv") then pause, end

S = ['Allan', 'CORNET';
     'csv read/write toolbox', 'for scilab'];

csv_write(S, TMPDIR + "/csv_write_S_1.csv", "|");
if ~isfile(TMPDIR + "/csv_write_S_1.csv") then pause, end

csv_write(S, TMPDIR + "/csv_write_S_2.csv", ascii(9));
if ~isfile(TMPDIR + "/csv_write_S_2.csv") then pause, end

csv_write(S, TMPDIR + "/csv_write_S_3.csv", "!", ",");
if ~isfile(TMPDIR + "/csv_write_S_3.csv") then pause, end

csv_write(S, TMPDIR + "/csv_write_S_4.csv", ";", ",");
if ~isfile(TMPDIR + "/csv_write_S_4.csv") then pause, end

r = csv_read(TMPDIR + "/csv_write_M_1.csv");
r = csv_read(TMPDIR + "/csv_write_M_2.csv", ascii(9));
r = csv_read(TMPDIR + "/csv_write_M_3.csv", " ", ",");
r = csv_read(TMPDIR + "/csv_write_M_4.csv", ";", ",");
r = csv_read(TMPDIR + "/csv_write_N_1.csv");
r = csv_read(TMPDIR + "/csv_write_N_2.csv", ascii(9));
r = csv_read(TMPDIR + "/csv_write_N_3.csv", " ", ",");
r = csv_read(TMPDIR + "/csv_write_N_4.csv", ";", ",");
r = csv_read(TMPDIR + "/csv_write_K_1.csv");
r = csv_read(TMPDIR + "/csv_write_K_2.csv", ascii(9));
r = csv_read(TMPDIR + "/csv_write_K_3.csv", " ", ",");
r = csv_read(TMPDIR + "/csv_write_K_4.csv", ";", ",");
r = csv_read(TMPDIR + "/csv_write_S_1.csv", "|");
r = csv_read(TMPDIR + "/csv_write_S_2.csv", ascii(9));
r = csv_read(TMPDIR + "/csv_write_S_3.csv", "!", ",");
r = csv_read(TMPDIR + "/csv_write_S_4.csv", ";", ",");
