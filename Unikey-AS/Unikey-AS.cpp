// Unikey-AS.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Unikey.AS.Dlg.h"
#include "Unikey-AS.h"

#include <Vu>

UNIKEY_AS_API char __name__[]    = "Unikey AS";
UNIKEY_AS_API char __author__[]  = "Vic P.";
UNIKEY_AS_API char __version__[] = "1.0";
UNIKEY_AS_API char __summary__[] = "The Unikey AS extension";
UNIKEY_AS_API char __url__[]     = "https://github.com/vic4key/Unikey-AS-DLL.git";

/**
 * VExt
 */

static CUnikeyASDlg* pUnikeyASDlg = nullptr;

UNIKEY_AS_API void VExt_Load()
{
  pUnikeyASDlg = new CUnikeyASDlg();
  pUnikeyASDlg->Create(CUnikeyASDlg::IDD, nullptr);
  pUnikeyASDlg->ShowWindow(SW_HIDE);
}

UNIKEY_AS_API void VExt_Unload()
{
  if (pUnikeyASDlg != nullptr)
  {
    if (::IsWindow(pUnikeyASDlg->GetSafeHwnd()))
    {
      pUnikeyASDlg->SendMessage(WM_CLOSE);
    }

    delete pUnikeyASDlg;
  }
}

/**
 * VExt::Window
 */

VExt_Expose_Object(Window)

void Window::on_display()
{
  VExt::API::msg_box(__FUNCSIG__);
}

void Window::on_setting()
{
  VExt::API::msg_box(__FUNCSIG__);
}

std::string Window::on_menu_define()
{
  std::string menus = R"([
  {
    "caption": "Display UI",
    "index": 1,
    "children": []
  },
  {
    "caption": "Information",
    "index": 2,
    "children": []
  }])";

  return menus;
}

std::pair<bool, bool> Window::on_menu_update(UINT idx, LPARAM lp)
{
  return { true, false }; // all menu items are enabled & unchecked
}

void Window::on_menu_execute(UINT idx, LPARAM lp)
{
  if (idx == 1)
  {
    if (pUnikeyASDlg != nullptr)
    {
      pUnikeyASDlg->ShowWindow(SW_SHOW);
    }
  }
  else if (idx == 2)
  {
    auto s = vu::format_A("%s %s © %s\n\nWritten in C++ on %s", __name__, __version__, __author__, __DATE__);
    VExt::API::msg_box(s);
  }
}
