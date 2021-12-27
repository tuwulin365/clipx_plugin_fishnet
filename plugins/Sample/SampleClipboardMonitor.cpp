#include <precomp.h>
#include "plugin.h"
#include "SampleClipboardMonitor.h"
#include "SampleConfigPage.h"

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

_DECLARE_SERVICETSINGLE(svc_ClipXClipboardMonitor, SampleClipboardMonitor);

//for debug
void ClipxPluginLog(char *pStr, int iLine)
{
    ofstream ofile;
    ofile.open("c:\\log.txt", ios::app);
    if (ofile)
    {
        ofile << pStr << " : " << iLine << endl;
        ofile.close();        
    }
}

// the user copied some text in the clipboard
static int NewTextClipboardProc(const char *text,  
                                int b_set_enabled, 
                                int b_set_save_full,  
                                int b_set_save_history,
                                int b_set_save_newline,
                                int b_set_full_match,
                                const char s_set_regex[4096],
                                const char s_set_file[4096])
{
    bool bIsMatch = false;
    ofstream ofile;
    
    if (!b_set_enabled)
    {
        return 1;
    }

    ofile.open(s_set_file, ios::app | ios::binary);
    if (ofile)
    {
        if (ofile.tellp() > 1024*1024*1024)
        {
            ofile << "!!!file over 1GB\r\n";
            ofile.close();
            return 1;
        }
        
        if (strlen(s_set_regex) && strlen(text))
        {
            if (0 == strcmp(s_set_regex, ".*"))
            {
                bIsMatch = true;
                if (b_set_save_newline)
                {
                    ofile << "\r\n";
                }
                ofile << text;
            }
            else
            {
                regex pattern;
                try
                {
                    pattern = s_set_regex;
                }
                catch (exception& e)
                {
                    ofile << "\r\n!!!pattern error\r\n";
                    ofile << "Standard exception: " << e.what() << "\r\n";
                    ofile.close();
                    return 1;
                }
                
                smatch result;
                string sText = text;

                if (b_set_full_match)
                {
                    //完全匹配
                    bIsMatch = regex_match(sText, result, pattern);
                    if (bIsMatch)
                    {
                        if (b_set_save_newline)
                        {
                            ofile << "\r\n";
                        }
                        ofile << text;
                    }
                }
                else
                {
                    //匹配所有子串
                    string::const_iterator iter_begin = sText.cbegin();
                    string::const_iterator iter_end = sText.cend();
                    while ((iter_begin != iter_end) && regex_search(iter_begin, iter_end, result, pattern))
                    {
                        bIsMatch = true;
                        
                        if (b_set_save_newline)
                        {
                            ofile << "\r\n";
                        }
                        
                        if (b_set_save_full)
                        {
                            ofile << text;
                            break;
                        }
                        else
                        {
                            ofile << result[0];
                        }

//                        ofile << "find!" << result[0] << endl;
//                        ofile << "substr start: " << *result[0].first << endl;
//                        if (result[0].second != iter_end)
//                        {
//                            ofile << "substr next: " <<  *result[0].second << endl;
//                        }
//                        else
//                        {
//                            ofile << "substr next: " << " no dat" << endl;
//                        }
                        iter_begin = result[0].second;  //更新迭代器位置
                    }                          
                }
            }
        }
        ofile.close();
    }
    
    return (bIsMatch && !b_set_save_history) ? 0 : 1;
}

// the user copied some text in the clipboard
int SampleClipboardMonitor::onNewTextClipboard(const char *text)
{
    int ret1;
    int ret2;

    if (!gb_enabled)
    {
        return 1;
    }
    
    ret1 = NewTextClipboardProc(text, 
                                gb_set1_enabled,
                                gb_set1_save_full,
                                gb_set1_save_history,
                                gb_set1_save_newline,
                                gb_set1_full_match,
                                gs_set1_regex,
                                gs_set1_file);

    ret2 = NewTextClipboardProc(text, 
                                gb_set2_enabled,
                                gb_set2_save_full,
                                gb_set2_save_history,
                                gb_set2_save_newline,
                                gb_set2_full_match,
                                gs_set2_regex,
                                gs_set2_file);
    
    return (ret1 && ret2) ? 1 : 0;
}

// the user copied a bitmap in the clipboard (HBITMAP format)
int SampleClipboardMonitor::onNewBitmapClipboard(HBITMAP bmp)
{
    return 1;
}

// the user copied a bitmap in the clipboard (packed DIB format)
int SampleClipboardMonitor::onNewDIBitmapClipboard(BITMAPINFO *dib)
{
    return 1;
}

int SampleClipboardMonitor::onNewFileListClipboard(HDROP filelist)
{
    return 1;
}

