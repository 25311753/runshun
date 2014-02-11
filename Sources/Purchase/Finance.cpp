//---------------------------------------------------------------------------
#include <map>
#include <vcl.h>
#pragma hdrstop

#include "Finance.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "OleExcelCom.h"
#include "Excel_2K_SRVR2.h"
#include <OleServer.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFinanceForm *FinanceForm;
/*
typedef struct
{
int chid;
char strChname[80];
} CHARGES;

static CArray<CHARGES,CHARGES> gCHARGES;
*/
enum E_COLUMN_NAME{
COL_CID = 0,
        COL_CLIWORKID,
        COL_ACCEPTDATE,
        COL_OPUNIT,
        COL_CLIENT,
        COL_GOODSPERF,
        COL_DECLAREID,
        COL_LADINGID,
        COL_CONTAINER,
        COL_LICENSENO,
        COL_CUSTFREE,
        COL_BEIZHU,
};
//add conno、备注、客户工单号
int charge_start_column = COL_BEIZHU+1; // 费用列起始列偏移. +0 ->第一个费用； +1 第二个费用
//---------------------------------------------------------------------------
void Finance(int nAuth)
{
        CALL_FORM(TFinanceForm);
}
__fastcall TFinanceForm::TFinanceForm(TComponent* Owner)
        : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------
void __fastcall TFinanceForm::FormShow(TObject *Sender)
{
        m_mChargeInfo.clear();
        m_strGoodsPerf = "";
        cbb1->Items->Add("");
        cbb2->Items->Add("");
        cbb3->Items->Add("");
        cbb4->Items->Add("");
        cbb5->Items->Add("");
        cbb6->Items->Add("");
        cbb7->Items->Add("");
        cbb8->Items->Add("");
        cbb9->Items->Add("");
        cbb10->Items->Add("");

        CString szSQL;
        szSQL.Format("select * from charges order by chid");
        RunSQL(dm1->Query1,szSQL,true);
        
        int column_charge = 0;
        while(!dm1->Query1->Eof)
        {
                int chid = dm1->Query1->FieldByName("chid")->AsInteger;
                AnsiString chname = dm1->Query1->FieldByName("chname")->AsString;
                
                cbb1->Items->Add(chname);
                cbb2->Items->Add(chname);
                cbb3->Items->Add(chname);
                cbb4->Items->Add(chname);
                cbb5->Items->Add(chname);
                cbb6->Items->Add(chname);
                cbb7->Items->Add(chname);
                cbb8->Items->Add(chname);
                cbb9->Items->Add(chname);
                cbb10->Items->Add(chname);
                lstView->Columns->Items[charge_start_column+(++column_charge)]->Caption = chname;

                m_mChargeInfo.insert(std::make_pair(chid, chname.c_str()));

                dm1->Query1->Next();
        }
        lstView->Columns->Items[charge_start_column+(++column_charge)]->Caption = "合计";
        
        cbb1->ItemIndex = 1;
        cbb2->ItemIndex = 2;
        cbb3->ItemIndex = 3;
        cbb4->ItemIndex = 4;
        cbb5->ItemIndex = 5;
        cbb6->ItemIndex = 6;
        cbb7->ItemIndex = 7;
        cbb8->ItemIndex = 8;
        cbb9->ItemIndex = 9;
        cbb10->ItemIndex = 10;

        TDateTime tDate=GetSysTime(false);
        dtpQryAcceptDate->DateTime=tDate;
        dtpQryAcceptDateEnd->DateTime=tDate;

        m_enWorkState=EN_IDLE;
        ResetCtrl();


}
//---------------------------------------------------------------------------

CString TFinanceForm::getAllContainerNo(AnsiString c){
        CString rt = "";
        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num; ){
                char str1[100],str2[100],str3[100],str4[100],strTmp[2048],strSealId[100];
                memset(str1,sizeof(str1),0x00);
                memset(str2,sizeof(str2),0x00);
                memset(str3,sizeof(str3),0x00);
                memset(str4,sizeof(str4),0x00);
                memset(strSealId,sizeof(strSealId),0x00);

                memset(strTmp,sizeof(strTmp),0x00);
                strcpy(strTmp,strTmp1);
                sscanf(strTmp,"%[^#]#",str1);
                sscanf(str1,"%s %s %s",str3,str4,strSealId);
                sscanf(strTmp,"%*[^#]#%[^@]",strTmp1);
// printf("head:[%s] tail:[%s]\n", str1, strTmp1);
// printf("bno:[%s] type:[%s]\n\n", str3, str4);
                rt += str3;
// rt += " | "; //0329
                if (++i<num)
                        rt += "\r\n " ; // excel里换行显示，最后一个不添加
        }
        return rt;
}

