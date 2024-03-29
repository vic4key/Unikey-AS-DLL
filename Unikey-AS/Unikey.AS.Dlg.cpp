// Unikey.AS.Dlg.cpp : implementation file
//

#include "framework.h"
#include "Unikey.AS.Dlg.h"

/**
 * Resolve the linking issue that related to linking `comctl32.dll (version 6)`
 * Ordinal Not Found
 * The ordinal 345 could not be located in the dynamic link library
 */
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
  CAboutDlg();

  // Dialog Data
  enum { IDD = IDD_ABOUTBOX };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  // Implementation
protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CUnikeyASDlg dialog

BEGIN_MESSAGE_MAP(CUnikeyASDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDOK, &CUnikeyASDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDC_OPTION, &CUnikeyASDlg::OnBnClickedOption)
  ON_WM_TIMER()
  ON_BN_CLICKED(IDC_TOP_MOST, &CUnikeyASDlg::OnBnClickedTopMost)
  ON_BN_CLICKED(IDC_MODE, &CUnikeyASDlg::OnBnClickedMode)
  ON_WM_DESTROY()
  ON_COMMAND(ID_MENU_SHOW, &CUnikeyASDlg::OnMenuShowMain)
  ON_COMMAND(ID_MENU_ABOUT, &CUnikeyASDlg::OnMenuAbout)
  ON_COMMAND(ID_MENU_EXIT, &CUnikeyASDlg::OnMenuExit)
  ON_WM_CLOSE()
  ON_WM_CREATE()
END_MESSAGE_MAP()

CUnikeyASDlg::CUnikeyASDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CUnikeyASDlg::IDD, pParent)
  , m_Status(_T(""))
  , m_ForceMode(FALSE)
  , m_TopMost(FALSE)
  , m_StateToggleButtonED(true)
  , m_EVmode(_T("EVX"))
  , m_pUnikeyNT(nullptr)
  , m_ModeState(CUnikeyNT::eMode::MODE_NA)
{
  AfxInitRichEdit2();
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUnikeyASDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_ACTIVE_WINDOW, m_Status);
  DDX_Control(pDX, IDC_MODE_ICON, m_ModeIcon);
  DDX_Check(pDX, IDC_FORCE_MODE, m_ForceMode);
  DDX_Check(pDX, IDC_TOP_MOST, m_TopMost);
  DDX_Control(pDX, IDC_MODE, m_SwitchMode);
  DDX_Control(pDX, IDOK, m_ToggleButtonED);
}

// CUnikeyASDlg message handlers

int CUnikeyASDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (__super::OnCreate(lpCreateStruct) == -1) return -1;

  if (this->Initialize() != 0)
  {
    return FALSE; // ExitProcess(0);
  }

  return FALSE;
}

BOOL CUnikeyASDlg::OnInitDialog()
{
  __super::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    BOOL bNameValid;
    CString strAboutMenu;
    bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
    ASSERT(bNameValid);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon

  ICONINFOEX icon;
  icon.cbSize = sizeof(icon);
  GetIconInfoEx(m_hIcon, &icon);
  m_ModeIcon.SetBitmap(icon.hbmColor);

  SetWindowLongPtr(
    this->GetSafeHwnd(),
    GWL_STYLE,
    GetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE) & ~WS_THICKFRAME);

  Setup();

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUnikeyASDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    __super::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUnikeyASDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    __super::OnPaint();
  }
}

HCURSOR CUnikeyASDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

void CUnikeyASDlg::UpdateToggleButtonED()
{
  if (m_StateToggleButtonED)
  {
    m_ToggleButtonED.SetWindowText(_T("ENABLED"));
    m_Timer = this->SetTimer (1, 100, nullptr); /* 100ms */
  }
  else
  {
    m_ToggleButtonED.SetWindowText(_T("DISABLED"));
    if (m_Timer != 0) this->KillTimer(m_Timer);
  }
}

void CUnikeyASDlg::OnBnClickedOk()
{
  m_StateToggleButtonED = !m_StateToggleButtonED;
  this->UpdateToggleButtonED();
}

