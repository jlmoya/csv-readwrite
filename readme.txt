readme.txt of the csv_readwrite module

fast dedicated scilab functions to read and write csv files

To compare speed:

with default scilab functions:
stacksize('max');
M = ones(1000, 1000);

timer();
write_csv(M, TMPDIR + "/csv_write_1.csv");
timer()

timer();
r = read_csv(TMPDIR + "/csv_write_1.csv")
timer()


with optimized functions:

stacksize('max');
M = ones(1000, 1000);

timer();
csv_write(M, TMPDIR + "/csv_write_1.csv");
timer()

timer();
r = csv_read(TMPDIR + "/csv_write_1.csv");
timer()

Allan CORNET - 2010