CString TFinanceForm::getFirstContainerNo(AnsiString c)
{
        CString rt = "";
        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num && i<1; ++i){
                char str1[100],str2[100],str3[100],str4[100],strTmp[2048],strSealId[100];
                memset(str1,sizeof(str1),0x00);
                memset(str2,sizeof(str2),0x00);
                memset(str3,sizeof(str3),0x00);
                memset(str4,sizeof(str4),0x00);
                memset(strSealId,sizeof(strSealId),0x00);

                memset(strTmp,sizeof(strTmp),0x00);
                strcpy(strTmp,strTmp1);
                sscanf(strTmp,"%[^#]#",str1);
                sscanf(str1,"%s %s %s",str3,str4,strSealId);
                sscanf(strTmp,"%*[^#]#%[^@]",strTmp1);
// printf("head:[%s] tail:[%s]\n", str1, strTmp1);
// printf("bno:[%s] type:[%s]\n\n", str3, str4);
                rt = str3;
        }
        return rt;
}
void __fastcall TFinanceForm::btnQueryClick(TObject *Sender)
{
        //gen date str
        unsigned short year0,month0,day0;
dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];
    sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);
        unsigned short year1,month1,day1;
dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];
    sprintf(strDate1,"%04d%02d%02d 23:59:59",year1,month1,day1);
        //~

        CString szSQL;
        szSQL="select *, year(acceptdate) as y, month(acceptdate) as m, day(acceptdate) as d, CONVERT(varchar(10), acceptdate, 23) as ad \
from customs \
where 1=1 ";
        if (!edtCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtCid->Text.c_str());
        }
        if (!edtDeclareId->Text.IsEmpty()){
                szSQL +=" and declareid="; szSQL += Str2DBString(edtDeclareId->Text.c_str());
        }
        if (!edtOperUnit->Text.IsEmpty()){
                szSQL +=" and operunit like '%"; szSQL += edtOperUnit->Text.c_str(); szSQL += "%'";
        }
        if (!edtLadingId->Text.IsEmpty()){
                szSQL +=" and ladingid="; szSQL += Str2DBString(edtLadingId->Text.c_str());
        }
        if (!edtClient->Text.IsEmpty()){
                szSQL +=" and client like '%"; szSQL += edtClient->Text.c_str(); szSQL += "%'";
        }
        if (!edtLicenseNo->Text.IsEmpty()){
                szSQL +=" and licenseno="; szSQL += Str2DBString(edtLicenseNo->Text.c_str());
        }
        if (!edtContainerinfo->Text.IsEmpty()){
                szSQL +=" and containerinfo like '%"; szSQL += edtContainerinfo->Text.c_str(); szSQL += "%'";
        }
        if (cbIsQryByDate->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
        }
        szSQL += " order by acceptdate";

        RunSQL(dm1->Query1,szSQL,true);
        lstView->Clear();
        if (dm1->Query1->Eof){
                m_enWorkState=EN_IDLE;
                ResetCtrl();
        }

        int column_no=0;
while(!dm1->Query1->Eof)
{
                column_no++;
                unsigned short year0,month0,day0;
                year0=dm1->Query1->FieldByName("y")->AsInteger;
                month0=dm1->Query1->FieldByName("m")->AsInteger;
                day0=dm1->Query1->FieldByName("d")->AsInteger;
                char strDate0[80];
         sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);

                TListItem *pItem = lstView->Items->Add();

                bool isNormal = (dm1->Query1->FieldByName("goodsperf")->AsString == "正常单");

                //fixed part
                pItem->Caption = column_no;
                pItem->SubItems->Add(dm1->Query1->FieldByName("cid")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("cliworkid")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("ad")->AsString);
                pItem->SubItems->Add(isNormal?dm1->Query1->FieldByName("operunit")->AsString:AnsiString(""));
                pItem->SubItems->Add(dm1->Query1->FieldByName("client")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("goodsperf")->AsString);
                pItem->SubItems->Add(isNormal?dm1->Query1->FieldByName("declareid")->AsString:AnsiString(""));
                pItem->SubItems->Add(dm1->Query1->FieldByName("ladingid")->AsString);
                pItem->SubItems->Add(AnsiString(getAllContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString)));
                pItem->SubItems->Add(isNormal?dm1->Query1->FieldByName("licenseno")->AsString:AnsiString(""));
                pItem->SubItems->Add(dm1->Query1->FieldByName("custfree")->AsString);
                double _custfree = StrToFloat(dm1->Query1->FieldByName("custfree")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("beizhu")->AsString);
                
                //init var charge column first, otherwise core in InsertCustFreeToListView2
                for(int i=0; i<m_mChargeInfo.size(); ++i) {
                        pItem->SubItems->Add("");
                }
                //for last column-total
                pItem->SubItems->Add("");
