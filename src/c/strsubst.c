/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include <string.h>
#include "strsubst.h"
#include "MALLOC.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
/* ========================================================================== */
char *strsubst(char* input_string,
              const char* string_to_search,
              const char* replacement_string)
{
	char *occurrence_str = NULL, *result_str = NULL;
	

	char *replacedString = NULL;
	int count = 0, len = 0;

	if (input_string == NULL) return NULL;

	if (string_to_search == NULL || replacement_string == NULL) 
	{
		return strdup(input_string);
	}

	occurrence_str = strstr (input_string, string_to_search);
	if (occurrence_str == NULL)
	{
		return strdup(input_string);
	}

	if (strlen (replacement_string) > strlen (string_to_search)) 
	{
		count = 0;
		len = (int)strlen (string_to_search);
		if (len)
		{
			occurrence_str = input_string;
			while(occurrence_str != NULL && *occurrence_str != '\0') 
			{
				occurrence_str = strstr (occurrence_str, string_to_search);
				if (occurrence_str != NULL) 
				{
					occurrence_str += len;
					count++;
				}
			}
		}
		len = count * ((int)strlen(replacement_string) - (int)strlen(string_to_search)) + (int)strlen(input_string);
	}
	else len = (int)strlen(input_string);

	replacedString = MALLOC (sizeof(char)*(len + 1));
	if (replacedString == NULL) return NULL;

	occurrence_str = input_string;
	result_str = replacedString;
	len = (int)strlen (string_to_search);
	while(*occurrence_str != '\0') 
	{
		if (*occurrence_str == string_to_search[0] && strncmp (occurrence_str, string_to_search, len) == 0) 
		{
			const char *N = NULL;
			N = replacement_string;
			while (*N != '\0') *result_str++ = *N++;
			occurrence_str += len;
		}
		else *result_str++ = *occurrence_str++;
	}
	*result_str = '\0';

	return replacedString;
}
/* ========================================================================== */
