/* ==================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ==================================================================== */
#include <string.h>
#include "stack-c.h"
#include "api_scilab.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
#include "MALLOC.h"
#include "csv_read.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
/* ==================================================================== */
/* csv_read(filename [, separator [,decimal]]) */
/* ==================================================================== */
int sci_csv_read(char *fname)
{
    SciErr sciErr;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;

    char *filename = NULL;
    char *separator = NULL;
    char *decimal = NULL;

    csvResult *result = NULL;

    CheckRhs(1, 3);
    CheckLhs(1, 1);

    if (Rhs == 3)
    {
        int *piAddressVarThree = NULL;
        int m3 = 0, n3 = 0;
        int iType3 = 0;

        sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressVarThree);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        sciErr = getVarType(pvApiCtx, piAddressVarThree, &iType3);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if (iType3 != sci_strings)
        {
            Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 3);
            return 0;
        }

        sciErr = getVarDimension(pvApiCtx, piAddressVarThree, &m3, &n3);

        if ( (m3 != n3) && (n3 != 1) )
        {
            Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 3);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, piAddressVarThree, &decimal))
        {
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }
    else
    {
        decimal = strdup(DEFAULT_CSV_READ_DECIMAL);
    }

    if (Rhs >= 2)
    {
        int *piAddressVarTwo = NULL;
        int m2 = 0, n2 = 0;
        int iType2 = 0;

        sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        sciErr = getVarType(pvApiCtx, piAddressVarTwo, &iType2);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if (iType2 != sci_strings)
        {
            Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 2);
            return 0;
        }

        sciErr = getVarDimension(pvApiCtx, piAddressVarTwo, &m2, &n2);

        if ( (m2 != n2) && (n2 != 1) )
        {
            Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 2);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, piAddressVarTwo, &separator))
        {
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }
    else
    {
        separator = strdup(DEFAULT_CSV_READ_SEPARATOR);
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarOne, &iType1);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (iType1 != sci_strings)
    {
        Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarOne, &m1, &n1);

    if ( (m1 != n1) && (n1 != 1) )
    {
        Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, piAddressVarOne, &filename))
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
        return 0;
    }

    result = csv_read(filename, separator, decimal);
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
                createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                if(sciErr.iErr)
                {
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

            case CSV_READ_FILE_NOT_EXIST:
            case CSV_READ_MOPEN_ERROR:
            {
                Scierror(999,_("%s: can not open file %s.\n"), fname, filename);
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
                Scierror(999,_("%s: can not read file %s.\n"), fname, filename);
            }
            break;
        }
    }
    else
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
    }
    freeCsvResult(result);
    if (filename) {FREE(filename); filename = NULL;}

    return 0;
}
/* ==================================================================== */