void CUnikeyASDlg::OnBnClickedOption()
{
  TASKDIALOG_BUTTON buttons[] =
  {
    { IDYES, L"Edit" },
    { IDNO, L"Reload" },
    { IDCANCEL, L"Cancel" },
  };

  int response = MessageBox(
    this->GetSafeHwnd(), IDS_OPTIONS, MB_ICONQUESTION, buttons, _countof(buttons), IDCANCEL);
  if (response == IDNO)
  {
    bool state = m_StateToggleButtonED;
    m_StateToggleButtonED = false;
    this->UpdateToggleButtonED();
    {
      if (m_pUnikeyNT->LoadFilterList(m_CfgPath) != 0)
      {
        CString text;
        text.LoadString(IDS_CONFIG_FILE_LOAD_FAILED);
        vu::msg_box(this->GetSafeHwnd(), MB_ICONERROR, m_AppName.c_str(), text.GetBuffer(), m_CfgPath.c_str());
      }
    }
    m_StateToggleButtonED = state;
    this->UpdateToggleButtonED();
  }
  else if (response == IDYES)
  {
    ShellExecute(this->GetSafeHwnd(), _T("open"), _T("notepad.exe"), m_CfgPath.c_str(), nullptr, SW_SHOWNORMAL);
  }
  else
  {
    // DO NOTHING
  }
}

int CUnikeyASDlg::Initialize()
{
  m_AppTitle = LoadRCString(IDS_APP_NAME);
  m_AppPath  = vu::get_current_file_path();
  m_AppName  = vu::extract_file_name(m_AppPath, false);
  m_AppDir   = vu::extract_file_directory(m_AppPath);

  auto extensions_dir = VExt::API::extensions_dir();

  vu::PathW path;
  path.join(vu::to_string_W(extensions_dir));
  path.join(L"Unikey-AS.INI");
  m_CfgPath = path.as_string();

  CString caption, text;
  caption.LoadString(IDS_ERROR);

  if (!vu::is_file_exists(m_CfgPath))
  {
    text.LoadString(IDS_CONFIG_FILE_NOT_FOUND);
    VExt::API::log(vu::to_string_A(text.GetBuffer()), VExt::logging_level_t::error);
    // vu::msg_box(this->GetSafeHwnd(), MB_ICONERROR, caption.GetBuffer(), text.GetBuffer(), m_CfgPath.c_str());
    return 1;
  }

  m_pUnikeyNT.reset(new CUnikeyNT);

  if (m_pUnikeyNT.get() == nullptr)
  {
    text.LoadString(IDS_INITIALIZE_HANDLER_FAILED);
    VExt::API::log(vu::to_string_A(text.GetBuffer()), VExt::logging_level_t::error);
    return 2;
  }

  if (m_pUnikeyNT->Initialize() != 0)
  {
    CString error = vu::get_last_error_W().c_str();
    text.LoadString(IDS_INITIALIZE_FAILED);
    text.Format(L"%s %s", text, error);
    VExt::API::log(vu::to_string_A(text.GetBuffer()), VExt::logging_level_t::error);
    return 3;
  }

  if (m_pUnikeyNT->LoadFilterList(m_CfgPath) != 0)
  {
    text.LoadString(IDS_CONFIG_FILE_LOAD_FAILED);
    VExt::API::log(vu::to_string_A(text.GetBuffer()), VExt::logging_level_t::error);
    return 4;
  }

  return 0;
}

void CUnikeyASDlg::Setup()
{
  this->UpdateData();
  {
    m_Timer = 0;

    m_ForceMode = TRUE;
    m_TopMost = TRUE;

    m_EN.LoadBitmap(IDB_EN);
    m_VN.LoadBitmap(IDB_VN);

    this->UpdateSwitchModeButton();

    this->UpdateToggleButtonED();

    this->SetWindowOnTopMost(m_TopMost != FALSE);

    this->CenterWindow();

    this->GetWindowTextW(m_Status);

    if (m_pUnikeyNT == nullptr || !m_pUnikeyNT->IsReady())
    {
      m_StateToggleButtonED = false;
      this->UpdateToggleButtonED();
      this->GetDlgItem(IDOK)->EnableWindow(FALSE);
      this->GetDlgItem(IDC_MODE)->EnableWindow(FALSE);
    }
  }
  this->UpdateData(FALSE);
}