/* //tobedel!!!
pItem->SubItems->Add("");
pItem->SubItems->Add("");
*/

                {//qry charges
                        //finances
                        CString szSQL2;
                        szSQL2.Format("select * from finance, charges where chid=CAST(substring(fid, len(fid)-1,2) as int) and fid like '%s__'" \
                                        , dm1->Query1->FieldByName("cid")->AsString);
                        RunSQL(dm1->Query2, szSQL2, true);
                        
                        float total = 0;
                        int row = pItem->Index;
                        //只可能有10个费用
                        for (int i=0; i<10 && !dm1->Query2->Eof; ++i){
                                int pos = charge_start_column + cbb1->Items->IndexOf(dm1->Query2->FieldByName("chname")->AsString.c_str()) -1; //借cbb1用
                                InsertCustFreeToListViewOri(row, pos, dm1->Query2->FieldByName("value")->AsString);
                                total += dm1->Query2->FieldByName("value")->AsFloat;
                                dm1->Query2->Next();
                        }
                        total += _custfree;
                        lstView->Items->Item[row]->SubItems->Strings[charge_start_column+m_mChargeInfo.size()] = FloatToStr(total);

                }
dm1->Query1->Next();
        }

        m_enWorkState=EN_IDLE;
        ResetCtrl();


}
//---------------------------------------------------------------------------
//tofixed！！too bore
bool TFinanceForm::IsDupFree()
{

        int idx1, idx2,idx3,idx4,idx5,idx6,idx7,idx8,idx9,idx10;
        idx1 = idx2 = idx3 = idx4 = idx5 = idx6 = idx7 = idx8 = idx9 = idx10 =0;

        idx1 = cbb1->ItemIndex;
        idx2 = cbb2->ItemIndex;
        idx3 = cbb3->ItemIndex;
        idx4 = cbb4->ItemIndex;
        idx5 = cbb5->ItemIndex;
        idx6 = cbb6->ItemIndex;
        idx7 = cbb7->ItemIndex;
        idx8 = cbb8->ItemIndex;
        idx9 = cbb9->ItemIndex;
        idx10 = cbb10->ItemIndex;

        if (idx1!=0 && (idx1 == idx2 || idx1 == idx3 || idx1 == idx4 || idx1 == idx5 || idx1 == idx6 || idx1 == idx7 || idx1 == idx8 || idx1 == idx9 || idx1 == idx10) ){
             if(cbb1->CanFocus())
                cbb1->SetFocus();
             return true;
        }
        if (idx2!=0 &&(idx2 == idx3 || idx2 == idx4 || idx2 == idx5 || idx2 == idx6 || idx2 == idx7 || idx2 == idx8 || idx2 == idx9 || idx2 == idx10) ){
             if(cbb2->CanFocus())
                cbb2->SetFocus();
             return true;
        }
        if (idx3!=0 &&(idx3 == idx4 || idx3 == idx5 || idx3 == idx6 || idx3 == idx7 || idx3 == idx8 || idx3 == idx9 || idx3 == idx10)){
             if(cbb3->CanFocus())
                cbb3->SetFocus();
             return true;
        }
        if (idx4!=0 &&(idx4 == idx5 || idx4 == idx6 || idx4 == idx7 || idx4 == idx8 || idx4 == idx9 || idx4 == idx10)){
             if(cbb4->CanFocus())
                cbb4->SetFocus();
             return true;
        }
         if (idx5!=0 &&(idx5 == idx6 || idx5 == idx7 || idx5 == idx8 || idx5 == idx9 || idx5 == idx10)){
             if(cbb5->CanFocus())
                cbb5->SetFocus();
             return true;
         }
          if (idx6!=0 &&( idx6 == idx7 || idx6 == idx8 || idx6 == idx9 || idx6 == idx10)){
             if(cbb6->CanFocus())
                cbb6->SetFocus();
             return true;
          }
           if (idx7!=0 &&(idx7 == idx8 || idx7 == idx9 || idx7 == idx10)){
             if(cbb7->CanFocus())
                cbb7->SetFocus();
             return true;
           }
           if (idx8!=0 &&(idx8 == idx9 || idx8 == idx10)){
             if(cbb8->CanFocus())
                cbb8->SetFocus();
             return true;
           }
            if (idx9!=0 &&(idx9 == idx10)) {
             if(cbb9->CanFocus())
                cbb9->SetFocus();
             return true;
            }


        return false;
}
/*
void TFinanceForm::InsertCustFreeToListView(TListItem *plstitem,int &col_order, AnsiString col_name, AnsiString col_value){
if (col_name.IsEmpty() || col_value==""){
col_order--;
return;
}

lstView->Columns->Items[col_order]->Caption = col_name;
plstitem->SubItems->Add(col_value);
}
*/
void TFinanceForm::InsertCustFreeToListView2(int row, TComboBox *pcbb,AnsiString col_value){
    if (pcbb->ItemIndex == 0){
        return;
    }

    lstView->Items->Item[row]->SubItems->Strings[charge_start_column+pcbb->ItemIndex - 1] = col_value;
}
void TFinanceForm::InsertCustFreeToListViewOri(int row, int pos, AnsiString col_value){
    lstView->Items->Item[row]->SubItems->Strings[pos] = col_value;
}
/*
int GetClassRight(LPCSTR lpszChname){
int nRt = 0;
for(int i=0;i<gCHARGES.GetSize();i++)
{
if(strcmp(gCHARGES[i].strChname,lpszChname)==0)
return nRt = gCHARGES[i].chid;
}
return nRt;
}
*/
int TFinanceForm::getChidByChname(CString chname){
        for (std::map<int, CString>::const_iterator it=m_mChargeInfo.begin(); it!=m_mChargeInfo.end(); ++it){
                if (it->second == chname){
                        return it->first;
                }
        }
        return 0;//error
}
void TFinanceForm::InsertValue(TComboBox *cbb, TEdit *edt){
        if (cbb->ItemIndex == 0) {
                return;
        } else if(edt->Text.IsEmpty()){
                ShowMessage("请填写对应费用");
                if(edt->CanFocus())
                edt->SetFocus();
                return;
        }

        char strChid[80];
    sprintf(strChid, "%s%02d",edtCid->Text.c_str(), getChidByChname(cbb->Text.c_str()) );

        CString szSQL;
        szSQL = "insert into finance(fid,value) values(";
        szSQL += Str2DBString(strChid);
        szSQL +=","; szSQL += Str2DBString(edt->Text.c_str());
        szSQL +=")";

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return;
        }
}
/*
void TFinanceForm::UpdateValue(TComboBox *cbb, TEdit *edt){
if (cbb->Text.IsEmpty()){
return;
}
char strChid[80];
sprintf(strChid,"%s%02d",edtCid->Text.c_str(),StrToInt(GetClassRight(cbb->Text.c_str())));

CString szSQL;
szSQL = "update finance set value=";
szSQL += Str2DBString(edt->Text.c_str());
szSQL += " where fid=";
szSQL += Str2DBString(strChid);
if(!RunSQL(dm1->Query1,szSQL))
{
ShowMessage("update fail!") ;
return;
}
}
*/
//空白状态才可以添加，一旦添加过，只能修改
void __fastcall TFinanceForm::btnModClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  return;
}
//---------------------------------------------------------------------------
float TFinanceForm::getCharge(TEdit *edt)
{
        return StrToFloat(edt->Text.IsEmpty()?"0":edt->Text.c_str());
}

