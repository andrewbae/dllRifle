#ifndef _MAIN_H
#define _MAIN_H

#ifdef SAMPLEDLL_EXPORTS
#define SAMPLEDLL_API __declspec(dllexport)
#else
#define SAMPLEDLL_API __declspec(dllimport)
#endif

#include <windows.h>

#endif