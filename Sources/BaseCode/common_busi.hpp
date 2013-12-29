#ifndef  _buis_common_util_
#define  _buis_common_util_

#include <vcl.h>
#include "common.hpp"

bool chkFormatContainerNo(AnsiString ss){
        if (ss.Length()!=11){
                ShowMessage("柜号格式长度应为11");
                return false;
        }
        char cinfo[12];
        memset(cinfo, 0x00, sizeof(cinfo));
        snprintf(cinfo, 11, ss.c_str());


        for (int i=0;i<4; ++i){
                if (!(cinfo[i]>='a' && cinfo[i]<='z') && !(cinfo[i]>='A' && cinfo[i]<='Z')){
                        ShowMessage("柜号格式非法，前1-4位应为英文字母");
                        return false;
                }
        }
        for (int i=4;i<11; ++i){
                if (!(cinfo[i]>='0' && cinfo[i]<='9')){
                        ShowMessage("柜号格式非法，5-12位应为数字");
                        return false;
                }
        }

        return true;
}

//组装集装箱信息:“柜数|箱号 柜型 封条号#箱号 柜型 封条号#@”
CString GetContainerInfo(TListView *lv){
        CString szContInfo;
        szContInfo += (IntToStr(lv->Items->Count)).c_str();
        szContInfo += '|';
        for (int i=0; i<lv->Items->Count; ++i) {
                szContInfo += lv->Items->Item[i]->Caption.c_str();
                szContInfo += ' ';
                szContInfo += lv->Items->Item[i]->SubItems->Strings[0].c_str();
                szContInfo += ' ';
                szContInfo += lv->Items->Item[i]->SubItems->Strings[1].c_str();
                szContInfo += '#';
        }
        szContInfo += '@';
        return szContInfo;
}
//把edit转成money
double edt2money(TEdit *edt, int decimal_place=0){
        double rt = 0;
        AnsiString s = edt->Text;
        try{
                if (isMoney(s, decimal_place)){
                        TryStrToFloat(s, rt);
                }
        }catch(...){
        }
        return rt;
}
#endif