// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include <afxwin.h>
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE UnikeyASDLL = { false, nullptr };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  UNREFERENCED_PARAMETER(lpReserved); // Remove this if you use lpReserved

  if (dwReason == DLL_PROCESS_ATTACH)
  {
    TRACE0("Unikey-AS.DLL Initializing!\n");

    if (AfxGetModuleState()->m_hCurrentInstanceHandle == nullptr)
    {
      AfxWinInit(hInstance, nullptr, GetCommandLine(), SW_NORMAL);
    }

    if (!AfxInitExtensionModule(UnikeyASDLL, hInstance)) // Extension DLL one-time initialization
    {
      return 0;
    }

    // Insert this DLL into the resource chain
    // NOTE: If this Extension DLL is being implicitly linked to by
    //  an MFC Regular DLL (such as an ActiveX Control)
    //  instead of an MFC application, then you will want to
    //  remove this line from DllMain and put it in a separate
    //  function exported from this Extension DLL.  The Regular DLL
    //  that uses this Extension DLL should then explicitly call that
    //  function to initialize this Extension DLL.  Otherwise,
    //  the CDynLinkLibrary object will not be attached to the
    //  Regular DLL's resource chain, and serious problems will
    //  result.

    new CDynLinkLibrary(UnikeyASDLL);
  }
  else if (dwReason == DLL_PROCESS_DETACH)
  {
    TRACE0("Unikey-AS.DLL Terminating!\n");
    AfxTermExtensionModule(UnikeyASDLL); // Terminate the library before destructors are called
  }

  return TRUE;
}
