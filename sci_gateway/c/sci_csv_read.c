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
#include "stringToComplex.h"
#include "csv_default.h"
#include "gw_csv_helpers.h"
/* ==================================================================== */
#define CONVTOSTR "string"
#define CONVTODOUBLE "double"
/* ==================================================================== */
/* csv_read(filename, separator, decimal, conversion, substitute, range)*/
/* ==================================================================== */
int sci_csv_read(char *fname)
{
    SciErr sciErr;
    int iErr = 0;

    char *filename = NULL;
    char *separator = NULL;
    char *decimal = NULL;
    char *conversion = NULL;

    char **toreplace = NULL;
    int nbElementsToReplace = 0;

    csvResult *result = NULL;

	BOOL bIsReal;
    double *dRealValues = NULL;

    CheckRhs(1, 5);
    CheckLhs(1, 1);

    if (Rhs == 5)
    {
        int m5 = 0, n5 = 0;
        toreplace = csv_getArgumentAsMatrixOfString(pvApiCtx, 5, fname, &m5, &n5, &iErr);
        if (iErr) return 0;
        if (n5 != 2) 
        {
             freeArrayOfString(toreplace, m5 * n5);
             toreplace = NULL;
             Scierror(999,_("%s: Wrong size for input argument #%d.\n"), fname, 5);
             return 0;
        }
        nbElementsToReplace = m5;
    }
    else
    {
        toreplace = NULL;
        nbElementsToReplace = 0;
    }

    if (Rhs >= 4)
    {
        int iErr = 0;
        conversion = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 4, fname, getCsvDefaultConversion(), &iErr);
        if (iErr) return 0;
        if (!((strcmp(conversion, CONVTOSTR) == 0) || (strcmp(conversion, CONVTODOUBLE) == 0)))
        {
            if (toreplace) {freeArrayOfString(toreplace, nbElementsToReplace * 2); toreplace = NULL;}
            if (conversion) {FREE(conversion); conversion = NULL;}
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
        int iErr = 0;
        decimal = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 3, fname, getCsvDefaultDecimal(), &iErr);
        if (iErr)
        {
            if (conversion) {FREE(conversion); conversion = NULL;}
            if (toreplace) {freeArrayOfString(toreplace, nbElementsToReplace * 2); toreplace = NULL;}
            return 0;
        }
    }
    else
    {
        decimal = strdup(getCsvDefaultDecimal());
    }

    if (Rhs >= 2)
    {
        int iErr = 0;
        separator = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 2, fname, getCsvDefaultSeparator(), &iErr);
        if (iErr)
        {
            if (toreplace) {freeArrayOfString(toreplace, nbElementsToReplace * 2); toreplace = NULL;}
            if (conversion) {FREE(conversion); conversion = NULL;}
            if (decimal) {FREE(decimal); decimal = NULL;}
            return 0;
        }
    }
    else
    {
        separator = strdup(getCsvDefaultSeparator());
    }


    filename = csv_getArgumentAsString(pvApiCtx, 1, fname, &iErr);
    if (iErr)
    {
        if (toreplace) {freeArrayOfString(toreplace, nbElementsToReplace * 2); toreplace = NULL;}
        if (separator) {FREE(separator); separator = NULL;}
        if (conversion) {FREE(conversion); conversion = NULL;}
        if (decimal) {FREE(decimal); decimal = NULL;}
        return 0;
    }

    result = csv_read(filename, separator, decimal, toreplace, nbElementsToReplace * 2);
    if (toreplace) {freeArrayOfString(toreplace, nbElementsToReplace * 2); toreplace = NULL;}
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
                    /* Workaround bug ticket 194 andbug 8688 */
                    if (csv_checkSpaceInStackForString(Rhs + 1, result->m, result->n, result->pstrValues))
                    {
                        sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                    }
                    else
                    {
                        freeCsvResult(result);
                        if (filename) {FREE(filename); filename = NULL;}
                        if (conversion) {FREE(conversion); conversion = NULL;}
                        SciError(17);
                        return 0;
                    }
                }
                else /* to double */
                {
                  stringToComplexError ierr = STRINGTOCOMPLEX_ERROR;
                  doublecomplex *dvalscomplex = stringsToComplexs(result->pstrValues, result->m * result->n, TRUE, &ierr);
                  if (dvalscomplex == NULL)
                  {
                     freeCsvResult(result);
                     if (filename) {FREE(filename); filename = NULL;}
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
							// See if matrix is real, or complex
							int i;
							bIsReal = csv_isreal(dvalscomplex, result->m , result->n );
							if ( bIsReal )
							{
								// Copy the real entries into an array of doubles.
								dRealValues = (double*)MALLOC(sizeof(double) * result->m*result->n);
								for (i = 0; i < result->m*result->n; i++)
								{
									dRealValues[i] = dvalscomplex[i].r;
								}
								sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, dRealValues);
								FREE(dRealValues);
								dRealValues = NULL;
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
            {
                Scierror(999,_("%s: %s does not exist.\n"), fname, filename);
            }
            break;

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
