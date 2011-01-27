/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 - 2011 */
/* ========================================================================== */
#include <string.h>
#include "csv_read.h"
#include "MALLOC.h"
#include "freeArrayOfString.h"
#include "mgetl.h"
#include "mopen.h"
#include "mclose.h"
#include "splitLine.h"
#include "strsubst.h"
#include "FileExist.h"
#include "expandPathVariable.h"
#if _MSC_VER
#include "strdup_windows.h"
#endif
#include "csv_default.h"
/* ========================================================================== */
#if _MSC_VER
#define READ_ONLY_TEXT_MODE "rt"
#else
#define READ_ONLY_TEXT_MODE "r"
#endif
/* ========================================================================== */
static int getNumbersOfColumnsInLines(const char **lines, int sizelines,
                                      const char *separator);
static int getNumbersOfColumnsInLine(const char *line, const char *separator);
static char **getStringsFromLines(const char **lines, int sizelines,
                                  const char *separator, const char *decimal,
                                  int m, int n);
static char **removeEmptyLinesAtTheEnd(char **lines, int *sizelines);
static char *stripCharacters(const char *line);
static char **replaceStrings(const char **lines, int nbLines, const char **toreplace, int sizetoreplace);
/* ========================================================================== */
csvResult* csv_read(const char *filename, const char *separator, const char *decimal, const char **toreplace, int sizetoreplace)
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
    char **replacedInLines = NULL;

    if ((filename == NULL) || (separator == NULL) || (decimal == NULL))
    {
        return NULL;
    }

    expandedFilename = expandPathVariable((char*)filename);
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
        if (lines)
        {
            freeArrayOfString(lines, nblines);
            lines = NULL;
        }

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

    if (toreplace && (sizetoreplace > 0))
    {
        replacedInLines = replaceStrings(lines, nblines, toreplace, sizetoreplace);
        if (replacedInLines)
        {
            freeArrayOfString(lines, nblines);
            lines = replacedInLines;
        }
    }

    result = csv_textscan(lines, nblines, separator, decimal);
    if (lines)
    {
        freeArrayOfString(lines, nblines);
        lines = NULL;
    }

    return result;
}
/* ========================================================================== */
csvResult* csv_textscan(const char **lines, int numberOfLines, const char *separator, const char *decimal)
{
    csvResult *result = NULL;
    int nbRows = 0;
    int nbColumns = 0;
    char **cellsStrings = NULL;
    char **cleanedLines = NULL;
    int nbLines = numberOfLines;

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

    /* remove last lines empty (bug 7003 in scilab)*/
    cleanedLines = removeEmptyLinesAtTheEnd((char**)lines, &nbLines);

    nbColumns = getNumbersOfColumnsInLines(cleanedLines, nbLines, separator);
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
        nbRows = nbLines;
    }

    cellsStrings = getStringsFromLines(cleanedLines, nbLines, separator, decimal, nbColumns, nbRows);

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
static int getNumbersOfColumnsInLines(const char **lines, int sizelines,
                                      const char *separator)
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
static int getNumbersOfColumnsInLine(const char *line, const char *separator)
{
    if (line && separator)
    {
        int i = 0;
        int nbTokens = 0;
        char **splittedStr = splitLine(line, separator, &nbTokens, 0);
        if (splittedStr)
        {
            if (nbTokens > 0)
            {
                if ( (nbTokens > 1) && ((int)strlen(splittedStr[nbTokens - 1]) == 0) )
                {
                    nbTokens--;
                }
            }
            freeArrayOfString(splittedStr, nbTokens);
            
            return nbTokens;
        }
        else
        {
            int len = (int)strlen(line);
            if (len > 0)
            {
                nbTokens = 1;
                return nbTokens;
            }
        }
    }
    return 0;
}
/* ========================================================================== */
static char **getStringsFromLines(const char **lines, int sizelines,
                                  const char *separator,
                                  const char *decimal,
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

            if (lineStrings)
            {
                if (nbTokens > 0) 
                {
                    if ((nbTokens > 1) && ((int)strlen(lineStrings[nbTokens - 1]) == 0))
                    {
                        nbTokens--;
                    }
                }
            }
            else
            {
                lineStrings = (char**)MALLOC(sizeof(char*) * 1);
                lineStrings[0] = strdup(lines[i]);
                nbTokens = 1;
            }

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
                    results[i + n * j] = strsubst(lineStrings[j], decimal, getCsvDefaultDecimal());
                    FREE(lineStrings[j]);
                    lineStrings[j] = NULL;
                }
            }
        }
    }
    return results;
}
/* ========================================================================== */
static char **removeEmptyLinesAtTheEnd(char **lines, int *sizelines)
{
    char **returnedLines = lines;
    int nbLinesToRemove = 0;
    if (lines)
    {
        int i = 0;
        if (*sizelines >= 1)
        {
            for(i = *sizelines - 1; i >= 0; i--)
            {
                char *cleanedLine = stripCharacters(lines[i]);
                if (cleanedLine)
                {
                    int len = (int) strlen(cleanedLine);
                    FREE(cleanedLine);
                    cleanedLine = NULL;
                    if (len == 0)
                    {
                        nbLinesToRemove++;
                        FREE(lines[i]);
                        lines[i] = NULL;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            
            if (nbLinesToRemove > 0)
            {
                returnedLines = (char **)REALLOC(lines, sizeof(char *) * (*sizelines - nbLinesToRemove));
                if (returnedLines)
                {
                    *sizelines = *sizelines - nbLinesToRemove;
                }
                else
                {
                    returnedLines = lines;
                }
            }
        }
        else
        {
            returnedLines = lines;
        }
    }
    return returnedLines;
}
/* ========================================================================== */
static char *stripCharacters(const char *line)
{
    char *returnedLine = NULL;
    if (line)
    {
        char *tmpLineWithoutTab = strsubst((char*)line, "\t", "");
        if (tmpLineWithoutTab)
        {
            char *tmpLineWithoutLF = strsubst(tmpLineWithoutTab, "\r", "");
            if (tmpLineWithoutLF)
            {
                char *tmpLineWithoutCR = strsubst(tmpLineWithoutTab, "\n", "");
                if (tmpLineWithoutCR)
                {
                    returnedLine = strsubst(tmpLineWithoutCR, " ", "");
                }
                else
                {
                    returnedLine = strdup(line);
                }
                FREE(tmpLineWithoutLF);
                tmpLineWithoutLF = NULL;
            }
            else
            {
                returnedLine = strdup(line);
            }
            FREE(tmpLineWithoutTab);
            tmpLineWithoutTab = NULL;
        }
        else
        {
            returnedLine = strdup(line);
        }
    }

    return returnedLine;
}
/* ========================================================================== */
static char **replaceStrings(const char **lines, int nbLines, const char **toreplace, int sizetoreplace)
{
    char **replacedStrings = NULL;
    if (lines)
    {
        int i = 0;

        replacedStrings = (char**)MALLOC(sizeof(char*) * nbLines);
        if (replacedStrings)
        {
            for (i = 0; i < sizetoreplace; i = i + 2)
            {
                int j = 0;
                for (j = 0; j < nbLines; j++)
                {
                    replacedStrings[j] = strsubst(lines[j], toreplace[i], toreplace[i + 1]);
                }
            }
        }
    }
    return replacedStrings;
}
/* ========================================================================== */