//#include <map.h>
//#include <string>

TComboBox *TFinanceForm::getCbb(int i)
{
        TComboBox *rt = NULL;
        switch(i){
                case 1:
                        rt=cbb1;
                        break;
                case 2:
                        rt=cbb2;
                        break;
                case 3:
                        rt=cbb3;
                        break;
                case 4:
                        rt=cbb4;
                        break;
                case 5:
                        rt=cbb5;
                        break;
                case 6:
                        rt=cbb6;
                        break;
                case 7:
                        rt=cbb7;
                        break;
                case 8:
                        rt=cbb8;
                        break;
                case 9:
                        rt=cbb9;
                        break;
                case 10:
                        rt=cbb10;
                        break;
                default:
                        break;

        };
        return rt;
}

TEdit *TFinanceForm::getEdt(int i)
{
        TEdit *rt = NULL;
        switch(i){
                case 1:
                        rt=edtCharge1;
                        break;
                case 2:
                        rt=edtCharge2;
                        break;
                case 3:
                        rt=edtCharge3;
                        break;
                case 4:
                        rt=edtCharge4;
                        break;
                case 5:
                        rt=edtCharge5;
                        break;
                case 6:
                        rt=edtCharge6;
                        break;
                case 7:
                        rt=edtCharge7;
                        break;
                case 8:
                        rt=edtCharge8;
                        break;
                case 9:
                        rt=edtCharge9;
                        break;
                case 10:
                        rt=edtCharge10;
                        break;
                default:
                        break;

        };
        return rt;
}
void TFinanceForm::ResetCharges(){
        cbb1->ItemIndex = 0;
        cbb2->ItemIndex = 0;
        cbb3->ItemIndex = 0;
        cbb4->ItemIndex = 0;
        cbb5->ItemIndex = 0;
        cbb6->ItemIndex = 0;
        cbb7->ItemIndex = 0;
        cbb8->ItemIndex = 0;
        cbb9->ItemIndex = 0;
        cbb10->ItemIndex = 0;

        edtCharge1->Text = "";
        edtCharge2->Text = "";
        edtCharge3->Text = "";
        edtCharge4->Text = "";
        edtCharge5->Text = "";
        edtCharge6->Text = "";
        edtCharge7->Text = "";
        edtCharge8->Text = "";
        edtCharge9->Text = "";
        edtCharge10->Text = "";


}
//---------------------------------------------------------------------------




