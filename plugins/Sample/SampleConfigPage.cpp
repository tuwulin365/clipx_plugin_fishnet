#include <precomp.h>
#include "plugin.h"
#include "SampleConfigPage.h"
#include "resource.h"

_DECLARE_SERVICETSINGLE(svc_ClipXConfigPage, SampleConfigPage);

// the name that appears in the config list
const char *SampleConfigPage::getPageTitle()
{
    return "Fishnet";
}

typedef struct _FishnetCfg
{
    int gb_set_enabled;
    int gb_set_save_full;
    int gb_set_save_history;
    int gb_set_save_newline;
    int gb_set_full_match;
    char gs_set_regex[4096];
    char gs_set_file[4096]; 
}FishnetCfg;

// settings, with default values
int gb_enabled = 0;

int gb_set1_enabled = 0;
int gb_set1_save_full = 0;
int gb_set1_save_history = 1;
int gb_set1_save_newline = 1;
int gb_set1_full_match = 0;
char gs_set1_regex[4096] = ".*";
char gs_set1_file[4096] = "fishnet_save1.txt";

int gb_set2_enabled = 0;
int gb_set2_save_full = 0;
int gb_set2_save_history = 1;
int gb_set2_save_newline = 1;
int gb_set2_full_match = 0;
char gs_set2_regex[4096] = ".*";
char gs_set2_file[4096] = "fishnet_save2.txt";


// temp values
int tb_enabled = 0;

int tb_set1_enabled = 0;
int tb_set1_save_full = 0;
int tb_set1_save_history = 0;
int tb_set1_save_newline = 0;
int tb_set1_full_match = 0;
char ts_set1_regex[4096] = "";
char ts_set1_file[4096] = "";

int tb_set2_enabled = 0;
int tb_set2_save_full = 0;
int tb_set2_save_history = 0;
int tb_set2_save_newline = 0;
int tb_set2_full_match = 0;
char ts_set2_regex[4096] = "";
char ts_set2_file[4096] = "";




// load settings from ini
void SampleConfigPage::loadSettings(const char *inifile, const char *section)
{
    gb_enabled = GetPrivateProfileInt(section, "fishnet_enabled", gb_enabled, inifile);
    
    gb_set1_enabled = GetPrivateProfileInt(section, "fishnet_set1_enabled", gb_set1_enabled, inifile);
    gb_set1_save_full = GetPrivateProfileInt(section, "fishnet_set1_save_full", gb_set1_save_full, inifile);
    gb_set1_save_history = GetPrivateProfileInt(section, "fishnet_set1_save_history", gb_set1_save_history, inifile);
    gb_set1_save_newline = GetPrivateProfileInt(section, "fishnet_set1_save_newline", gb_set1_save_newline, inifile);
    gb_set1_full_match = GetPrivateProfileInt(section, "fishnet_set1_full_match", gb_set1_full_match, inifile);
    GetPrivateProfileString(section, "fishnet_set1_regex", gs_set1_regex, gs_set1_regex, sizeof(gs_set1_regex), inifile);
    GetPrivateProfileString(section, "fishnet_set1_file", gs_set1_file, gs_set1_file, sizeof(gs_set1_file), inifile);

    gb_set2_enabled = GetPrivateProfileInt(section, "fishnet_set2_enabled", gb_set2_enabled, inifile);
    gb_set2_save_full = GetPrivateProfileInt(section, "fishnet_set2_save_full", gb_set2_save_full, inifile);
    gb_set2_save_history = GetPrivateProfileInt(section, "fishnet_set2_save_history", gb_set2_save_history, inifile);
    gb_set2_save_newline = GetPrivateProfileInt(section, "fishnet_set2_save_newline", gb_set2_save_newline, inifile);
    gb_set2_full_match = GetPrivateProfileInt(section, "fishnet_set2_full_match", gb_set2_full_match, inifile);
    GetPrivateProfileString(section, "fishnet_set2_regex", gs_set2_regex, gs_set2_regex, sizeof(gs_set2_regex), inifile);
    GetPrivateProfileString(section, "fishnet_set2_file", gs_set2_file, gs_set2_file, sizeof(gs_set2_file), inifile);
}

