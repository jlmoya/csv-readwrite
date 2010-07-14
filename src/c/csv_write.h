/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#ifndef __CSV_WRITE_H__
#define __CSV_WRITE_H__

typedef enum {
    CSV_WRITE_NO_ERROR = 0,
    CSV_WRITE_FOPEN_ERROR = 1,
    CSV_WRITE_ERROR = 2,
    CSV_WRITE_SEPARATOR_DECIMAL_EQUAL = 3
} csvWriteError;

#define DEFAULT_CSV_WRITE_SEPARATOR " "
#define DEFAULT_CSV_WRITE_DECIMAL "."

csvWriteError csv_write_double(char *filename,
                               double *pdValues, int m, int n,
                               char *separator,
                               char *decimal);

csvWriteError csv_write_string(char *filename,
                               char **pStrValues, int m, int n,
                               char *separator,
                               char *decimal);

#endif /* __CSV_WRITE_H__ */
/* ========================================================================== */

