/* ==================================================================== */
/* Allan CORNET */
/* DIGITEO 2011 */
/* ==================================================================== */
#include <string.h>
#ifdef _MSC_VER
#include <windows.h>
#include "strdup_windows.h"
#endif
#include "latintoutf.h"
#include "charEncoding.h"
#include "sci_malloc.h"
/* ==================================================================== */
#ifdef _MSC_VER
#pragma comment(lib,"oleaut32.lib")
#endif
/* ==================================================================== */
#define LINE_MAX 4096
#define EMPTYSTR ""
/* ==================================================================== */
/* Scilab 2027 port: IsValidUTF8() was never a Scilab/Windows API function
   (it is called unconditionally on every platform below, not just under
   _MSC_VER) and does not exist anywhere in current Scilab core either --
   provide a minimal, self-contained UTF-8 well-formedness check locally. */
static int IsValidUTF8(const char *str)
{
    const unsigned char *bytes = (const unsigned char*)str;
    if (!bytes)
    {
        return 0;
    }
    while (*bytes)
    {
        if ((bytes[0] & 0x80) == 0x00)
        {
            bytes += 1;
        }
        else if ((bytes[0] & 0xE0) == 0xC0 && (bytes[1] & 0xC0) == 0x80)
        {
            bytes += 2;
        }
        else if ((bytes[0] & 0xF0) == 0xE0 && (bytes[1] & 0xC0) == 0x80 && (bytes[2] & 0xC0) == 0x80)
        {
            bytes += 3;
        }
        else if ((bytes[0] & 0xF8) == 0xF0 && (bytes[1] & 0xC0) == 0x80 && (bytes[2] & 0xC0) == 0x80 && (bytes[3] & 0xC0) == 0x80)
        {
            bytes += 4;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
/* ==================================================================== */
char *latintoutf(char *_inString)
{
    char *outString = NULL;
    if (_inString)
    {
#ifdef _MSC_VER
        if (IsValidUTF8(_inString))
        {
            outString = strdup(_inString);
        }
        else
        {
            /* conversion ANSI to UTF */
            int Len = 0;
            int newLen = 0;
            BSTR bstrCode = NULL;

            Len = MultiByteToWideChar(CP_ACP, 0, _inString, lstrlen(_inString), NULL, NULL);
            bstrCode = SysAllocStringLen(NULL, Len);
            if (bstrCode)
            {
                if (MultiByteToWideChar(CP_ACP, 0, _inString, lstrlen(_inString), bstrCode, Len) == 0)
                {
                    return strdup(_inString);
                }

                newLen = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, outString, 0, NULL, NULL);
                outString = (char*) MALLOC(newLen + 1);
                if (outString)
                {
                    if (WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, outString, newLen, NULL, NULL) == 0)
                    {
                        SysFreeString(bstrCode);
                        FREE(outString);
                        return strdup(_inString);
                    }
                }
                else
                {
                    outString = strdup(_inString);
                }
                SysFreeString(bstrCode);
                bstrCode = NULL;
            }
            else
            {
                outString = strdup(_inString);
            }
        }
#else
        if (IsValidUTF8(_inString))
        {
            outString = strdup(_inString);
        }
        else
        {
            int len = (int)strlen(_inString);
            int i = 0;

            outString = (char*)MALLOC(((len*3) + 1) * sizeof(char));
            if (outString == NULL) return NULL;
            strcpy(outString, EMPTYSTR);

            for (i = 0; i < len; i++)
            {
                unsigned char *outUtfChar = NULL;
                unsigned char inAnsiChar = 0;

                if (_inString[i] < 0) inAnsiChar = 256 + _inString[i];
                else inAnsiChar = _inString[i];

                if(inAnsiChar < 128)
                {
                    outUtfChar = (char *)CALLOC(2, sizeof(char));
                    if (outUtfChar)
                    {
                        outUtfChar[0] = inAnsiChar;
                        outUtfChar[1] = 0;
                    }
                }
                else
                {
                    outUtfChar = (char *)CALLOC(3, sizeof(char));
                    if (outUtfChar)
                    {
                        outUtfChar[0] = (inAnsiChar >> 6) | 0xC0;
                        outUtfChar[1] = (inAnsiChar & 0x3F) | 0x80;
                        outUtfChar[2] = 0;
                    }
                }

                if (outUtfChar)
                {
                    strcat(outString, outUtfChar);
                    FREE(outUtfChar);
                    outUtfChar = NULL;
                }
            }
        }
#endif
    }
    return outString;
}
/*--------------------------------------------------------------------------*/