// save settings to ini
void SampleConfigPage::saveSettings(const char *inifile, const char *section)
{
    WritePrivateProfileString(section, "fishnet_enabled", StringPrintf("%d", gb_enabled), inifile);
    
    WritePrivateProfileString(section, "fishnet_set1_enabled", StringPrintf("%d", gb_set1_enabled), inifile);
    WritePrivateProfileString(section, "fishnet_set1_save_full", StringPrintf("%d", gb_set1_save_full), inifile);
    WritePrivateProfileString(section, "fishnet_set1_save_history", StringPrintf("%d", gb_set1_save_history), inifile);
    WritePrivateProfileString(section, "fishnet_set1_save_newline", StringPrintf("%d", gb_set1_save_newline), inifile);
    WritePrivateProfileString(section, "fishnet_set1_full_match", StringPrintf("%d", gb_set1_full_match), inifile);
    WritePrivateProfileString(section, "fishnet_set1_regex", gs_set1_regex, inifile);
    WritePrivateProfileString(section, "fishnet_set1_file", gs_set1_file, inifile);

    WritePrivateProfileString(section, "fishnet_set2_enabled", StringPrintf("%d", gb_set2_enabled), inifile);
    WritePrivateProfileString(section, "fishnet_set2_save_full", StringPrintf("%d", gb_set2_save_full), inifile);
    WritePrivateProfileString(section, "fishnet_set2_save_history", StringPrintf("%d", gb_set2_save_history), inifile);
    WritePrivateProfileString(section, "fishnet_set2_save_newline", StringPrintf("%d", gb_set2_save_newline), inifile);
    WritePrivateProfileString(section, "fishnet_set2_full_match", StringPrintf("%d", gb_set2_full_match), inifile);
    WritePrivateProfileString(section, "fishnet_set2_regex", gs_set2_regex, inifile);
    WritePrivateProfileString(section, "fishnet_set2_file", gs_set2_file, inifile);
}

// settings are copied to temporary variables, which the dialog works on, when the clipx config dialog is brought up
void SampleConfigPage::copySettings()
{
    tb_enabled              = gb_enabled;
    
    tb_set1_enabled         = gb_set1_enabled;
    tb_set1_save_full       = gb_set1_save_full;
    tb_set1_save_history    = gb_set1_save_history;
    tb_set1_save_newline    = gb_set1_save_newline;
    tb_set1_full_match      = gb_set1_full_match;
    strcpy(ts_set1_regex, gs_set1_regex);
    strcpy(ts_set1_file, gs_set1_file);

    tb_set2_enabled         = gb_set2_enabled;
    tb_set2_save_full       = gb_set2_save_full;
    tb_set2_save_history    = gb_set2_save_history;
    tb_set2_save_newline    = gb_set2_save_newline;
    tb_set2_full_match      = gb_set2_full_match;
    strcpy(ts_set2_regex, gs_set2_regex);
    strcpy(ts_set2_file, gs_set2_file);
}

// settings are validated when the user clicks ok or apply
void SampleConfigPage::applySettings()
{
    gb_enabled              = tb_enabled;
    
    gb_set1_enabled         = tb_set1_enabled;
    gb_set1_save_full       = tb_set1_save_full;
    gb_set1_save_history    = tb_set1_save_history;
    gb_set1_save_newline    = tb_set1_save_newline;
    gb_set1_full_match      = tb_set1_full_match;
    strcpy(gs_set1_regex, ts_set1_regex);
    strcpy(gs_set1_file, ts_set1_file);

    gb_set2_enabled         = tb_set2_enabled;
    gb_set2_save_full       = tb_set2_save_full;
    gb_set2_save_history    = tb_set2_save_history;
    gb_set2_save_newline    = tb_set2_save_newline;
    gb_set2_full_match      = tb_set2_full_match;
    strcpy(gs_set2_regex, ts_set2_regex);
    strcpy(gs_set2_file, ts_set2_file);
}

void updateVisibility(HWND hwndDlg)
{
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET1_ENABLE), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET1_ENABLED), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET1_SAVE_FULL), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET1_SAVE_HISTORY), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET1_SAVE_NEWLINE), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET1_FULL_MATCH), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_EDIT_SET1_REGEX), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_EDIT_SET1_FILE), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET1_REGEX), tb_enabled && tb_set1_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET1_FILE), tb_enabled && tb_set1_enabled);

    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET2_ENABLE), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET2_ENABLED), tb_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET2_SAVE_FULL), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET2_SAVE_HISTORY), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET2_SAVE_NEWLINE), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_SET2_FULL_MATCH), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_EDIT_SET2_REGEX), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_EDIT_SET2_FILE), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET2_REGEX), tb_enabled && tb_set2_enabled);
    EnableWindow(GetDlgItem(hwndDlg, IDC_STATIC_SET2_FILE), tb_enabled && tb_set2_enabled);
}

HWND g_last_dlg = NULL;

