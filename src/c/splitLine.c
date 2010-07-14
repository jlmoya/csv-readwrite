/* ==================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ==================================================================== */
#include <string.h>
#include "splitLine.h"
#include "MALLOC.h"
/* ==================================================================== */
char **splitLine(char *str, char *sep, int *toks, char meta)
{
    char **retstr = NULL;
    char *idx = NULL;
    char *end = NULL;
    char *sep_end = NULL;
    char *sep_idx = NULL;
    int len = 0;
    int curr_str = 0;
    char last_char = 0xFF;

    sep_end = sep + strlen(sep);
    end = str + strlen(str);

    sep_idx = sep;
    idx = str;

    if (strstr(str, sep) == NULL)
    {
        *toks = 0;
        return NULL;
    }

    retstr = (char **) MALLOC((sizeof(char *) * (int)strlen(str)));
    if (retstr == NULL)
    {
        *toks = 0;
        return NULL;
    }

    while(idx < end)
    {
        while(sep_idx < sep_end)
        {
            if((*idx == *sep_idx) && (last_char != meta))
            {
                if(len > 0)
                {
                    if(curr_str < (int)strlen(str))
                    {
                        retstr[curr_str] = (char *) MALLOC((sizeof(char) * len) + 1);

                        if(retstr[curr_str] == NULL)
                        {
                            *toks = 0;
                            return NULL;
                        }
                        memcpy(retstr[curr_str], (idx - len), len);
                        retstr[curr_str][len] = 0;
                        len = 0;
                        curr_str++;
                        last_char = *idx;
                        idx++;
                    }

                    if(curr_str >= (int)strlen(str))
                    {
                        *toks = curr_str + 1;
                        return retstr;
                    }
                }
                else
                {
                    last_char = *idx;
                    idx++;
                    sep_idx = sep;
                    len = 0;
                }
            }
            else
            {
                sep_idx++;
            }
        }

        sep_idx = sep;
        len++;
        last_char = *idx;
        idx++;
    }

    if(len > 0)
    {
        retstr[curr_str] = (char *) MALLOC((sizeof(char) * len) + 1);

        if(retstr[curr_str] == NULL) 
        {
            *toks = 0;
            return NULL;
        }

        memcpy(retstr[curr_str], (idx - len), len);
        retstr[curr_str][len] = 0;

        *toks = curr_str + 1;
    }
    return retstr;
}
/* ==================================================================== */
