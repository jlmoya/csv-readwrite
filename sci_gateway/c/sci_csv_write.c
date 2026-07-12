/*
*  Copyright (C) 2010-2012 - DIGITEO - Allan CORNET
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/
#include <string.h>
#include <stdio.h>
#include "api_scilab.h"
#include "sci_types.h"
#include "Scierror.h"
#include "sci_malloc.h"
#include "csv_write.h"
#include "localization.h"
#include "freeArrayOfString.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "csv_default.h"
#include "checkCsvWriteFormat.h"
#include "gw_csv_helpers.h"
/* ========================================================================== */
/* csv_write(M, filename[, separator, decimal, precision]) */
/* with M string or double (not complex)
/* ========================================================================== */
int sci_csv_write(char *fname, void *pvApiCtx)
{
    SciErr sciErr;
    int iErr = 0;
    csvWriteError csvError = CSV_WRITE_ERROR;

    char *separator = NULL;
    char *decimal = NULL;
    char *filename = NULL;
    char *precisionFormat = NULL;
    char **pHeadersLines = NULL;
    int nbHeadersLines = 0;

    char **pStringValues = NULL;
    double *pDoubleValuesReal = NULL;
    double *pDoubleValuesImag = NULL;
    int bIsComplex = 0;
    int mValues = 0;
    int nValues = 0;

    int *piAddressVarTwo = NULL;
    int m2 = 0, n2 = 0;
    int iType2 = 0;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;

    CheckRhs(2, 6);
    // Scilab 2027 port: the success path below only ever does `LhsVar(1) = 0;`
    // (this toolbox's void/no-return-value idiom -- it never actually creates
    // a stack value for output #1), which is only consistent with being
    // called with zero captured outputs. CheckLhs(1,1) forced exactly one,
    // which the void success path could never satisfy on return -- matches
    // the toolbox's own shipped test (tests/unit_tests/csv_readwrite.tst),
    // which always calls csv_write(x,filename) bare, uncaptured.
    CheckLhs(0, 1);

    if (Rhs > 5)
    {
        int isOnlyRowOrCol = 0;
        int m6 = 0; int n6 = 0;
        pHeadersLines = csv_getArgumentAsMatrixOfString(pvApiCtx, 6, fname, &m6, &n6, &iErr);
        if (iErr) return 0;
        isOnlyRowOrCol = ((m6 > 1) && (n6 == 1)) || ((m6 == 1) && (n6 > 1)) || ((m6 == 1) && (n6 == 1));
        if (!isOnlyRowOrCol)
        {
            if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
            Scierror(999,_("%s: Wrong size for input argument #%d: A 1-by-n or m-by-1 array of strings expected.\n"), fname, 6);
            return 0;
        }
        nbHeadersLines = m6 * n6;
    }

    if (Rhs > 4)
    {
        if (csv_isDoubleScalar(pvApiCtx, 5))
        {
#define FORMAT_FIELDVALUESTR "%%.%dlg"
            int iFormatValue = (int) csv_getArgumentAsScalarDouble(pvApiCtx, 5, fname, &iErr);
            if (iErr)
            {
                if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
                return 0;
            }

            if ((iFormatValue < 1) || (iFormatValue > 17))
            {
                Scierror(999,_("%s: Wrong value for input argument #%d: A double (value 1 to 17) expected.\n"), fname, 5);
                if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
                return 0;
            }

            precisionFormat = (char*)MALLOC(sizeof(char) * ((int)strlen(FORMAT_FIELDVALUESTR)+1));
            if (precisionFormat == NULL)
            {
                Scierror(999,_("%s: Memory allocation error.\n"), fname);
                if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
                return 0;
            }
            sprintf(precisionFormat, FORMAT_FIELDVALUESTR, iFormatValue);
        }
        else
        {
            precisionFormat = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 5, fname, getCsvDefaultPrecision(), &iErr);
            if (iErr) return 0;
            if (checkCsvWriteFormat(precisionFormat))
            {
                Scierror(999,_("%s: Not supported format %s.\n"), fname, precisionFormat);
                if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
                if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
                return 0;
            }
        }
    }
    else
    {
        precisionFormat = strdup(getCsvDefaultPrecision());
    }

    if (Rhs > 3)
    {
        decimal = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 4, fname, getCsvDefaultDecimal(), &iErr);
        if (iErr)
        {
            if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
            if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
            return 0;
        }
    }
    else
    {
        decimal = strdup(getCsvDefaultDecimal());
    }

    if (Rhs > 2)
    {
        separator = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 3, fname, getCsvDefaultSeparator(), &iErr);
        if (iErr)
        {
            if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
            if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
            if (decimal) {FREE(decimal); decimal = NULL;}
            return 0;
        }
    }
    else
    {
        separator = strdup(getCsvDefaultSeparator());
    }

    filename = csv_getArgumentAsString(pvApiCtx, 2, fname, &iErr);
    if (iErr)
    {
        if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if(sciErr.iErr)
    {
        if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
        if (filename) {FREE(filename); filename = NULL;}
        if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarOne, &iType1);
    if(sciErr.iErr)
    {
        if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
        if (filename) {FREE(filename); filename = NULL;}
        if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    if (iType1 == sci_strings)
    {
        pStringValues = csv_getArgumentAsMatrixOfString(pvApiCtx, 1, fname, &m1, &n1, &iErr);
        if (iErr)
        {
            if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
            if (filename) {FREE(filename); filename = NULL;}
            if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
            if (decimal) {FREE(decimal); decimal = NULL;}
            if (separator) {FREE(separator); separator = NULL;}
            return 0;
        }
    }
    else if (iType1 == sci_matrix)
    {
        if (isVarComplex(pvApiCtx, piAddressVarOne))
        {
            bIsComplex = 1;
            sciErr = getComplexMatrixOfDouble(pvApiCtx, piAddressVarOne, &m1, &n1, &pDoubleValuesReal, &pDoubleValuesImag);
        }
        else
        {
            sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarOne, &m1, &n1, &pDoubleValuesReal);
        }

        if(sciErr.iErr)
        {
            if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
            if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
            if (filename) {FREE(filename); filename = NULL;}
            if (decimal) {FREE(decimal); decimal = NULL;}
            if (separator) {FREE(separator); separator = NULL;}
            printError(&sciErr, 0);
            return 0;
        }
    }
    else
    {
        if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
        if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}
        if (filename) {FREE(filename); filename = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}

        Scierror(999,_("%s: Wrong type for input argument #%d: A matrix of string or a matrix of real expected.\n"), fname, 1);
        return 0;
    }

    if (pStringValues)
    {
        csvError = csv_write_string(filename,
            pStringValues, m1, n1,
            separator,
            decimal,
            pHeadersLines, nbHeadersLines);
    }
    else
    {
        if (bIsComplex)
        {
            csvError = csv_write_complex(filename,
                pDoubleValuesReal,
                pDoubleValuesImag,
                m1, n1,
                separator,
                decimal,
                precisionFormat,
                pHeadersLines, nbHeadersLines);
        }
        else
        {
            csvError = csv_write_double(filename,
                pDoubleValuesReal, m1, n1,
                separator,
                decimal,
                precisionFormat,
                pHeadersLines, nbHeadersLines);
        }
    }

    if (pHeadersLines) { freeArrayOfString(pHeadersLines, nbHeadersLines); pHeadersLines = NULL;}
    if (pStringValues) { freeArrayOfString(pStringValues, m1 * n1); pStringValues = NULL;}
    if (decimal) {FREE(decimal); decimal = NULL;}
    if (separator) {FREE(separator); separator = NULL;}
    if (precisionFormat) {FREE(precisionFormat); precisionFormat = NULL;}

    switch(csvError)
    {
    case CSV_WRITE_SEPARATOR_DECIMAL_EQUAL:
        {
            Scierror(999,_("%s: separator and decimal must have different values.\n"), fname);
        }
        break;
    case CSV_WRITE_NO_ERROR:
        {
            LhsVar(1) = 0;
            PutLhsVar();
        }
        break;

    case CSV_WRITE_FOPEN_ERROR:
        {
            Scierror(999,_("%s: can not open file %s.\n"), fname, filename);
        }
        break;
    default:
    case CSV_WRITE_ERROR:
        {
            Scierror(999, _("%s: error.\n"), fname);
        }
        break;
    }

    if (filename) {FREE(filename); filename = NULL;}

    return 0;
}
/* ========================================================================== */
