#ifndef __LIBCSVREADWRITE_C_GW_HXX__
#define __LIBCSVREADWRITE_C_GW_HXX__

#ifdef _MSC_VER
#ifdef LIBCSVREADWRITE_C_GW_EXPORTS
#define LIBCSVREADWRITE_C_GW_IMPEXP __declspec(dllexport)
#else
#define LIBCSVREADWRITE_C_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define LIBCSVREADWRITE_C_GW_IMPEXP
#endif

extern "C" LIBCSVREADWRITE_C_GW_IMPEXP int libcsvreadwrite_c(wchar_t* _pwstFuncName);



#endif /* __LIBCSVREADWRITE_C_GW_HXX__ */
