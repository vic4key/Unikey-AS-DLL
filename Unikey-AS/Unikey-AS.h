// Unikey-AS.h : Defines the initialization routines for the DLL.
//

#pragma once

#ifdef UNIKEY_AS_EXPORTS
#define UNIKEY_AS_API extern "C" __declspec(dllexport)
#else
#define UNIKEY_AS_API __declspec(dllimport)
#endif
