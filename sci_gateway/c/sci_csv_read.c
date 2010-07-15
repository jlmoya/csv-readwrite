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
#include "stringToDouble.h"
/* ==================================================================== */
#define CONVTOSTR "string"
#define CONVTODOUBLE "double"
/* ==================================================================== */
/* csv_read(filename [, separator [,decimal [,conversion]]]) */
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
    char *conversion = NULL;

    csvResult *result = NULL;

    CheckRhs(1, 4);
    CheckLhs(1, 1);

    if (Rhs == 4)
    {
        int *piAddressVarFour = NULL;
        int m4 = 0, n4 = 0;
        int iType4 = 0;

        sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddressVarFour);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        sciErr = getVarType(pvApiCtx, piAddressVarThree, &iType4);
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

        if (getAllocatedSingleString(pvApiCtx, piAddressVarFour, &conversion))
        {
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }

        if (strcmp(conversion, CONVTOSTR) || strcmp(conversion, CONVTODOUBLE) || strcmp(conversion, CONVTOAUTO))
        {
            FREE(conversion);
            conversion = NULL;
            Scierror(999,_("%s: Wrong value for input argument #%d: '%s' or '%s' string expected.\n"), fname, 4, "double", "string");
            return 0;
        }
    }
    else
    {
      conversion = strdup(CONVTOSTR);
    }

    if (Rhs >= 3)
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
                if (strcmp(conversion, CONVTOSTR) == 0)
                {
                  sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                }
                else /* to double */
                {
                  stringToDoubleError ierr = STRINGTODOUBLE_ERROR;
                  double *dvals = stringToDouble(result->pstrValues, result->m * result->n, TRUE, &ierr);
                  if (dvals == NULL)
                  {
                     freeCsvResult(result);
                     if (filename) {FREE(filename); filename = NULL;}
                     if (conversion) {FREE(conversion); conversion = NULL;}
                     Scierror(999,_("%s: Memory allocation error.\n"), fname);
                     return 0;
                  }

                  switch(ierr)
                  {
                        case STRINGTODOUBLE_NOT_A_NUMBER:
                        case STRINGTODOUBLE_NO_ERROR:
                        {
                          sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, dvals);
                          FREE(dvals);
                          dvals = NULL;
                        }
                        break;

                        case STRINGTODOUBLE_MEMORY_ALLOCATION:
                        {
                          Scierror(999,_("%s: Memory allocation error.\n"), fname);
                        }
                        default:
                        case STRINGTODOUBLE_ERROR:
                        {
                          Scierror(999,_("%s: can not convert data.\n"), fname);
                        }
                  }
                }

                if(sciErr.iErr)
                {
                        freeCsvResult(result);
                        if (filename) {FREE(filename); filename = NULL;}
                        if (conversion) {FREE(conversion); conversion = NULL;}
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
    if (conversion) {FREE(conversion); conversion = NULL;}

    return 0;
}
/* ==================================================================== */
