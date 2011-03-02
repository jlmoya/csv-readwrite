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

#include "MALLOC.h"
#include "getRange.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
/* ========================================================================== */
#define SIZE_ARRAY_RANGE 4
/* ========================================================================== */
static int getSizeRange(const int *iRange, int maxRows, int maxCols);
static int getSizeRows(const int *iRange, int maxRows);
static int getSizeCols(const int *iRange, int maxCols);
static int getNumberElementsInRange(const int *iRange, int maxRows, int maxCols);
/* ========================================================================== */
int isValidRange(const int *range, int sizeArray)
{
    int i = 0;

    if (range == NULL) return 0;
    if (sizeArray != SIZE_ARRAY_RANGE) return 0;

    for (i = 0; i < sizeArray; i++)
    {
        if (range[i] <= 0) return 0;
    }

    if (range[0] > range[2]) return 0;
    if (range[1] > range[3]) return 0;

    return 1;
}
/* ========================================================================== */
char **getRangeAsString(const char **pStrsValues,
                        int nbRows, int nbCols,
                        const int *iRange,
                        int *returnedNbRows, int *returnedNbCols)
{
    if (isValidRange(iRange, SIZE_ARRAY_RANGE))
    {
        char **newStrArray = NULL;
        int sizeRange = getNumberElementsInRange(iRange, nbRows, nbCols);
		int R1, C1, R2, C2;

        *returnedNbRows = getSizeRows(iRange, nbRows);
        *returnedNbCols = getSizeCols(iRange, nbCols);

        newStrArray = (char**)MALLOC(sizeof(char*) * sizeRange);
        if (newStrArray == NULL)
        {
            *returnedNbCols = 0;
            *returnedNbRows = 0;
        }
        else
        {
            int i = 0;
            int j = 0;
            int k = 0;
            
			R1 = iRange[0];
			C1 = iRange[1];
			R2 = iRange[2];
			C2 = iRange[3];

			for ( j = C1-1 ; j < C2 ; j++)
			{
				for (i = R1-1 ; i < R2 ; i++ )
				{
                    newStrArray[k] = strdup(pStrsValues[i + nbRows*j]);
                    k++;
                }
            }
        }
        return newStrArray;
    }
    return NULL;
}
/* ========================================================================== */
doublecomplex *getRangeAsComplex(const doublecomplex *pComplex,
                        int nbRows, int nbCols,
                        const int *iRange,
                        int *returnedNbRows, int *returnedNbCols)
{
    if (isValidRange(iRange, SIZE_ARRAY_RANGE))
    {
        doublecomplex *newComplexArray = NULL;
        int sizeRange = getSizeRange(iRange, nbRows, nbCols);
		int R1, C1, R2, C2;
		doublecomplex source;

        *returnedNbRows = getSizeRows(iRange, nbRows);
        *returnedNbCols = getSizeCols(iRange, nbCols);

        newComplexArray = (doublecomplex*)MALLOC(sizeof(doublecomplex) * sizeRange);
        if (newComplexArray == NULL)
        {
            *returnedNbCols = 0;
            *returnedNbRows = 0;
        }
        else
        {
            int i = 0;
            int j = 0;
            int k = 0;

			R1 = iRange[0];
			C1 = iRange[1];
			R2 = iRange[2];
			C2 = iRange[3];

			for ( j = C1-1 ; j < C2 ; j++)
			{
				for (i = R1-1 ; i < R2 ; i++ )
				{
					source = pComplex[i + nbRows*j];
                    newComplexArray[k].r = source.r;
                    newComplexArray[k].i = source.i;
                    k++;
                }
            }
        }

        return newComplexArray;
    }
    return NULL;
}
/* ========================================================================== */
static int getSizeRange(const int *iRange, int maxRows, int maxCols)
{
    if (iRange)
    {
        return (getSizeRows(iRange, maxRows) * getSizeCols(iRange, maxCols));
    }
    return 0;
}
/* ========================================================================== */
static int getSizeRows(const int *iRange, int maxRows)
{
    int sizeRows = 0;
	int R1, R2;

	R1 = iRange[0];
	R2 = iRange[2];

	if (iRange == NULL) {
		return 0;
	}
    sizeRows = R2 - R1 + 1;

	if (sizeRows == 0) {
		return 1;
	}
        
    if (sizeRows > maxRows)
    {
        return maxRows;
    }
    return sizeRows;
}
/* ========================================================================== */
static int getSizeCols(const int *iRange, int maxCols)
{
    int sizeCols = 0;
		int C1, C2;

	C1 = iRange[1];
	C2 = iRange[3];

    if (iRange == NULL) return 0;
    sizeCols = C2 - C1 + 1;

	if (sizeCols == 0) {
		return 1;
	}

    if (sizeCols > maxCols)
    {
        return maxCols;
    }
    return sizeCols;
}
/* ========================================================================== */
static int getNumberElementsInRange(const int *iRange, int maxRows, int maxCols)
{
    int i = 0;
    int j = 0;
    int k = 0;
            
    for (i = iRange[0] ; i <= iRange[2] ; i++ )
    {
        if (i <= maxCols)
        {
            for ( j = iRange[1] ; j <= iRange[3] ; j++)
            {
                if (j <= maxRows)
                {
                    k++;
                }
            }
        }
    }
    return k;
}
/* ========================================================================== */