// dialog operates only on temp values, the values are copied from the actual settings prior to running the dialog,
// and copied back to the actual settings when teh user clicks ok or apply
INT_PTR CALLBACK dlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            g_last_dlg = hwndDlg;
            CheckDlgButton(hwndDlg, IDC_CHECK_ENABLE, tb_enabled ? BST_CHECKED : BST_UNCHECKED);
        
            CheckDlgButton(hwndDlg, IDC_CHECK_SET1_ENABLED, tb_set1_enabled ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET1_SAVE_FULL, tb_set1_save_full ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET1_SAVE_HISTORY, tb_set1_save_history ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET1_SAVE_NEWLINE, tb_set1_save_newline ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET1_FULL_MATCH, tb_set1_full_match ? BST_CHECKED : BST_UNCHECKED);
            SetDlgItemText(hwndDlg, IDC_EDIT_SET1_REGEX, ts_set1_regex);
            SetDlgItemText(hwndDlg, IDC_EDIT_SET1_FILE, ts_set1_file);

            CheckDlgButton(hwndDlg, IDC_CHECK_SET2_ENABLED, tb_set2_enabled ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET2_SAVE_FULL, tb_set2_save_full ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET2_SAVE_HISTORY, tb_set2_save_history ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET2_SAVE_NEWLINE, tb_set2_save_newline ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwndDlg, IDC_CHECK_SET2_FULL_MATCH, tb_set2_full_match ? BST_CHECKED : BST_UNCHECKED);
            SetDlgItemText(hwndDlg, IDC_EDIT_SET2_REGEX, ts_set2_regex);
            SetDlgItemText(hwndDlg, IDC_EDIT_SET2_FILE, ts_set2_file);
            
            updateVisibility(hwndDlg);
            return TRUE;
        case WM_USER+0x100:
            tb_enabled = gb_enabled;
            CheckDlgButton(hwndDlg, IDC_CHECK_ENABLE, tb_enabled ? BST_CHECKED : BST_UNCHECKED);
            updateVisibility(hwndDlg);
            return 0;
        case WM_COMMAND:
        {
            int wNotifyCode = HIWORD(wParam);
            int wID = LOWORD(wParam);
            HWND hwndCtl = (HWND) lParam;
            switch (wID)
            {
                case IDC_CHECK_ENABLE:
                    tb_enabled = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                    
                case IDC_CHECK_SET1_ENABLED:
                    tb_set1_enabled = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET1_SAVE_FULL:
                    tb_set1_save_full = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET1_SAVE_HISTORY:
                    tb_set1_save_history = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET1_SAVE_NEWLINE:
                    tb_set1_save_newline = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET1_FULL_MATCH:
                    tb_set1_full_match = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;

                case IDC_CHECK_SET2_ENABLED:
                    tb_set2_enabled = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET2_SAVE_FULL:
                    tb_set2_save_full = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET2_SAVE_HISTORY:
                    tb_set2_save_history = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET2_SAVE_NEWLINE:
                    tb_set2_save_newline = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                case IDC_CHECK_SET2_FULL_MATCH:
                    tb_set2_full_match = IsDlgButtonChecked(hwndDlg, wID);
                    updateVisibility(hwndDlg);
                    g_clipx->config_allowApply();
                    return 0;
                    
                case IDC_EDIT_SET1_REGEX:
                case IDC_EDIT_SET1_FILE:
                case IDC_EDIT_SET2_REGEX:
                case IDC_EDIT_SET2_FILE:
                    if (wNotifyCode == EN_CHANGE)
                    {
                        char czString[4096] = {0};
                        int value = GetDlgItemText(hwndDlg, wID, czString, sizeof(czString));
                        if (value > 0)
                        {
                            g_clipx->config_allowApply();
                            switch (wID)
                            {
                                case IDC_EDIT_SET1_REGEX:
                                    strcpy(ts_set1_regex, czString);
                                    return 0;
                                case IDC_EDIT_SET1_FILE:
                                    strcpy(ts_set1_file, czString);
                                    return 0;

                                case IDC_EDIT_SET2_REGEX:
                                    strcpy(ts_set2_regex, czString);
                                    return 0;
                                case IDC_EDIT_SET2_FILE:
                                    strcpy(ts_set2_file, czString);
                                    return 0;
                            }
                        }
                    }
                    break;
            }
            break;
        }
        case WM_DESTROY:
            g_last_dlg = NULL;
            break;
    }
    return 0;
}

// create the sub dialog
HWND SampleConfigPage::createPage(HWND parent)
{
    return CreateDialog(the->getOSModuleHandle(), MAKEINTRESOURCE(IDD_CONFIGPAGE), parent, dlgProc);
}

