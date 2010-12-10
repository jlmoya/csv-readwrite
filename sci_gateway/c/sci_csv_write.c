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
#include "csv_write.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "csv_default.h"
/* ========================================================================== */
/* csv_write(M, filename[, separator, decimal]) */
/* with M string or double (not complex)
/* ========================================================================== */
int sci_csv_write(char *fname)
{
    SciErr sciErr;
    csvWriteError csvError = CSV_WRITE_ERROR;
    char *separator = NULL;
    char *decimal = NULL;
    char *filename = NULL;
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

    CheckRhs(2, 4);
    CheckLhs(1, 1);

    if (Rhs > 3)
    {
        int *piAddressVarFour = NULL;
        int iType4  = 0;
        int m4 = 0, n4 = 0;
        sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddressVarFour);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        sciErr = getVarType(pvApiCtx, piAddressVarFour, &iType4);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if (iType4 != sci_strings)
        {
            Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 4);
            return 0;
        }

        sciErr = getVarDimension(pvApiCtx, piAddressVarFour, &m4, &n4);

        if ( (m4 != n4) && (n4 != 1) )
        {
            Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 4);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, piAddressVarFour, &decimal))
        {
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }
    else
    {
        decimal = strdup(getCsvDefaultDecimal());
    }

    if (Rhs > 2)
    {
        int *piAddressVarThree = NULL;
        int iType3  = 0;
        int m3 = 0, n3 = 0;

        sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressVarThree);
        if(sciErr.iErr)
        {
            if (decimal) {FREE(decimal); decimal = NULL;}
            printError(&sciErr, 0);
            return 0;
        }

        sciErr = getVarType(pvApiCtx, piAddressVarThree, &iType3);
        if(sciErr.iErr)
        {
            if (decimal) {FREE(decimal); decimal = NULL;}
            printError(&sciErr, 0);
            return 0;
        }

        if (iType3 != sci_strings)
        {
            if (decimal) {FREE(decimal); decimal = NULL;}
            Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 3);
            return 0;
        }

        sciErr = getVarDimension(pvApiCtx, piAddressVarThree, &m3, &n3);

        if ( (m3 != n3) && (n3 != 1) )
        {
            if (decimal) {FREE(decimal); decimal = NULL;}
            Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 3);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, piAddressVarThree, &separator))
        {
            if (decimal) {FREE(decimal); decimal = NULL;}
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }
    else
    {
        separator = strdup(getCsvDefaultSeparator);
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if(sciErr.iErr)
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarTwo, &iType2);
    if(sciErr.iErr)
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    if (iType2 != sci_strings)
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarTwo, &m2, &n2);

    if ( (m2 != n2) && (n2 != 1) )
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, piAddressVarTwo, &filename))
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if(sciErr.iErr)
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarOne, &iType1);
    if(sciErr.iErr)
    {
        if (decimal) {FREE(decimal); decimal = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    if ((iType1 == sci_strings) || (iType1 == sci_matrix))
    {
        if (iType1 == sci_matrix)
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
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}
                printError(&sciErr, 0);
                return 0;
            }
        }
        else
        {
            int *lengthStringValues = NULL;
            int i = 0;

            sciErr = getVarDimension(pvApiCtx, piAddressVarOne, &m1, &n1);
            if(sciErr.iErr)
            {
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}

                printError(&sciErr, 0);
                return 0;
            }

            lengthStringValues = (int*)MALLOC(sizeof(int) * (m1 * n1));
            if (lengthStringValues == NULL)
            {
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}
                Scierror(999,_("%s: Memory allocation error.\n"), fname);
                return 0;
            }

            sciErr = getMatrixOfString(pvApiCtx, piAddressVarOne, &m1, &n1, lengthStringValues, NULL);
            if(sciErr.iErr)
            {
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}
                if (lengthStringValues) {FREE(lengthStringValues); lengthStringValues = NULL;}
                printError(&sciErr, 0);
                return 0;
            }

            pStringValues = (char**)MALLOC(sizeof(char*) * (m1 * n1));
            if (pStringValues == NULL)
            {
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}
                if (lengthStringValues) {FREE(lengthStringValues); lengthStringValues = NULL;}
                Scierror(999,_("%s: Memory allocation error.\n"),fname);
                return 0;
            }

            for (i = 0; i < (m1 * n1); i++)
            {
                pStringValues[i] = (char*)MALLOC(sizeof(char) * (lengthStringValues[i] + 1));
                if (pStringValues[i] == NULL)
                {
                    if (filename) {FREE(filename); filename = NULL;}
                    if (decimal) {FREE(decimal); decimal = NULL;}
                    if (separator) {FREE(separator); separator = NULL;}
                    if (lengthStringValues) {FREE(lengthStringValues); lengthStringValues = NULL;}
                    freeArrayOfString(pStringValues, m1 * n1);
                    Scierror(999,_("%s: Memory allocation error.\n"),fname);
                    return 0;
                }
            }

            sciErr = getMatrixOfString(pvApiCtx, piAddressVarOne, &m1, &n1, lengthStringValues, pStringValues);
            if (lengthStringValues) {FREE(lengthStringValues); lengthStringValues = NULL;}
            if(sciErr.iErr)
            {
                if (filename) {FREE(filename); filename = NULL;}
                if (decimal) {FREE(decimal); decimal = NULL;}
                if (separator) {FREE(separator); separator = NULL;}
                freeArrayOfString(pStringValues, m1 * n1);
                printError(&sciErr, 0);
                return 0;
            }
        }
    }
    else
    {
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
                                    decimal);
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
                                    decimal);
        }
        else
        {
            csvError = csv_write_double(filename,
                                    pDoubleValuesReal, m1, n1,
                                    separator,
                                    decimal);
        }
    }

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

    if (pStringValues) { freeArrayOfString(pStringValues, m1 * n1); pStringValues = NULL;}
    if (filename) {FREE(filename); filename = NULL;}
    if (decimal) {FREE(decimal); decimal = NULL;}
    if (separator) {FREE(separator); separator = NULL;}

    return 0;
}
/* ========================================================================== */