void CUnikeyASDlg::OnTimer(UINT_PTR nIDEvent)
{
  this->UpdateData();

  bool changedToOther = false;

  auto pActiveWindow = this->GetForegroundWindow();
  if (pActiveWindow != m_pActiveWindow && (m_pActiveWindow = pActiveWindow) != nullptr)
  {
    CString theWindowName = _T("");
    int nSize = pActiveWindow->GetWindowTextLength();
    if (nSize > 0)
    {
      m_pActiveWindow->GetWindowTextW(theWindowName);
    }

    CString theWindowClass = _T("");
    {
      wchar_t s[MAXBYTE] = { 0 };
      nSize = GetClassNameW(m_pActiveWindow->GetSafeHwnd(), s, MAXBYTE);
      if (nSize > 0)
      {
        theWindowClass = s;
      }
    }

    CString theProcessName = _T("");
    {
      DWORD pid = 0;
      GetWindowThreadProcessId(m_pActiveWindow->GetSafeHwnd(), &pid);
      auto hp = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
      wchar_t s[MAX_PATH] = { 0 };
      DWORD size = MAX_PATH;
      QueryFullProcessImageNameW(hp, PROCESS_NAME_NATIVE, s, &size);
      CloseHandle(hp);
      theProcessName = PathFindFileNameW(s);
    }

    if (m_pActiveWindow != this)
    {
      m_Status  = _T("");
      m_Status += theWindowName;
      m_Status += _T("\n");
      m_Status += theWindowClass;
      m_Status += _T("\n");
      m_Status += theProcessName;

      this->UpdateData(FALSE);
    }
    changedToOther = true;
  }

  auto mode = m_pUnikeyNT->DetermineByWindowHandle(pActiveWindow->GetSafeHwnd());
  if (m_ForceMode) m_pUnikeyNT->SwitchMode(mode);
  else if (changedToOther) m_pUnikeyNT->SwitchMode(mode);

  mode = m_pUnikeyNT->GetModeState();
  if (mode != m_ModeState)
  {
    m_ModeState = mode;
    this->UpdateSwitchModeButton();
  }

  __super::OnTimer(nIDEvent);
}

void CUnikeyASDlg::OnBnClickedTopMost()
{
  this->SetWindowOnTopMost(m_TopMost == FALSE ? false : true);
}

void CUnikeyASDlg::OnBnClickedMode()
{
  if (m_pUnikeyNT.get() == nullptr || !m_pUnikeyNT->IsReady()) return;

  m_ModeState = m_pUnikeyNT->GetModeState();
  m_ModeState = (m_ModeState != CUnikeyNT::eMode::MODE_EN ?
    CUnikeyNT::eMode::MODE_EN : CUnikeyNT::eMode::MODE_VN);

  m_pUnikeyNT->SwitchMode(m_ModeState);

  m_ModeState = m_pUnikeyNT->GetModeState();

  this->UpdateSwitchModeButton();
}

void CUnikeyASDlg::UpdateSwitchModeButton()
{
  if (m_pUnikeyNT == nullptr || !m_pUnikeyNT->IsReady()) return;

  m_ModeState = m_pUnikeyNT->GetModeState();

  m_SwitchMode.SetBitmap(m_ModeState == CUnikeyNT::eMode::MODE_EN ? m_EN : m_VN);
}

void CUnikeyASDlg::OnDestroy()
{
  if (m_Timer != 0) this->KillTimer(m_Timer);
  __super::OnDestroy();
}

void CUnikeyASDlg::OnClose()
{
  this->ShowWindow(SW_HIDE);
}

void CUnikeyASDlg::OnMenuShowMain()
{
  this->ShowWindow(SW_SHOW);
}

