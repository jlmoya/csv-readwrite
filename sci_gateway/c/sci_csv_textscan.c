/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include <string.h>
#include "stack-c.h"
#include "api_scilab.h"
#include "sci_types.h"
#include "Scierror.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "stringToComplex.h"
#include "csv_default.h"
#include "csv_read.h"
#include "getRange.h"
#include "gw_csv_helpers.h"
/* ========================================================================== */
#define CONVTOSTR "string"
#define CONVTODOUBLE "double"
/* ========================================================================== */
int sci_csv_textscan(char *fname)
{
    SciErr sciErr;
    int iErr = 0;
    int i = 0;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;

    char **text = NULL;
    int *lengthText = NULL;
    int nbLines = 0;

    char *separator = NULL;
    char *decimal = NULL;
    char *conversion = NULL;

    int *iRange = NULL;
    int haveRange = 0;

    csvResult *result = NULL;

    CheckRhs(1, 5);
    CheckLhs(1, 1);

    if (Rhs == 5)
    {
        #define SIZE_RANGE_SUPPORTED 4
        int m5 = 0, n5 = 0;

        iRange = csv_getArgumentAsMatrixofIntFromDouble(pvApiCtx, 5, fname, &m5, &n5, &iErr);
        if (iErr) return 0;

        if ((m5 * n5 != SIZE_RANGE_SUPPORTED) || (n5 != 1))
        {
            if (iRange) {FREE(iRange); iRange = NULL;}
            Scierror(999,_("%s: Wrong size for input argument #%d: A column vector expected.\n"), fname, 5);
            return 0;
        }

        if (isValidRange(iRange, m5 * n5))
        {
            haveRange = 1;
        }
        else
        {
            if (iRange) {FREE(iRange); iRange = NULL;}
            Scierror(999,_("%s: Wrong value for input argument #%d: A column vector expected.\n"), fname, 5);
            return 0;
        }
    }

    if (Rhs >= 4)
    {
        conversion = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 4, fname, getCsvDefaultConversion(), &iErr);
        if (iErr)
        {
            if (iRange) { FREE(iRange); iRange = NULL;}
            return 0;
        }

        if (!((strcmp(conversion, CONVTOSTR) == 0) || (strcmp(conversion, CONVTODOUBLE) == 0)))
        {
            if (iRange) { FREE(iRange); iRange = NULL;}
            if (conversion) { FREE(conversion); conversion = NULL;}

            Scierror(999,_("%s: Wrong value for input argument #%d: '%s' or '%s' string expected.\n"), fname, 4, "double", "string");
            return 0;
        }
    }
    else
    {
      conversion = strdup(getCsvDefaultConversion());
    }

    if (Rhs >= 3)
    {
        decimal = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 3, fname, getCsvDefaultDecimal(), &iErr);
        if (iErr)
        {
            if (iRange) { FREE(iRange); iRange = NULL;}
            if (conversion) {FREE(conversion); conversion = NULL;}
            return 0;
        }
    }
    else
    {
        decimal = strdup(getCsvDefaultDecimal());
    }

    if (Rhs >= 2)
    {
        separator = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 3, fname, getCsvDefaultSeparator(), &iErr);
        if (iErr)
        {
            if (iRange) { FREE(iRange); iRange = NULL;}
            if (decimal) {FREE(decimal); decimal = NULL;}
            if (conversion) {FREE(conversion); conversion = NULL;}
            return 0;
        }
    }
    else
    {
        separator = strdup(getCsvDefaultSeparator());
    }

    if (!csv_isRowVector(pvApiCtx, 1) &&
        !csv_isColumnVector(pvApiCtx, 1) &&
        !csv_isScalar(pvApiCtx, 1))
    {
        if (iRange) { FREE(iRange); iRange = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (conversion) {FREE(conversion); conversion = NULL;}
        Scierror(999,_("%s: Wrong size for input argument #%d: string expected.\n"), fname, 1);
        return 0;
    }

    text = csv_getArgumentAsMatrixOfString(pvApiCtx, 1, fname, &m1, &n1, &iErr);
    if (iErr)
    {
        if (iRange) { FREE(iRange); iRange = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (conversion) {FREE(conversion); conversion = NULL;}
        return 0;
    }

    result = csv_textscan(text, nbLines, separator, decimal);
    if (text)
    {
        if (separator) {FREE(separator); separator = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        freeArrayOfString(text, nbLines);
        text = NULL;
    }

    if (separator) {FREE(separator); separator = NULL;}
    if (decimal) {FREE(decimal); decimal = NULL;}

    if (result)
    {
        switch(result->err)
        {
            case CSV_READ_SEPARATOR_DECIMAL_EQUAL:
            {
                Scierror(999,_("%s: separator and decimal must have different values.\n"), fname);
            }
            break;

            case CSV_READ_NO_ERROR:
            {
                if (strcmp(conversion, CONVTOSTR) == 0)
                {
                    if (haveRange)
                    {
                        int newM = 0;
                        int newN = 0;

                        char **pStrRange = getRangeAsString(result->pstrValues, result->m, result->n, iRange, &newM, &newN);
                        if (pStrRange)
                        {
                            sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, newM, newN, pStrRange);
                            freeArrayOfString(pStrRange, newM * newN);
                        }
                        else
                        {
                            Scierror(999,_("%s: Memory allocation error.\n"), fname);
                        }

                    }
                    else
                    {
                        sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                    }
                }
                else /* to double */
                {
                  stringToComplexError ierr = STRINGTOCOMPLEX_ERROR;
                  doublecomplex *dvalscomplex = stringsToComplexs(result->pstrValues, result->m * result->n, TRUE, &ierr);
                  if (dvalscomplex == NULL)
                  {
                     freeCsvResult(result);
                     if (conversion) {FREE(conversion); conversion = NULL;}
                     if (iRange) { FREE(iRange); iRange = NULL;}
                     if (ierr == STRINGTOCOMPLEX_ERROR)
                     {
                        Scierror(999,_("%s: can not convert data.\n"), fname);
                     }
                     else
                     {
                         Scierror(999,_("%s: Memory allocation error.\n"), fname);
                     }
                     return 0;
                  }

                  switch(ierr)
                  {
                        case STRINGTOCOMPLEX_NOT_A_NUMBER:
                        case STRINGTOCOMPLEX_NO_ERROR:
                        {
                            if (haveRange)
                            {
                                int newM = 0;
                                int newN = 0;

                                doublecomplex *complexRange = getRangeAsComplex(dvalscomplex, result->m, result->n, iRange, &newM, &newN);
                                if (complexRange)
                                {
                                    sciErr = createComplexZMatrixOfDouble(pvApiCtx, Rhs + 1, newM, newN, complexRange);
                                    FREE(complexRange);
                                    complexRange = NULL;
                                }
                                else
                                {
                                    Scierror(999,_("%s: Memory allocation error.\n"), fname);
                                }
                            }
                            else
                            {
                                sciErr = createComplexZMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, dvalscomplex);
                            }
                            FREE(dvalscomplex);
                            dvalscomplex = NULL;
                        }
                        break;

                        case STRINGTOCOMPLEX_MEMORY_ALLOCATION:
                        {
                          Scierror(999,_("%s: Memory allocation error.\n"), fname);
                        }
                        default:
                        case STRINGTOCOMPLEX_ERROR:
                        {
                          Scierror(999,_("%s: can not convert data.\n"), fname);
                        }
                  }
                }

                if(sciErr.iErr)
                {
                    freeCsvResult(result);
                    if (conversion) {FREE(conversion); conversion = NULL;}
                    if (iRange) { FREE(iRange); iRange = NULL;}
                    printError(&sciErr, 0);
                    return 0;
                }
                else
                {
                    LhsVar(1) = Rhs + 1;
                    C2F(putlhsvar)();
                }
            }
            break;

            case CSV_READ_MEMORY_ALLOCATION:
            {
                Scierror(999,_("%s: Memory allocation error.\n"), fname);
            }
            break;

            case CSV_READ_READLINES_ERROR:
            case CSV_READ_COLUMNS_ERROR:
            case CSV_READ_ERROR:
            {
                Scierror(999,_("%s: can not read text.\n"), fname);
            }
            break;
        }
    }
    else
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
    }
    freeCsvResult(result);
    if (conversion) {FREE(conversion); conversion = NULL;}
    if (iRange) { FREE(iRange); iRange = NULL;}

    return 0;
}
/* ========================================================================== */