void __fastcall TFinanceForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
    if (Selected!=NULL){
        ResetCharges();
// edtCid->Text = Item->Caption;
        edtCid->Text = Item->SubItems->Strings[COL_CID];
        edtOperUnit->Text = Item->SubItems->Strings[COL_OPUNIT];
        edtClient->Text = Item->SubItems->Strings[COL_CLIENT];
        edtDeclareId->Text = Item->SubItems->Strings[COL_DECLAREID];
        edtLadingId->Text = Item->SubItems->Strings[COL_LADINGID];
        edtContainerinfo->Text = Item->SubItems->Strings[COL_CONTAINER];
        edtLicenseNo->Text = Item->SubItems->Strings[COL_LICENSENO];
        edtCustFree->Text = Item->SubItems->Strings[COL_CUSTFREE];
        edtRemark->Text = Item->SubItems->Strings[COL_BEIZHU];
        int cbb_order = 0;

        int pos_charge = 0;
        for (std::map<int, CString>::const_iterator it=m_mChargeInfo.begin(); it!=m_mChargeInfo.end(); ++it){
                int pos = charge_start_column + pos_charge++;
                if (Item->SubItems->Strings[pos] != ""){
                        cbb_order++;
                        TComboBox *cbb = getCbb(cbb_order);
                        TEdit *edt = getEdt(cbb_order);
                        cbb->ItemIndex = cbb->Items->IndexOf(AnsiString(it->second));
                        edt->Text = Item->SubItems->Strings[pos];

                }
        }
        btnMod->Enabled = true;
    }

}
//---------------------------------------------------------------------------

void TFinanceForm::ResetCtrl()
{
  if(m_enWorkState==EN_IDLE)
  {
    //lstview
    lstView->Enabled = true;
    //btn
// btnMod->Enabled=isHasResult;
    btnMod->Enabled=false;
    btnOK->Enabled =false;
    btnCancel->Enabled=false;
    //qry panel
    for(int i=0;i <plQry->ControlCount;i++)
    {
              plQry->Controls[i]->Enabled = true;
    }
    //charge panel
    for(int i=0;i <plMod->ControlCount;i++)
    {
              plMod->Controls[i]->Enabled = false;
    }
  }
  else
  {
    //lstview
    lstView->Enabled = false;
    //btn
    btnMod->Enabled=false;
    btnOK->Enabled =true;
    btnCancel->Enabled=true;
    //qry panel
    for(int i=0;i <plQry->ControlCount;i++)
    {
              plQry->Controls[i]->Enabled = false;
    }
    //charge panel
    for(int i=0;i <plMod->ControlCount;i++)
    {
              plMod->Controls[i]->Enabled = true;
    }
  }

}
void __fastcall TFinanceForm::h(TObject *Sender)
{

      if(lstView->Selected == NULL){
// btnAddDetail->Enabled = true;
         btnMod->Enabled = false;
         clearQryInput();
      }
}
//---------------------------------------------------------------------------

void __fastcall TFinanceForm::btnCancelClick(TObject *Sender)
{
  int nState;
    
//clear input

  lstView->ItemIndex=-1;
  lstView->Selected = NULL;
  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  clearQryInput();
}
//---------------------------------------------------------------------------

void __fastcall TFinanceForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;

  switch(m_enWorkState)
  {
    case EN_EDIT:
      if (-1 == ModCharge())
        return;
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }

  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------