void CUnikeyASDlg::OnMenuAbout()
{
  this->SendMessage(WM_SYSCOMMAND, IDM_ABOUTBOX);
}

void CUnikeyASDlg::OnMenuExit()
{
  /*auto s = vu::LoadResourceString(IDS_ASK_QUIT);
  auto response = this->MessageBox(s.c_str(), m_AppTitle.c_str(), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2);
  if (response == IDNO) return;*/

  if (m_Timer != 0) this->KillTimer(m_Timer);

  PostQuitMessage(0);
}

void CUnikeyASDlg::SetWindowOnTopMost(bool flag)
{
  RECT rect = { 0 };
  this->GetWindowRect(&rect);

  ::SetWindowPos(
    m_hWnd,
    flag ? HWND_TOPMOST : HWND_NOTOPMOST,
    rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
    IsWindowVisible() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW
  );
}

void CUnikeyASDlg::CenterWindow()
{
  auto cx = ::GetSystemMetrics(SM_CXSCREEN) / 2 ;
  auto cy = ::GetSystemMetrics(SM_CYSCREEN) / 2 ;

  RECT rect = {0};
  this->GetWindowRect(&rect);

  SIZE size =
  {
    rect.right - rect.left,
    rect.bottom - rect.top
  };

  ::SetWindowPos(
    this->GetSafeHwnd(),
    m_TopMost ? HWND_TOPMOST : HWND_NOTOPMOST,
    cx - size.cx / 2,
    cy - size.cy,
    size.cx,
    size.cy,
    IsWindowVisible() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW
  );
}

int CUnikeyASDlg::MessageBox(
  const HWND hwnd,
  const std::wstring& content,
  const UINT icon,
  const TASKDIALOG_BUTTON* pbuttons,
  const UINT nbuttons,
  const UINT buttondef)
{
  if (pbuttons == nullptr || nbuttons == 0)
  {
    return 0;
  }

  PCWSTR picon = nullptr;
  HICON  hicon = nullptr;

  switch (icon)
  {
  case MB_ICONERROR:
    picon = TD_ERROR_ICON;
    break;

  case MB_ICONQUESTION:
    hicon = LoadIcon(nullptr, IDI_QUESTION);
    break;

  case MB_ICONWARNING:
    picon = TD_WARNING_ICON;
    break;

  case MB_ICONINFORMATION:
    picon = TD_INFORMATION_ICON;
    break;

  default:
    break;
  }

  TASKDIALOGCONFIG tdc = { 0 };
  tdc.cbSize = sizeof(tdc);
  tdc.hInstance  = nullptr;
  tdc.hwndParent = hwnd,
  tdc.pszContent = content.c_str();
  if (picon != nullptr)
  {
    tdc.pszMainIcon = picon;
  }
  else if (hicon != nullptr)
  {
    tdc.dwFlags |= TDF_USE_HICON_MAIN;
    tdc.hMainIcon = hicon;
  }
  tdc.pButtons = pbuttons;
  tdc.cButtons = nbuttons;
  if (buttondef != 0)
  {
    tdc.nDefaultButton = buttondef;
  }

  int button = 0;

  HRESULT result = TaskDialogIndirect(&tdc, &button, nullptr, nullptr);
  if (result != S_OK)
  {
    return 0;
  }

  return button;
}

int CUnikeyASDlg::MessageBox(
  const HWND hwnd,
  const UINT content,
  const UINT icon,
  const TASKDIALOG_BUTTON* pbuttons,
  const UINT nbuttons,
  const UINT buttondef)
{
  auto s = LoadRCString(content);
  return MessageBox(hwnd, s, icon, pbuttons, nbuttons, buttondef);
}

std::wstring CUnikeyASDlg::LoadRCString(UINT id)
{
  TCHAR file_path[MAX_PATH] = { 0 };
  GetModuleFileName(HMODULE(&__ImageBase), file_path, sizeof(file_path));
  auto file_name = vu::extract_file_name(file_path);
  return vu::load_rs_string(id, file_name);
}
