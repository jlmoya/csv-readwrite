/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include "csv_read.h"
#include "freeArrayOfString.h"
#include "mgetl.h"
#include "mopen.h"
#include "mclose.h"
#include "splitLine.h"
#include "strsubst.h"
#include "FileExist.h"
#include "expandPathVariable.h"
/* ========================================================================== */
#if _MSC_VER
#define READ_ONLY_TEXT_MODE "rt"
#else
#define READ_ONLY_TEXT_MODE "r"
#endif
/* ========================================================================== */
static int getNumbersOfColumnsInLines(char **lines, int sizelines,
                                      char *separator);
static int getNumbersOfColumnsInLine(char *line, char *separator);
static char **getStringsFromLines(char **lines, int sizelines,
                                  char *separator, char *decimal,
                                  int m, int n);
/* ========================================================================== */
csvResult* csv_read(char *filename, char *separator, char *decimal)
{
    char *expandedFilename = NULL;
    csvResult *result = NULL;
    int fd = 0;
    int f_swap = 0;
    double res = 0.0;
    int errMOPEN = MOPEN_INVALID_STATUS;
    int errMGETL = MGETL_ERROR;
    double dErrClose = 0.;
    char **lines = NULL;
    int nblines = 0;

    int nbRows = 0;
    int nbColumns = 0;
    char **cellsStrings = NULL;

    if ((filename == NULL) || (separator == NULL) || (decimal == NULL))
    {
        return NULL;
    }

    if (strcmp(separator, decimal) == 0)
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_SEPARATOR_DECIMAL_EQUAL;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
        return result;
    }

    expandedFilename = expandPathVariable(filename);
    if (!FileExist(expandedFilename))
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_FILE_NOT_EXIST;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
        if (expandedFilename) {FREE(expandedFilename); expandedFilename = NULL;}
        return result;
    }

    C2F(mopen)(&fd, expandedFilename, READ_ONLY_TEXT_MODE, &f_swap, &res, &errMOPEN);
    if (expandedFilename) {FREE(expandedFilename); expandedFilename = NULL;}
    if (errMOPEN != MOPEN_NO_ERROR)
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_MOPEN_ERROR;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
        return result;
    }

    lines = mgetl(fd, -1, &nblines, &errMGETL);
    C2F(mclose)(&fd, &dErrClose);

    if (errMGETL != MGETL_NO_ERROR)
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_READLINES_ERROR;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
        return result;
    }

    nbColumns = getNumbersOfColumnsInLines(lines, nblines, separator);
    if (nbColumns == 0)
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_COLUMNS_ERROR;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
        return result;
    }
    else
    {
        nbRows = nblines;
    }

    cellsStrings = getStringsFromLines(lines, nblines, separator, decimal, nbColumns, nbRows);
    freeArrayOfString(lines, nblines);

    if (cellsStrings)
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_NO_ERROR;
            result->m = nbRows;
            result->n = nbColumns;
            result->pstrValues = cellsStrings;
        }
    }
    else
    {
        result = (csvResult*)(MALLOC(sizeof(csvResult)));
        if (result)
        {
            result->err = CSV_READ_COLUMNS_ERROR;
            result->m = 0;
            result->n = 0;
            result->pstrValues = NULL;
        }
    }
    return result;
}
/* ========================================================================== */
void freeCsvResult(csvResult *result)
{
    if (result)
    {
        if (result->pstrValues)
        {
            freeArrayOfString(result->pstrValues, result->m * result->n);
            result->pstrValues = NULL;
        }
        result->m = 0;
        result->n = 0;
        result->err = CSV_READ_ERROR;
        FREE(result);
        result = NULL;
    }
}
/* ========================================================================== */
static int getNumbersOfColumnsInLines(char **lines, int sizelines,
                                      char *separator)
{
    int previousNbColumns = 0;
    int NbColumns = 0;
    BOOL firstLine = TRUE;
    if (lines)
    {
        int i = 0;
        for (i = 0; i < sizelines; i++)
        {
            NbColumns = getNumbersOfColumnsInLine(lines[i], separator);
            if (firstLine)
            {
                previousNbColumns = NbColumns;
                firstLine = FALSE;
            }
            else
            {
                if (previousNbColumns != NbColumns)
                {
                    return 0;
                }
            }
        }
    }
    return NbColumns;
}
/* ========================================================================== */
static int getNumbersOfColumnsInLine(char *line, char *separator)
{
    if (line && separator)
    {
        int i = 0;
        int nbTokens = 0;
        char **splittedStr = splitLine(line, separator, &nbTokens, 0);
        if (splittedStr)
        {
            freeArrayOfString(splittedStr, nbTokens);
            if (nbTokens > 0) nbTokens--;
            return nbTokens;
        }
    }
    return 0;
}
/* ========================================================================== */
static char **getStringsFromLines(char **lines, int sizelines,
                                  char *separator,
                                  char *decimal,
                                  int m, int n)
{
    char **results = NULL;

    if (lines == NULL) return NULL;
    if (separator == NULL) return NULL;
    if (m == 0 || n == 0) return NULL;

    results = (char**) MALLOC(sizeof(char*) * (m * n));
    if (results)
    {
        int i = 0;
        for (i = 0; i < sizelines; i++)
        {
            int nbTokens = 0;
            char **lineStrings = splitLine(lines[i], separator, &nbTokens, 0);
            int j = 0;
            if (nbTokens > 0) nbTokens--;
            if (m != nbTokens)
            {
                freeArrayOfString(results, m * n);
                FREE(lineStrings);
                return NULL;
            }

            for (j = 0; j < m; j++)
            {
                if (decimal)
                {
                    results[i + n * j] = lineStrings[j];
                }
                else
                {
                    results[i + n * j] = strsubst(lineStrings[j], decimal, DEFAULT_CSV_READ_DECIMAL);
                    FREE(lineStrings[j]);
                    lineStrings[j] = NULL;
                }
            }
        }
    }
    return results;
}
/* ========================================================================== */
