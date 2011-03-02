/*
 *  Copyright (C) 2010-2011 - DIGITEO - Allan CORNET
 *  Copyright (C) 2011 - DIGITEO - Michael Baudin
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
#include "gw_csv_helpers.h"
/* ========================================================================== */
int sci_csv_stringtodouble(char *fname)
{
    SciErr sciErr;
    int iErr = 0;
    int m1 = 0, n1 = 0;
    char **pStringValues = NULL;

    BOOL bConvertToNan = TRUE;
	BOOL bIsReal;

    int i = 0;

    doublecomplex *dvalscomplex = NULL;
    stringToComplexError ierr = STRINGTOCOMPLEX_ERROR;

    double *dRealValues = NULL;

    CheckRhs(1, 2);
    CheckLhs(1, 1);

    if (Rhs == 1)
    {
        bConvertToNan = TRUE;
    }
    else /* Rhs == 2 */
    {
        bConvertToNan = csv_getArgumentAsScalarBoolean(pvApiCtx, 2, fname, &iErr);
        if (iErr) return 0;
    }

    pStringValues = csv_getArgumentAsMatrixOfString(pvApiCtx, 1, fname, &m1, &n1, &iErr);
    if (iErr) return 0;

    dvalscomplex = stringsToComplexs(pStringValues, m1 * n1, bConvertToNan, &ierr);

    freeArrayOfString(pStringValues, m1 * n1);
    pStringValues = NULL;

    if (dvalscomplex == NULL)
    {
        switch(ierr)
        {
            case STRINGTOCOMPLEX_NOT_A_NUMBER:
            case STRINGTOCOMPLEX_ERROR:
                Scierror(999,_("%s: can not convert data.\n"), fname);
            return 0;

            default:
                Scierror(999,_("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }

    switch(ierr)
    {
        case STRINGTOCOMPLEX_NOT_A_NUMBER:
        case STRINGTOCOMPLEX_NO_ERROR:
        {
			// See if matrix is real, or complex
			bIsReal = TRUE;
			for (i = 0; i < m1*n1; i++)
			{
				if ( dvalscomplex[i].i != 0 )
				{
					bIsReal = FALSE;
					break;
				}
			}
			if ( bIsReal )
			{
				// Copy the real entries into an array of doubles.
				dRealValues = (double*)MALLOC(sizeof(double) * m1*n1);
				for (i = 0; i < m1*n1; i++)
				{
					dRealValues[i] = dvalscomplex[i].r;
				}
				sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, m1, n1, dRealValues);
				FREE(dRealValues);
				dRealValues = NULL;
			}
			else
			{
				sciErr = createComplexZMatrixOfDouble(pvApiCtx, Rhs + 1, m1, n1, dvalscomplex);
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

    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
    }
    else
    {
        LhsVar(1) = Rhs + 1;
        C2F(putlhsvar)();
    }

    return 0;
}
/* ========================================================================== */