int TFinanceForm::ModCharge(){
        int rt = -1;

        if (lstView->Selected == NULL) {
                ShowMessage("未选中记录");
                return rt;
        }
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n 确定保存上述费用吗？ \n",edtCid->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return rt;

        if (edtCid->Text.IsEmpty()){
                ShowMessage("请先填写工单号");
                return rt;
        }
        //valid check
        if (IsDupFree()) {
                ShowMessage("有重复费用项目,请检查输入");
                return rt;
        }
        //del all free
        CString szSQL;
        szSQL.Format("delete from finance where fid like '%s__'",edtCid->Text.c_str());
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("delete fail!") ;
                return rt;
        }

        //then insert new free
        InsertValue(cbb1,edtCharge1);
        InsertValue(cbb2,edtCharge2);
        InsertValue(cbb3,edtCharge3);
        InsertValue(cbb4,edtCharge4);
        InsertValue(cbb5,edtCharge5);
        InsertValue(cbb6,edtCharge6);
        InsertValue(cbb7,edtCharge7);
        InsertValue(cbb8,edtCharge8);
        InsertValue(cbb9,edtCharge9);
        InsertValue(cbb10,edtCharge10);

        //update custfree
        if (!edtCustFree->Text.IsEmpty()) {
                szSQL.Format("update customs set custfree='%s' where cid='%s'",edtCustFree->Text.c_str(), edtCid->Text.c_str());
                if(!RunSQL(dm1->Query1,szSQL))
                {
                        ShowMessage("update custfree fail!") ;
                        return rt;
                }
        }

        //add listview
        TListItem *pItem = lstView->Items->Add();
        bool isNormal = (lbGoodsPerf->Caption == "正常单");
        // int nColPos = 0;
        pItem->Caption = 0; //mod after
        pItem->SubItems->Add(edtCid->Text);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[COL_CLIWORKID]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[COL_ACCEPTDATE]);
        pItem->SubItems->Add(isNormal?edtOperUnit->Text:AnsiString(""));
        pItem->SubItems->Add(edtClient->Text);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[COL_GOODSPERF]);
        pItem->SubItems->Add(isNormal?edtDeclareId->Text:AnsiString(""));
        pItem->SubItems->Add(edtLadingId->Text);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[COL_CONTAINER]);
        pItem->SubItems->Add(isNormal?edtLicenseNo->Text:AnsiString(""));
        pItem->SubItems->Add(edtCustFree->Text);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[COL_BEIZHU]);

        //init var charge column first, otherwise core in InsertCustFreeToListView2
        for(int i=0; i<m_mChargeInfo.size(); ++i) {
                pItem->SubItems->Add("");
        }
        pItem->SubItems->Add("");

        int row = pItem->Index;
        InsertCustFreeToListView2(row, cbb1, edtCharge1->Text);
        InsertCustFreeToListView2(row, cbb2, edtCharge2->Text);
        InsertCustFreeToListView2(row, cbb3, edtCharge3->Text);
        InsertCustFreeToListView2(row, cbb4, edtCharge4->Text);
        InsertCustFreeToListView2(row, cbb5, edtCharge5->Text);
        InsertCustFreeToListView2(row, cbb6, edtCharge6->Text);
        InsertCustFreeToListView2(row, cbb7, edtCharge7->Text);
        InsertCustFreeToListView2(row, cbb8, edtCharge8->Text);
        InsertCustFreeToListView2(row, cbb9, edtCharge9->Text);
        InsertCustFreeToListView2(row, cbb10, edtCharge10->Text);
        float total = getCharge(edtCharge1) + getCharge(edtCharge2) + getCharge(edtCharge3) +
            getCharge(edtCharge4) + getCharge(edtCharge5) + getCharge(edtCharge6) +
            getCharge(edtCharge7) + getCharge(edtCharge8) + getCharge(edtCharge9) +
            getCharge(edtCharge10);

        double _custfree = StrToFloat(edtCustFree->Text);
        total += _custfree;

        lstView->Items->Item[row]->SubItems->Strings[charge_start_column+m_mChargeInfo.size()] = FloatToStr(total);
        //delete after add

        lstView->Selected->Delete();

        //clear input
        clearQryInput();
        lstView->ItemIndex = -1;
        lstView->Selected = NULL;
        rt = 0;
        flushColumnNo();
        return rt;
}


