#pragma once

#ifdef _MSC_VER
# ifdef DLL_A
#  define A_API __declspec(dllexport)
# else
#  define A_API __declspec(dllimport)
# endif
#else
# define A_API
#endif
