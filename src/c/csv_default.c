/*
 *  Copyright (C) 2010-2011 - DIGITEO - Allan CORNET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#include <string.h>
#include "csv_default.h"
#include "MALLOC.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "checkCsvWriteFormat.h"
/* ========================================================================== */
#define DEFAULT_CSV_SEPARATOR ","
#define DEFAULT_CSV_DECIMAL "."
#define DEFAULT_CSV_PRECISION "%.17lg"
#define CSV_DECIMAL_MODE_1 DEFAULT_CSV_DECIMAL
#define CSV_DECIMAL_MODE_2 ","
#define DEFAULT_CSV_CONVERSION "double"
#define CSV_CONVERSION_MODE_1 DEFAULT_CSV_CONVERSION
#define CSV_CONVERSION_MODE_2 "string"
/* ========================================================================== */
static char *defaultCsvSeparator = NULL;
static char *defaultCsvDecimal = NULL;
static char *defaultCsvConversion = NULL;
static char *defaultCsvPrecision = NULL;
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
const char *getCsvDefaultPrecision(void)
{
    initializeCsvDefaultValues();
    return defaultCsvPrecision;
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
int setCsvDefaultPrecision(const char *precision)
{
    if (initializeCsvDefaultValues()) return 1;
    if (precision == NULL) return 1;
    if (checkCsvWriteFormat(precision) == 0)
    {
        if (defaultCsvPrecision) FREE(defaultCsvPrecision);
        defaultCsvPrecision = strdup(precision);
        if (defaultCsvPrecision) return 0;
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

    if (defaultCsvPrecision == NULL)
    {
        defaultCsvPrecision = strdup(DEFAULT_CSV_PRECISION);
    }

    if ((defaultCsvSeparator == NULL) ||
        (defaultCsvDecimal == NULL) ||
        (defaultCsvConversion == NULL) ||
        (defaultCsvPrecision == NULL))
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
    if (defaultCsvPrecision) {FREE(defaultCsvPrecision); defaultCsvPrecision = NULL;}
    return initializeCsvDefaultValues();
}
/* ========================================================================== */
