#include <wchar.h>
#include "libcsvreadwrite_c.hxx"
extern "C"
{
#include "libcsvreadwrite_c.h"
#include "addfunction.h"
}

#define MODULE_NAME L"libcsvreadwrite_c"

int libcsvreadwrite_c(wchar_t* _pwstFuncName)
{
    if(wcscmp(_pwstFuncName, L"csv_read") == 0){ addCStackFunction(L"csv_read", &sci_csv_read, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"csv_write") == 0){ addCStackFunction(L"csv_write", &sci_csv_write, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"csv_textscan") == 0){ addCStackFunction(L"csv_textscan", &sci_csv_textscan, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"csv_stringtodouble") == 0){ addCStackFunction(L"csv_stringtodouble", &sci_csv_stringtodouble, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"csv_default") == 0){ addCStackFunction(L"csv_default", &sci_csv_default, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"csv_isnum") == 0){ addCStackFunction(L"csv_isnum", &sci_csv_isnum, MODULE_NAME); }

    return 1;
}
