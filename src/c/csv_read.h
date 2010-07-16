/* ==================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ==================================================================== */
#ifndef __CSV_READ_H__
#define __CSV_READ_H__

typedef enum {
    CSV_READ_NO_ERROR = 0,
    CSV_READ_MOPEN_ERROR = 1,
    CSV_READ_FILE_NOT_EXIST = 2,
    CSV_READ_MEMORY_ALLOCATION = 3,
    CSV_READ_READLINES_ERROR = 4,
    CSV_READ_COLUMNS_ERROR = 5,
    CSV_READ_ERROR = 6,
    CSV_READ_SEPARATOR_DECIMAL_EQUAL = 7
} csvReadError;

#define DEFAULT_CSV_READ_SEPARATOR ","
#define DEFAULT_CSV_READ_DECIMAL "."

typedef struct {
    char **pstrValues;
    int m;
    int n;
    csvReadError err;
} csvResult;

csvResult* csv_read(char *filename, char *separator, char *decimal);

void freeCsvResult(csvResult *result);

#endif /* __CSV_READ_H__ */

