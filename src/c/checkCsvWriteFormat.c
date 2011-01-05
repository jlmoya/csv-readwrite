/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2011 */
/* ========================================================================== */
#include <string.h>
#include "csv_default.h"
#include "MALLOC.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "checkCsvWriteFormat.h"
/* ========================================================================== */
#define NB_FORMAT_SUPPORTED 7 
static char *supportedFormat[NB_FORMAT_SUPPORTED] = 
{"lf", "lg", "d", "i", "e", "f", "g"};
/* ========================================================================== */
static char *replaceInFormat(const char *format);
static char *getCleanedFormat(const char *format);
/* ========================================================================== */
int checkCsvWriteFormat(const char *format)
{
    if (format)
    {
        char *tokenPercent1 = strchr(format, '%');
        char *tokenPercent2 = strrchr(format, '%');
        if ((tokenPercent2 && tokenPercent1) && (tokenPercent1 == tokenPercent2))
        {
            char *cleanedFormat = getCleanedFormat(format);
            if (cleanedFormat)
            {
                FREE(cleanedFormat);
                cleanedFormat = NULL;
                return 0;
            }
        }
    }
    return 1;
}
/* ========================================================================== */
static char *replaceInFormat(const char *format)
{
    char *newFormat = NULL;
    if (format)
    {
        int i = 0;
        for (i = 0; i < NB_FORMAT_SUPPORTED; i++)
        {
            char *cleanedFormat = getCleanedFormat(format);
            if (cleanedFormat)
            {
                newFormat = strdup("%s");
                FREE(cleanedFormat);
                cleanedFormat = NULL;
            }
        }
    }
    return newFormat;
}
/* ========================================================================== */
static char *getCleanedFormat(const char *format)
{
    char *cleanedFormat = NULL;
    if (format)
    {
        char *percent = strchr(format, '%');
        if (percent)
        {
            int i = 0;
            for(i = 0; i < NB_FORMAT_SUPPORTED; i++)
            {
                char *token = strstr(percent, supportedFormat[i]);
                if (token)
                {
                    int nbcharacters = strlen(percent) - strlen(token);          
                    cleanedFormat = strdup(percent);
                    cleanedFormat[nbcharacters] = 0;
                    if ( ((nbcharacters - 1 > 0) && (isdigit(cleanedFormat[nbcharacters-1])) ||
                        (cleanedFormat[nbcharacters-1]) == '.') ||
                        (cleanedFormat[nbcharacters-1]) == '%')
                    {
                        strcat(cleanedFormat, supportedFormat[i]);
                        return cleanedFormat;
                    }
                    else
                    {
                        FREE(cleanedFormat);
                        cleanedFormat = NULL;
                    }
                }
            }
        }
    }
    return cleanedFormat;
}
/* ========================================================================== */