void TFinanceForm::clearQryInput()
{
        edtRemark->Text = "";
// cbIsQryByDate->Checked = false;
   edtCid->Text = "";
        edtDeclareId->Text = "";
        edtLadingId->Text = "";
        edtOperUnit->Text = "";
        edtLicenseNo->Text = "";
        edtClient->Text = "";
        edtContainerinfo->Text = "";
        edtCustFree->Text = "";
        cbb1->ItemIndex = -1;
        cbb2->ItemIndex = -1;
        cbb3->ItemIndex = -1;
        cbb4->ItemIndex = -1;
        cbb5->ItemIndex = -1;
        cbb6->ItemIndex = -1;
        cbb7->ItemIndex = -1;
        cbb8->ItemIndex = -1;
        cbb9->ItemIndex = -1;
        cbb10->ItemIndex = -1;
        edtCharge1->Text = "";
        edtCharge2->Text = "";
        edtCharge3->Text = "";
        edtCharge4->Text = "";
        edtCharge5->Text = "";
        edtCharge6->Text = "";
        edtCharge7->Text = "";
        edtCharge8->Text = "";
        edtCharge9->Text = "";
        edtCharge10->Text = "";
}

//---------------------------------------------------------------------------


void __fastcall TFinanceForm::Button2Click(TObject *Sender)
{
        AnsiString sfile ="";
 if(SaveDialog1->Execute()){
        sfile = SaveDialog1->FileName;
// ShowMessage(sfile);
 }else{
        ShowMessage("导出未完成");
        return;
 }
         std::map<int, int> map_charge_exist; // 如所有行都没有某个费用，则标记0；否则标记1。
        map_charge_exist.clear();
        //初始化全部为0
        for (int i=0; i<m_mChargeInfo.size(); ++i){
                map_charge_exist.insert(std::make_pair(i, 0));
        }

        //init listViewPure's column header names by listView's
        int pos_pure = 0;
        int pos_ori = 0;
        lstViewPure->Columns->Items[0]->Caption = "序号";
        for (pos_ori=0; pos_ori<charge_start_column-1-1; pos_ori++){//！！备注放最后
                AnsiString column_title = lstView->Columns->Items[pos_ori+1+1]->Caption;
                //cancel
/* if (column_title=="经营单位" || column_title=="报关单号"){//不到出：经营单位、报关单号
continue;
}
*/
                lstViewPure->Columns->Items[++pos_pure]->Caption = column_title;
        }
        //~

        //标记那个费用非空
        for (int row=0; row<lstView->Items->Count; ++row) {
                for (int col=0; col<m_mChargeInfo.size(); ++col) {
                        int pos_real = charge_start_column + col;
                        if (lstView->Items->Item[row]->SubItems->Strings[pos_real] != ""){
                                map_charge_exist[col] = 1 ;
                        }
                }
        }

        //构造非空费用列名 - 根据map_charge_exist构造情况！！
       for (int j=0; j<m_mChargeInfo.size(); ++j) {
               int pos_real = charge_start_column+j;
                if (map_charge_exist[j] == 1){
                    lstViewPure->Columns->Items[1+pos_pure++]->Caption = lstView->Columns->Items[pos_real+1]->Caption;
                }
       }

        lstViewPure->Columns->Items[1+pos_pure++]->Caption = "合计";
        lstViewPure->Columns->Items[1+pos_pure++]->Caption = "备注";

        //copy data
        lstViewPure->Clear();
        edtMockDeclareid->Text = "";
        for(int i=0;i<lstView->Items->Count;i++)
        {
                 TListItem *pItem = lstViewPure->Items->Add();
                 pItem->Caption = AnsiString(i+1);

                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_CLIWORKID]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_ACCEPTDATE]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_OPUNIT]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_CLIENT]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_GOODSPERF]);
                 edtMockDeclareid->Text = lstView->Items->Item[i]->SubItems->Strings[COL_DECLAREID];
                 pItem->SubItems->Add((edtMockDeclareid->Text.Length() > 9)? edtMockDeclareid->Text.SubString(edtMockDeclareid->Text.Length()-9+1,9):edtMockDeclareid->Text);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_LADINGID]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_CONTAINER]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_LICENSENO]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_CUSTFREE]);

                 int j=0;
                 int cnt=0;
                 for (j=0; j<m_mChargeInfo.size(); ++j) {
                        int pos_real = charge_start_column + j;
                        if (map_charge_exist[j] == 0){
                               continue;
                        }
                        pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[pos_real]);
                        cnt++;
                 }
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[charge_start_column+j]); //must！ 不显示2个column
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[COL_BEIZHU]);

                 //必须，否则异常，导致到处1条记录就中断
                 for (int t=cnt; t<40; ++t)
                        pItem->SubItems->Add("");
        }
        //gen excel
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{

                vExcel = Variant::CreateObject("Excel.Application"); //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");

                vExcel.OlePropertySet("DisplayAlerts",false);
                //属性设置
// vExcel.OlePropertySet("Visible",true);
                vSheet.OlePropertyGet("Rows",++iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",15);//设置所有列的列宽为28

                //添加表体图片
                AnsiString strPic = "d:\\p1.jpg";
                vPicture = vSheet.OlePropertyGet( "Pictures").OleFunction( "Insert",strPic.c_str());
                vPicture.OlePropertySet("Left", 50);
                vPicture.OlePropertySet("Top", 10);
                //列名
// Insert2Excel(vSheet, ++iRows, );
                ++iRows;
                for (int i=0; i<lstViewPure->Columns->Count; ++i){
                //lstViewPure->Columns->Items[i]->Caption
                        vSheet.OlePropertyGet("Cells",iRows,i+1).OlePropertySet("Value",lstViewPure->Columns->Items[i]->Caption.c_str());
                }
                //数据
            TListItem *pItem;
            for(int i=0;i<lstViewPure->Items->Count;i++)
            {
                ++iRows;
                iCols = 0;
     pItem=lstViewPure->Items->Item[i];
                if (lbGoodsPerf->Caption != "正常单"){
                        vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",pItem->Caption.c_str());
                        for (int i=1; i<lstViewPure->Columns->Count; ++i){
                                vSheet.OlePropertyGet("Cells",iRows,i+1).OlePropertySet("Value",pItem->SubItems->Strings[i-1].c_str());
                        }
}
           }
          
                //加框
// AnsiString strRange = "A"+IntToStr(2)+":"+AnsiString(NumbertoString(lstViewPure->Columns->Count+1))+IntToStr(iRows);
                AnsiString strRange = "A"+IntToStr(2)+":"+AnsiString(NumbertoString(1+pos_pure))+IntToStr(iRows);
                vRange = vSheet.OlePropertyGet("Range",strRange.c_str());
                vRange.OlePropertySet("VerticalAlignment", 3);
                vRange.OlePropertySet("HorizontalAlignment", 3);
                vBorders = vRange.OlePropertyGet("Borders");
                vBorders.OlePropertySet("linestyle",xlContinuous);
                vBorders.OlePropertySet("weight",xlThin);
                vBorders.OlePropertySet("colorindex",xlAutomatic);

                //账号信息
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                AnsiString strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge", true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
/* AnsiString strAccount1 = "账号：4758 5020 1880 8049 23\r\n \*/
                AnsiString strAccount1 = "账号：7068 5641 1524\r\n \
开户行：中国银行广州市茶窖支行\r\n \
户名：邱亚才\r\n \
帐户性质：活期一本通";

                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge", true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                strAccount1 = "账号：6228 4800 8389 9556 910\r\n \
开户行：农行番禺德安支行\r\n \
户名：屈艳仟";
                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge", true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                strAccount1 ="账号：3602 0242 0100 0738 803\r\n \
开户行：工行万丰支行 \r\n \
户名：蒙赤勇";
                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                /////////////////////////////////////////////////////////////////////////////////////
                vSheet.OleProcedure("SaveAs", sfile.c_str());

                vWorkBook.OleProcedure("Close");

                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
                ShowMessage("导出完毕");


        }catch(...){
                ShowMessage("导出失败");
        }

}
//---------------------------------------------------------------------------


void __fastcall TFinanceForm::c(TObject *Sender)
{
/*
object Panel10: TPanel
Left = 1103
Top = 51
Width = 60
Height = 21
BevelInner = bvLowered
BevelOuter = bvLowered
Caption = #25253#20851#36153
Font.Charset = DEFAULT_CHARSET
Font.Color = clWindowText
Font.Height = -12
Font.Name = 'Tahoma'
Font.Style = [fsBold]
ParentColor = True
ParentFont = False
TabOrder = 21
end
object edtCustFree: TEdit
Left = 1164
Top = 51
Width = 80
Height = 21
ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
TabOrder = 20
end
*/
}
//---------------------------------------------------------------------------

void TFinanceForm::flushColumnNo(){
        int cnt_row = lstView->Items->Count;
        int column_no=0;
        if (cnt_row>0){
                for (int row=0; row<(cnt_row-1); ++row) {
                        column_no++;
// lstView->Items->Item[row]->SubItems->Strings[0] = column_no;
                        lstView->Items->Item[row]->Caption = column_no;
                }
        }
}
