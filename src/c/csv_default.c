/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include <string.h>
#include "csv_default.h"
#include "MALLOC.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
/* ========================================================================== */
#define DEFAULT_CSV_SEPARATOR ","
#define DEFAULT_CSV_DECIMAL "."
#define CSV_DECIMAL_MODE_1 DEFAULT_CSV_DECIMAL
#define CSV_DECIMAL_MODE_2 ","
#define DEFAULT_CSV_CONVERSION "string"
#define CSV_CONVERSION_MODE_1 DEFAULT_CSV_CONVERSION
#define CSV_CONVERSION_MODE_2 "double"
/* ========================================================================== */
static char *defaultCsvSeparator = NULL;
static char *defaultCsvDecimal = NULL;
static char *defaultCsvConversion = NULL;
/* ========================================================================== */
static int initializeCsvDefaultValues(void);
/* ========================================================================== */
const char *getCsvDefaultSeparator(void)
{
    initializeCsvDefaultValues();
    return defaultCsvSeparator;
}
/* ========================================================================== */
const char *getCsvDefaultDecimal(void)
{
    initializeCsvDefaultValues();
    return defaultCsvDecimal;
}
/* ========================================================================== */
const char *getCsvDefaultConversion(void)
{
    initializeCsvDefaultValues();
    return defaultCsvConversion;
}
/* ========================================================================== */
int setCsvDefaultSeparator(const char *separator)
{
    if (initializeCsvDefaultValues()) return 1;
    if (separator == NULL) return 1;

    if (strcmp(separator, getCsvDefaultDecimal()) == 0) return 1;

    defaultCsvSeparator = strdup(separator);
    if (defaultCsvSeparator == NULL) return 1;

    return 0;
}
/* ========================================================================== */
int setCsvDefaultDecimal(const char *decimal)
{
    if (initializeCsvDefaultValues()) return 1;
    if (decimal == NULL) return 1;

    /* decimal separator supported . and , */
    if ((strcmp(decimal, CSV_DECIMAL_MODE_1) == 0) ||
        (strcmp(decimal, CSV_DECIMAL_MODE_2) == 0))
    {
        if (strcmp(decimal, getCsvDefaultSeparator()) == 0) return 1;
        defaultCsvDecimal = strdup(decimal);    
        if (defaultCsvDecimal == NULL) return 1;
        return 0;
    }
    return 1;
}
/* ========================================================================== */
int setCsvDefaultConversion(const char *conversion)
{
    if (initializeCsvDefaultValues()) return 1;
    if (conversion == NULL) return 1;

    if ((strcmp(conversion, CSV_CONVERSION_MODE_1) == 0) ||
        (strcmp(conversion, CSV_CONVERSION_MODE_2) == 0))
    {
        if (defaultCsvConversion) FREE(defaultCsvConversion);
        defaultCsvConversion = strdup(conversion);
        if (defaultCsvConversion) return 0;
    }

    return 1;
}
/* ========================================================================== */
static int initializeCsvDefaultValues(void)
{
    if (defaultCsvSeparator == NULL)
    {
        defaultCsvSeparator = strdup(DEFAULT_CSV_SEPARATOR);
    }

    if (defaultCsvDecimal == NULL)
    {
        defaultCsvDecimal = strdup(DEFAULT_CSV_DECIMAL);
    }

    if (defaultCsvConversion == NULL)
    {
        defaultCsvConversion = strdup(DEFAULT_CSV_CONVERSION);
    }

    if ((defaultCsvSeparator == NULL) ||
        (defaultCsvDecimal == NULL) ||
        (defaultCsvConversion == NULL))
    {
        return 1;
    }

    return 0;
}
/* ========================================================================== */
int setCsvDefaultReset(void)
{
    if (defaultCsvSeparator) {FREE(defaultCsvSeparator); defaultCsvSeparator = NULL;}
    if (defaultCsvDecimal) {FREE(defaultCsvDecimal); defaultCsvDecimal = NULL;}
    if (defaultCsvConversion) {FREE(defaultCsvConversion); defaultCsvConversion = NULL;}
    return initializeCsvDefaultValues;
}
/* ========================================================================== */
