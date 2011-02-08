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

#include "MALLOC.h"
#include "getRange.h"
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
            
            for ( j = iRange[1] ; j <= iRange[3] ; j++)
            {
                for (i = iRange[0] ; i <= iRange[2] ; i++ )
                {
                    newStrArray[k] = strdup(pStrsValues[j + (*returnedNbRows)*i]);
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
            
            for (i = iRange[0] ; i < (*returnedNbCols) ; i++ )
            {
                for ( j = iRange[1] ; j < (*returnedNbRows) ; j++)
                {
                    newComplexArray[k].r = pComplex[i + (*returnedNbCols)*j].r;
                    newComplexArray[k].i = pComplex[i + (*returnedNbCols)*j].i;
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
    if (iRange == NULL) return 0;
    sizeRows = iRange[3] - iRange[1];
    if (sizeRows == 0) return (sizeRows = 1);
        
    if (sizeRows > maxRows)
    {
        return maxRows;
    }
    return sizeRows + 1;
}
/* ========================================================================== */
static int getSizeCols(const int *iRange, int maxCols)
{
    int sizeCols = 0;
    if (iRange == NULL) return 0;
    sizeCols = iRange[2] - iRange[0];
    if (sizeCols == 0) return (sizeCols = 1);

    if (sizeCols > maxCols)
    {
        return maxCols;
    }
    return sizeCols + 1;
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
