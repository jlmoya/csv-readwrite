/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#if defined(__linux__)
#define _GNU_SOURCE /* Bug 5673 fix: avoid dependency on GLIBC_2.7 */
#endif
/* ========================================================================== */
#include <stdio.h>
#include <string.h>
#include "csv_write.h"
#include "charEncoding.h"
#include "MALLOC.h"
#include "core_math.h"
#include "BOOL.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "strsubst.h"
#include "expandPathVariable.h"
/* ========================================================================== */
#define DEFAULT_CSV_WRITE_STRING_FORMAT "%s"
#define DEFAULT_CSV_WRITE_DOUBLE_FORMAT "%lg"
#define NanString "Nan"
#define InfString "Inf"
#define NegInfString "-Inf"
#define EMPTY_STRING ""
#if _MSC_VER
    #define MODEFD "wt"
#else
    #define MODEFD "w"
#endif
#define EOL "\n"
/* ========================================================================== */
#ifndef signbit
static int signbit(double x)
{
    union
    {
        double d;
        short s[4];
        int i[2];
    } u;

    u.d = x;
#if SIZEOF_INT == 4
    return u.i[1] < 0;
#else
    return u.s[3] < 0;
#endif
}
#endif /* signbit */
/* ========================================================================== */
csvWriteError csv_write_double(char *filename,
                               double *pdValues, int m, int n,
                               char *separator,
                               char *decimal)
{
    FILE  *fd = NULL;
    int i = 0, j = 0;
    char *expandedFilename = NULL;

    if (filename == NULL) return CSV_WRITE_ERROR;
    if (pdValues == NULL) return CSV_WRITE_ERROR;
    if (m < 0 || n < 0) return CSV_WRITE_ERROR;
    if (separator == NULL) return CSV_WRITE_ERROR;
    if (decimal == NULL) return CSV_WRITE_ERROR;

    if (strcmp(separator, decimal) == 0) return CSV_WRITE_SEPARATOR_DECIMAL_EQUAL;

    expandedFilename = expandPathVariable(filename);
    wcfopen(fd , filename, MODEFD);
    if (expandedFilename) {FREE(expandedFilename); expandedFilename = NULL;}
    if ( fd == (FILE *)NULL ) return CSV_WRITE_FOPEN_ERROR;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (ISNAN(pdValues[i + m*j]))
            {
                fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, NanString);
            }
            else if (finite(pdValues[i + m*j]))
            {
                char buffer[65535];
                char *result = NULL;
                sprintf(buffer, DEFAULT_CSV_WRITE_DOUBLE_FORMAT, pdValues[i + m*j]);
                result = strsubst(buffer, DEFAULT_CSV_WRITE_DECIMAL, decimal);
                if (result)
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, result);
                    FREE(result);
                    result = NULL;
                }
                else
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_DOUBLE_FORMAT, pdValues[i + m*j]);
                }
            }
            else
            {
                if ( signbit(pdValues[i + m*j]) )
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, NegInfString);
                }
                else
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, InfString);
                }
            }
            if (j + 1 < n) fprintf(fd, separator);
        }
        fprintf(fd, EOL);
    }

    fclose(fd);
    return CSV_WRITE_NO_ERROR;
}
/* ========================================================================== */
csvWriteError csv_write_string(char *filename,
                               char **pStrValues, int m, int n,
                               char *separator,
                               char *decimal)
{
    FILE  *fd = NULL;
    int i = 0, j = 0;

    if (filename == NULL) return CSV_WRITE_ERROR;
    if (pStrValues == NULL) return CSV_WRITE_ERROR;
    if (m < 0 || n < 0) return CSV_WRITE_ERROR;
    if (separator == NULL) return CSV_WRITE_ERROR;

    if (strcmp(separator, decimal) == 0) return CSV_WRITE_SEPARATOR_DECIMAL_EQUAL;

    wcfopen(fd , filename, MODEFD);
    if ( fd == (FILE *)NULL ) return CSV_WRITE_FOPEN_ERROR;


   for (i = 0 ; i < m ; i++ )
   {
        for ( j = 0 ; j < n ; j++)
        {
            if (decimal == NULL)
            {
                fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, pStrValues[i + m*j]);
            }
            else
            {
                char *result = NULL;
                result = strsubst(pStrValues[i + m*j], DEFAULT_CSV_WRITE_DECIMAL, decimal);
                if (result)
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, result);
                    FREE(result);
                    result = NULL;
                }
                else
                {
                    fprintf(fd, DEFAULT_CSV_WRITE_STRING_FORMAT, pStrValues[i + m*j]);
                }
            }
            if (j + 1 < n) fprintf(fd, separator);
        }
        fprintf(fd, EOL);
   }

   fclose(fd);
   return CSV_WRITE_NO_ERROR;
}
/* ========================================================================== */
