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
/* ========================================================================== */
#define CONVTOSTR "string"
#define CONVTODOUBLE "double"
/* ========================================================================== */
int sci_csv_textscan(char *fname)
{
    SciErr sciErr;
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

        if (getAllocatedSingleString(pvApiCtx, piAddressVarFour, &conversion))
        {
            Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }

        if (!((strcmp(conversion, CONVTOSTR) == 0) || (strcmp(conversion, CONVTODOUBLE) == 0)))
        {
            FREE(conversion);
            conversion = NULL;
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
        decimal = strdup(getCsvDefaultDecimal());
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
        separator = strdup(getCsvDefaultSeparator());
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
        Scierror(999,_("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarOne, &m1, &n1);
    
    if (!isRowVector(pvApiCtx, piAddressVarOne) && 
        !isColumnVector(pvApiCtx, piAddressVarOne) &&
        !isScalar(pvApiCtx, piAddressVarOne))
    {
        Scierror(999,_("%s: Wrong size for input argument #%d: string expected.\n"), fname, 1);
        return 0;
    }
    
    nbLines = m1 * n1;
    
    lengthText = (int*)MALLOC(sizeof(int) * nbLines);
    if (lengthText == NULL)
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
        return 0;
    }
    
    text = (char**)MALLOC(sizeof(char*) * nbLines);
    if (text == NULL)
    {
        Scierror(999,_("%s: Memory allocation error.\n"),fname);
        return 0;
    }
    
    // get lengthStrings value
    sciErr = getMatrixOfString(pvApiCtx, piAddressVarOne, &m1, &n1, lengthText, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    for (i = 0; i < nbLines; i++)
    {
        text[i] = (char*)MALLOC(sizeof(char) * (lengthText[i] + 1));
        if (text[i] == NULL)
        {
            freeArrayOfString(text, nbLines);
            if (lengthText) {FREE(lengthText); lengthText = NULL;}
            Scierror(999,_("%s: Memory allocation error.\n"),fname);
            return 0;
        }
    }
    
    sciErr = getMatrixOfString(pvApiCtx, piAddressVarOne, &m1, &n1, lengthText, text);
    if(sciErr.iErr)
    {
        freeArrayOfString(text, nbLines);
        if (lengthText) {FREE(lengthText); lengthText = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    result = csv_textscan(text, nbLines, separator, decimal);
    if (text)
    {
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
                  sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                }
                else /* to double */
                {
                  stringToComplexError ierr = STRINGTOCOMPLEX_ERROR;
                  doublecomplex *dvalscomplex = stringsToComplexs(result->pstrValues, result->m * result->n, TRUE, &ierr);
                  if (dvalscomplex == NULL)
                  {
                     freeCsvResult(result);
                     if (conversion) {FREE(conversion); conversion = NULL;}
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
                          sciErr = createComplexZMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, dvalscomplex);
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

    return 0;
}
/* ========================================================================== */
