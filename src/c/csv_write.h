/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 - 2011 */
/* ========================================================================== */
#ifndef __CSV_WRITE_H__
#define __CSV_WRITE_H__

typedef enum {
    CSV_WRITE_NO_ERROR = 0,
    CSV_WRITE_FOPEN_ERROR = 1,
    CSV_WRITE_ERROR = 2,
    CSV_WRITE_SEPARATOR_DECIMAL_EQUAL = 3
} csvWriteError;


csvWriteError csv_write_double(const char *filename,
                               const double *pdValues, int m, int n,
                               const char *separator,
                               const char *decimal,
                               const char *precisionFormat,
                               const char **headersLines,
                               int nbHeadersLines);
                               
csvWriteError csv_write_complex(const char *filename,
                               const double *pdValuesReal,
                               const double *pdValuesImag,
                               int m, int n,
                               const char *separator,
                               const char *decimal,
                               const char *precisionFormat,
                               const char **headersLines,
                               int nbHeadersLines);

csvWriteError csv_write_string(const char *filename,
                               const char **pStrValues, int m, int n,
                               const char *separator,
                               const char *decimal,
                               const char **headersLines,
                               int nbHeadersLines);
#endif /* __CSV_WRITE_H__ */
/* ========================================================================== */

