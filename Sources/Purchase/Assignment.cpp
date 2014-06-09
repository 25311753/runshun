//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <FileCtrl.hpp>
#include "Assignment.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
/*
#include "OleExcelCom.h"
#include "Excel_2K_SRVR2.h"
#include <OleServer.hpp>
*/
#include "common.hpp"

#include <assert.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAssignmentForm *AssignmentForm;
//---------------------------------------------------------------------------
void Assignment(int nAuth)
{
        CALL_FORM(TAssignmentForm);
}
__fastcall TAssignmentForm::TAssignmentForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

CString getFirstContainerNo(AnsiString c)
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
//			printf("head:[%s] tail:[%s]\n", str1, strTmp1);
//			printf("bno:[%s] type:[%s]\n\n", str3, str4);
                rt = str3;
        }
        return rt;
}

std::map<CString, std::pair<CString, CString> > genContainerInfoDetail(AnsiString c)
{

        std::map<CString, std::pair<CString, CString> > rt;
        rt.clear();
        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num; ++i){
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
//			printf("head:[%s] tail:[%s]\n", str1, strTmp1);
//			printf("bno:[%s] type:[%s]\n\n", str3, str4);
//                rt = str3;
                rt.insert(std::make_pair(str3, std::make_pair(str4, strSealId)));
        }
/*
                        for (std::map<CString, std::pair<CString, CString> >::iterator it=c.begin(); it!=c.end(); ++it){
                                CString ss;
                                ss.Format("%s %s %s", it->first, it->second.first, it->second.second);
                                ShowMessage(AnsiString(ss));
                        }
*/        
        return rt;
}
void TAssignmentForm::flushContainer(AnsiString c){
        lstViewContainer->Items->Clear();

		char cnt[10];memset(cnt,sizeof(cnt),0x00);
		char body[2048];memset(body,sizeof(body),0x00);
		sscanf(c.c_str(),"%[^|]|",cnt);
		sscanf(c.c_str(),"%*[^|]|%[^@]",body);

		char strTmp1[2048];
		memset(strTmp1,sizeof(strTmp1),0x00);
		strcpy(strTmp1,body);
                int num = StrToInt(cnt);
		for (int i =0; i<num; ++i){
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
//			printf("head:[%s] tail:[%s]\n", str1, strTmp1);
//			printf("bno:[%s] type:[%s]\n\n", str3, str4);

                        TListItem *pItem =lstViewContainer->Items->Add();
                        assert(pItem!=NULL);
                        pItem->Caption=AnsiString(str3);
                        pItem->SubItems->Add(AnsiString(str4));
                        pItem->SubItems->Add(AnsiString(strSealId));

		}
}

void TAssignmentForm::Load2ListView(TListView **pLstView, LPCSTR cid){
        TListView *p= *pLstView;
        if (p == NULL )
                return;
        //if exist return
        for (int i=0; i<p->Items->Count; ++i) {
             if (p->Items->Item[i]->Caption == cid)
                return;
        }
        //~
	TListItem *pItem =(*pLstView)->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=cid;
}
void __fastcall TAssignmentForm::btnQueryClick(TObject *Sender)
{

        edtCid->Text = edtCid->Text.Trim();
        unsigned short year0,month0,day0;
	dtpAcceptDateBegin->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d%02d%02d 23:59:59",year1,month1,day1);

        CString szSQL;
        szSQL="select cid,status from customs where 1=1 ";
        if (!edtCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtCid->Text.c_str());
        }
        if (!edtOperUnit->Text.IsEmpty()) {
                szSQL += " and operunit="; szSQL += Str2DBString(edtOperUnit->Text.c_str());
        }
        if (!edtLadingId->Text.IsEmpty())   {
                szSQL += " and ladingid="; szSQL += Str2DBString(edtLadingId->Text.c_str());
        }
        if (!cbbTransport->Text.IsEmpty())   {
                szSQL += " and transport="; szSQL += Str2DBString(cbbTransport->Text.c_str());
        }
        if (!cbbStatus->Text.IsEmpty()){
                szSQL += " and status="; szSQL += Str2DBString(cbbStatus->Text.c_str());
        }
        if (!edtContainerNo->Text.IsEmpty()){
                szSQL += " and containerinfo like '%"; szSQL += edtContainerNo->Text.c_str(); szSQL += "%' ";
        }
        if (cbIsQryByDate->Checked){
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
                szSQL += " order by endcustdate";
        }

//        edtDebug->Text = AnsiString(szSQL);
//        TListItem *pItem;
//        lstViewDown->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);

	if(dm1->Query1->Eof){
                ShowMessage("记录不存在");
	}
	while(!dm1->Query1->Eof)
	{
                AnsiString szStatus = dm1->Query1->FieldByName("status")->AsString;
                TListView *plv = NULL;
                if (szStatus == "已接单"){
                  plv = lstViewYJD;
                } else if (szStatus == "单证处理中"){
                  plv = lstViewDZCLZ;
                } else if (szStatus == "海关审核中"){
                  plv = lstViewSH;
                } else if (szStatus == "查验中") {
                  plv = lstViewCYZ;
                } else if (szStatus == "已放行"){
                  plv = lstViewYFX;
                } else if (szStatus == "已交放行条"){
                  plv = lstViewYJCZ;
                } else if (szStatus == "已结汇"){
                  plv = lstViewYJH;
                } else if (szStatus == "预报检"){
                  plv = lstViewYBJ;
                }



                Load2ListView(&plv, dm1->Query1->FieldByName("cid")->AsString.c_str());
		dm1->Query1->Next();
        }
        edtCid->Text = "";
}
//---------------------------------------------------------------------------
void TAssignmentForm::ChangeStatus(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus){
        CString strOldCidList = "1";
        for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                strOldCidList += ",";
                strOldCidList += (*pOldLstView)->Items->Item[i]->Caption.c_str();
        }

                CString szSQL;
                szSQL = "update customs set status=";
                szSQL += Str2DBString(newStatus.c_str());
                szSQL += " where cid in (";
                szSQL += strOldCidList;
                szSQL += ")";
                if(!RunSQL(dm1->Query1,szSQL))
                {
                       ShowMessage("update status fail!") ;
                       return;
                }
                 //add new
                for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                        TListItem *pItemNew =(*pNewLstView)->Items->Add();
                        assert(pItemNew!=NULL);
                        pItemNew->Caption = (*pOldLstView)->Items->Item[i]->Caption.c_str();
                }

                //del old
                (*pOldLstView)->Clear();
                
/*        TListItem *pItemOld;
        pItemOld = (*pOldLstView)->Selected;
        if (pItemOld==NULL){
                return;
        }
                CString szSQL;
                szSQL = "update customs set status=";
                szSQL += Str2DBString(newStatus.c_str());
                szSQL += " where cid=";
                szSQL += Str2DBString(pItemOld->Caption.c_str());
                if(!RunSQL(dm1->Query1,szSQL))
                {
                       ShowMessage("update status fail!") ;
                       return;
                }
                //add new
               	TListItem *pItemNew =(*pNewLstView)->Items->Add();
                assert(pItemNew!=NULL);
                pItemNew->Caption=pItemOld->Caption;
                //del old
                (*pNewLstView)->Selected->Delete();
*/
}
 void TAssignmentForm::ChangeStatusSelected(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus){
        CStringArray flg_selected_old;
        for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                flg_selected_old.Add("");
        }

        CString strOldCidList = "1";
        for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                if((*pOldLstView)->Items->Item[i]->Selected == false)
                        continue;
                strOldCidList += ",";
                strOldCidList += (*pOldLstView)->Items->Item[i]->Caption.c_str();
                //mark selected of oldList
                flg_selected_old.SetAt(i,"1");
        }

                CString szSQL;
                szSQL = "update customs set status=";
                szSQL += Str2DBString(newStatus.c_str());
                szSQL += " where cid in (";
                szSQL += strOldCidList;
                szSQL += ")";
                if(!RunSQL(dm1->Query1,szSQL))
                {
                       ShowMessage("update status fail!") ;
                       return;
                }
//                Edit1->Text = AnsiString(szSQL);
                 //add new first
                for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                        if((*pOldLstView)->Items->Item[i]->Selected == false)
                                continue;

                        TListItem *pItemNew =(*pNewLstView)->Items->Add();
                        assert(pItemNew!=NULL);
                        pItemNew->Caption = (*pOldLstView)->Items->Item[i]->Caption.c_str();
//                        (*pOldLstView)->Items->Item[i]->Delete();
                }
                //then del old.
                for(int i = 0; i < (*pOldLstView)->Items->Count; i++){
//                        ShowMessage(AnsiString(flg_selected_old.GetSize()));
                        if((*pOldLstView)->Items->Item[i]->Selected == true) {
                                (*pOldLstView)->Items->Item[i]->Delete();
                                i--;
                        }
                }

}

void TAssignmentForm::ChangeStatusSelectedPass(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus){
        CStringArray flg_selected_old;
        for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                flg_selected_old.Add("");
        }

        CString strOldCidList = "1";
        for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                if((*pOldLstView)->Items->Item[i]->Selected == false)
                        continue;
                strOldCidList += ",";
                strOldCidList += (*pOldLstView)->Items->Item[i]->Caption.c_str();
                //mark selected of oldList
                flg_selected_old.SetAt(i,"1");
        }
        char strDate0[80];
        sprintf(strDate0, "%s", "-");
        if (newStatus == "已放行"){
                TDateTime tDate=GetSysTime(false);
                dtpPassDate->DateTime=tDate;
                unsigned short year0,month0,day0,hour0,minute0,sec0,msec0;
                dtpPassDate->DateTime.DecodeDate(&year0,&month0,&day0);
                dtpPassDate->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
           	//sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);
                sprintf(strDate0,"%04d-%02d-%02d %02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);
        }

                CString szSQL;
                szSQL = "update customs set status=";
                szSQL += Str2DBString(newStatus.c_str());
                szSQL += " , pass_date=";
                szSQL += Str2DBString(strDate0);
                szSQL += " where cid in (";
                szSQL += strOldCidList;
                szSQL += ")";
                if(!RunSQL(dm1->Query1,szSQL))
                {
                       ShowMessage("update status fail!") ;
                       return;
                }
//                Edit1->Text = AnsiString(szSQL);
                 //add new first
                for(int i = 0;i < (*pOldLstView)->Items->Count;i++){
                        if((*pOldLstView)->Items->Item[i]->Selected == false)
                                continue;

                        TListItem *pItemNew =(*pNewLstView)->Items->Add();
                        assert(pItemNew!=NULL);
                        pItemNew->Caption = (*pOldLstView)->Items->Item[i]->Caption.c_str();
//                        (*pOldLstView)->Items->Item[i]->Delete();
                }
                //then del old.
                for(int i = 0; i < (*pOldLstView)->Items->Count; i++){
//                        ShowMessage(AnsiString(flg_selected_old.GetSize()));
                        if((*pOldLstView)->Items->Item[i]->Selected == true) {
                                (*pOldLstView)->Items->Item[i]->Delete();
                                i--;
                        }
                }

}
void __fastcall TAssignmentForm::btnCheckClick(TObject *Sender)
{

        AnsiString newStatus = "海关审核中";
        ChangeStatusSelected(&lstViewCYZ, &lstViewSH, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnPassClick(TObject *Sender)
{
        AnsiString newStatus = "已放行";
        ChangeStatusSelectedPass(&lstViewSH, &lstViewYFX, newStatus);
}
//---------------------------------------------------------------------------


void __fastcall TAssignmentForm::btnYJCZClick(TObject *Sender)
{
        AnsiString newStatus = "已交放行条";
        ChangeStatusSelected(&lstViewYFX, &lstViewYJCZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::FormShow(TObject *Sender)
{

        edtQryCid->Text = "";
        edtQryLading->Text = "";
        edtQryJZS->Text = "";
        

        TDateTime tDate=GetSysTime(false);
        dtpAcceptDateBegin->DateTime=tDate;
        dtpAcceptDateEnd->DateTime=tDate;
        dtpQryAcceptDate->DateTime=tDate;
        dtpQryAcceptDateEnd->DateTime=tDate;
               CString szSQL;

        cbbTransport->Items->Add("");
	szSQL.Format("select * from dictransport");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbTransport->Items->Add(dm1->Query1->FieldByName("tpname")->AsString);
//                m_lstTransport.Add(dm1->Query1->FieldByName("tpname")->AsString.c_str());
		dm1->Query1->Next();
        }
        cbbTransport->ItemIndex=0;
        cbbQryStatus->ItemIndex=0;
        cbbStatus->Items->Add("");
	szSQL.Format("select * from dicstatus");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbStatus->Items->Add(dm1->Query1->FieldByName("sname")->AsString);
                cbbQryStatus->Items->Add(dm1->Query1->FieldByName("sname")->AsString);

               // m_lstStatus.Add(dm1->Query1->FieldByName("sname")->AsString.c_str());
		dm1->Query1->Next();
        }

        cbbStatus->ItemIndex = 0;

        //船代
	szSQL.Format("select * from dicshipagent");
	RunSQL(szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbShipAgent->Items->Add(dm1->Query1->FieldByName("saname")->AsString);
		dm1->Query1->Next();
        }

        
}
//---------------------------------------------------------------------------


void __fastcall TAssignmentForm::btnSHClick(TObject *Sender)
{
        AnsiString newStatus = "海关审核中";
        ChangeStatusSelected(&lstViewDZCLZ, &lstViewSH, newStatus);
}
//---------------------------------------------------------------------------

/*
static String cstr[]={"零","壹","贰","叁","肆", "伍", "陆","柒","捌","玖"};
static String wstr[] ={ "", "", "拾", "佰", "仟", "万", "拾", "佰", "仟", "亿", "拾", "佰", "仟" };

int SplitString(TStringList *resultStringList,String splittStr,String sourceStr)
{
    resultStringList->Text = "";
    int splitterLength = splittStr.Length();
    int pos = sourceStr.Pos(splittStr);
    String tmp;
    while (pos > 0) {
        tmp = sourceStr.SubString(1, pos - 1);
        resultStringList->Add(tmp);
        sourceStr = sourceStr.SubString(pos + splitterLength, sourceStr.Length() - pos - splitterLength + 1);
        pos = sourceStr.Pos(splittStr);
    }
    resultStringList->Add(sourceStr);
    return resultStringList->Count;
}
*/
String ConvertInt(String oldString)
{
    oldString = oldString.Trim();
    TStringList * strList = new TStringList();
    int count = SplitString(strList, ".", oldString);
    if (count == 0 || count > 2) {
        ShowMessage("数字格式不正确！");
    }
    //整数部分
    String str = strList->Strings[0];
    if (str.Length() > 12) {
        ShowMessage("数字太大，不能处理！");
    }

    //处理整数部分
    int len = str.Length();
    String tmpstr, rstr;
    rstr="";

    TReplaceFlags   rf;
    rf   <<   rfReplaceAll;
    for (int i = 1; i <= len; i++) {
        tmpstr = str.SubString(len - i + 1, 1);
        rstr = cstr[StrToInt(tmpstr)] + wstr[i] + rstr;
    }

    rstr=StringReplace(rstr, "拾零", "拾", rf);
    rstr=StringReplace(rstr, "零拾", "零", rf);
    rstr=StringReplace(rstr, "零佰", "零", rf);
    rstr=StringReplace(rstr, "零仟", "零", rf);
    rstr=StringReplace(rstr, "零万", "万", rf);
    for (int i = 1; i <= 6; i++) {
        rstr = StringReplace(rstr, "零零", "零", rf);
    }
    rstr=StringReplace(rstr, "零万", "零", rf);
    rstr = StringReplace(rstr, "零亿", "亿", rf);
    rstr=StringReplace(rstr, "零零", "零", rf);
    rstr+="圆";

        //小数部分
    if (count == 2) {
        String strXiaoshu = strList->Strings[1];
        int xiaoshuLength = strXiaoshu.Length();
        if (xiaoshuLength == 1) {
            rstr += cstr[StrToInt(strXiaoshu)] + "角";
        } else if (xiaoshuLength >= 2 ) {
            rstr += cstr[StrToInt(strXiaoshu[1])] + "角" + cstr[StrToInt(strXiaoshu[2])] + "分";;
        } else if  (xiaoshuLength == 0) {
            rstr += "整";
        }
    }
    return rstr;
}



void __fastcall TAssignmentForm::btnSH2DZCLZClick(TObject *Sender)
{
        AnsiString newStatus = "单证处理中";
        ChangeStatusSelected(&lstViewSH, &lstViewDZCLZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYFX2SHClick(TObject *Sender)
{
        AnsiString newStatus = "海关审核中";
        ChangeStatusSelectedPass(&lstViewYFX, &lstViewSH, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJCZ2YFXClick(TObject *Sender)
{
        AnsiString newStatus = "已放行";
        ChangeStatusSelected(&lstViewYJCZ, &lstViewYFX, newStatus);
}
//---------------------------------------------------------------------------


void __fastcall TAssignmentForm::btnCYZ2SHClick(TObject *Sender)
{
        AnsiString newStatus = "查验中";
        ChangeStatusSelected(&lstViewSH, &lstViewCYZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnQryClick(TObject *Sender)
{

        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d%02d%02d 23:59:59",year1,month1,day1);

        CString szSQL;
        szSQL="select * from customs where 1=1 ";
        if (!edtQryCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtQryCid->Text.c_str());
        }
        if (!edtQryLading->Text.IsEmpty())   {
                szSQL += " and ladingid="; szSQL += Str2DBString(edtQryLading->Text.c_str());
        }
        if (!cbbQryStatus->Text.IsEmpty()){
                szSQL += " and status="; szSQL += Str2DBString(cbbQryStatus->Text.c_str());
        }
        if (!edtQryJZS->Text.IsEmpty()){
                szSQL += " and containerinfo like'%"; szSQL += edtQryJZS->Text.c_str(); szSQL+="%'";
        }
        if (!cbbShipAgent->Text.IsEmpty()){
                szSQL += " and shipagent="; szSQL += Str2DBString(cbbShipAgent->Text.c_str());
        }

        if (cbIsQryByDateUp->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
        }
        szSQL += " order by endcustdate";
        
        TListItem *pItem;
        lstView->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);

        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                return;
        }
        int column_no = 0;
	while(!dm1->Query1->Eof)
	{
                pItem=lstView->Items->Add();
//                pItem->Caption=dm1->Query1->FieldByName("cid")->AsString;
                pItem->Caption = ++column_no;
		pItem->SubItems->Add(dm1->Query1->FieldByName("cid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goodsperf")->AsString);

		pItem->SubItems->Add(dm1->Query1->FieldByName("operunit")->AsString);     
		pItem->SubItems->Add(dm1->Query1->FieldByName("ladingid")->AsString);

                pItem->SubItems->Add(AnsiString(getFirstContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString)));
		pItem->SubItems->Add(dm1->Query1->FieldByName("doer")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("endcustdate")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("shipagent")->AsString);     //0620

		pItem->SubItems->Add(dm1->Query1->FieldByName("status")->AsString);   
		pItem->SubItems->Add(dm1->Query1->FieldByName("beizhu")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("containerinfo")->AsString);
                lstViewContainer->Items->Clear();

		dm1->Query1->Next();
	}
        edtQryCid->Text = "";
//       	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{

        flushContainer(AnsiString(Item->SubItems->Strings[8+1+1].c_str()));//0620 add shipagent
}
//---------------------------------------------------------------------------



void __fastcall TAssignmentForm::edtQryCidKeyPress(TObject *Sender,
      char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        btnQryClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::edtCidKeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        btnQueryClick(Sender);
    }           
}
//---------------------------------------------------------------------------



void __fastcall TAssignmentForm::btnYJHClick(TObject *Sender)
{
        AnsiString newStatus = "已结汇";
        ChangeStatusSelected(&lstViewYJCZ, &lstViewYJH, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJH2YJCZClick(TObject *Sender)
{
        AnsiString newStatus = "已交放行条";
        ChangeStatusSelected(&lstViewYJH, &lstViewYJCZ, newStatus);
}
//---------------------------------------------------------------------------




void __fastcall TAssignmentForm::btnFlowTableClick(TObject *Sender)
{
        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d%02d%02d 23:59:59",year1,month1,day1);

        CString szSQL;
        szSQL="select * from customs where 1=1 ";
        if (!edtQryCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtQryCid->Text.c_str());
        }
        if (!edtQryLading->Text.IsEmpty())   {
                szSQL += " and ladingid="; szSQL += Str2DBString(edtQryLading->Text.c_str());
        }
        if (!cbbQryStatus->Text.IsEmpty()){
                szSQL += " and status="; szSQL += Str2DBString(cbbQryStatus->Text.c_str());
        }
        if (!edtQryJZS->Text.IsEmpty()){
                szSQL += " and containerinfo like'%"; szSQL += edtQryJZS->Text.c_str(); szSQL+="%'";
        }
        if (!cbbShipAgent->Text.IsEmpty()){
                szSQL += " and shipagent="; szSQL += Str2DBString(cbbShipAgent->Text.c_str());
        }
        
        if (cbIsQryByDateUp->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
                szSQL += " order by endcustdate";
        }

        RunSQL(dm1->Query1,szSQL,true);
        int row_cnt = dm1->Query1->RecordCount;
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                return;
        }

        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Columns").OlePropertyGet("Item",1).OlePropertySet("ColumnWidth",5);//设置个别列宽
                vSheet.OlePropertyGet("Columns").OlePropertyGet("Item",3).OlePropertySet("NumberFormatLocal","@");//设置数字格式


                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_row_height(30).set_font_type("楷体_GB2312").\
                                           set_font_style("加粗").set_font_size(24).set_alignment(3).\
                                           write("流程表");
                }

                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "N", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("序号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("工单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("报关单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("经营单位"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("提单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("集装箱号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("封条号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("柜型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("品名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("毛重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("截关日期"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("状态"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("备注"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;
                //add result
                while(!dm1->Query1->Eof){

                        AnsiString strCId = dm1->Query1->FieldByName("cid")->AsString;
                        AnsiString declareid = dm1->Query1->FieldByName("declareid")->AsString;
                        AnsiString containerinfo = dm1->Query1->FieldByName("containerinfo")->AsString;
                        std::map<CString, std::pair<CString, CString> > c = genContainerInfoDetail(containerinfo);

//                        for (std::map<CString, std::pair<CString, CString> >::iterator it=c.begin(); it!=c.end(); ++it){
                                tmp_column=1;
                                ole_helper_raw.write(AnsiString(++pos), iRows, tmp_column++);
                                ole_helper_raw.write(strCId, iRows, tmp_column++);
                                declareid = (declareid.Length() > 9)? \
                                                declareid.SubString(declareid.Length()-9+1,9):declareid;
                                ole_helper_raw.write(declareid, iRows, tmp_column++);
                                ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++);
                                ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);
                                //qry first mname
                                AnsiString rs_mname , rs_sum_casescnt, rs_sum_grossweight;
                                rs_mname = "";
                                rs_sum_casescnt = "";
                                rs_sum_grossweight = "";

                                CString szSQL_M = "";
                                szSQL_M.Format("select mname from customs_detail,merchandise where cdid like '%s__'  and cmid=mid order by cdid",strCId);
edtDebug->Text = AnsiString(szSQL_M);
                                RunSQL(dm1->Query2,szSQL_M,true);
                                if (!dm1->Query2->Eof){
                                        rs_mname = dm1->Query2->FieldByName("mname")->AsString;
                                }
                                //qry sum_casescnt sum_grossweight
                                CString szSQL_C = "";
                                szSQL_C.Format("select sum(casescnt) sum_casescnt, sum(grossweight) sum_grossweight from customs_detail where cdid like '%s__'",strCId);

                                RunSQL(dm1->Query3,szSQL_C,true);
                                if (!dm1->Query3->Eof){
                                        rs_sum_casescnt = dm1->Query3->FieldByName("sum_casescnt")->AsString;
                                        rs_sum_grossweight = dm1->Query3->FieldByName("sum_grossweight")->AsString;
                                }

//                                ole_helper_raw.write(AnsiString(getFirstContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString)), iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(c.begin()->first), iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(c.begin()->second.second), iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(c.begin()->second.first), iRows, tmp_column++);

                                ole_helper_raw.write(rs_mname, iRows, tmp_column++);
                                ole_helper_raw.write(rs_sum_casescnt, iRows, tmp_column++);
                                ole_helper_raw.write(rs_sum_grossweight, iRows, tmp_column++);

                                ole_helper_raw.write(dm1->Query1->FieldByName("endcustdate")->AsString, iRows, tmp_column++);
                                ole_helper_raw.write(dm1->Query1->FieldByName("status")->AsString, iRows, tmp_column++);
                                ole_helper_raw.write(dm1->Query1->FieldByName("beizhu")->AsString, iRows, tmp_column++);
                                iRows++;
//                        }
                        //if more then 1 container
                        if(c.size()>1){
                            std::map<CString, std::pair<CString, CString> >::iterator it=c.begin();
                            ++it;
                            for (; it!=c.end(); ++it){
                                tmp_column=1;
                                AnsiString str_empty = "";
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(it->first), iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(it->second.second), iRows, tmp_column++);
                                ole_helper_raw.write(AnsiString(it->second.first), iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                ole_helper_raw.write(str_empty, iRows, tmp_column++);
                                iRows++;
                             }
                        }
               		dm1->Query1->Next();

                }
                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "N", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }

        } catch(...){
        }

}
//---------------------------------------------------------------------------



void __fastcall TAssignmentForm::btnYJD2YJYClick(TObject *Sender)
{
        AnsiString newStatus = "预报检";
        ChangeStatusSelected(&lstViewYJD, &lstViewYBJ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJY2YJDClick(TObject *Sender)
{

        AnsiString newStatus = "已接单";
        ChangeStatusSelected(&lstViewYBJ, &lstViewYJD, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJY2DZCLZClick(TObject *Sender)
{
        AnsiString newStatus = "单证处理中";
        ChangeStatusSelected(&lstViewYBJ, &lstViewDZCLZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnDZCLZ2YJYClick(TObject *Sender)
{
        AnsiString newStatus = "预报检";
        ChangeStatusSelected(&lstViewDZCLZ, &lstViewYBJ, newStatus);
}
//---------------------------------------------------------------------------












void __fastcall TAssignmentForm::btnPass1Click(TObject *Sender)
{
        AnsiString newStatus = "查验中";
        ChangeStatusSelected(&lstViewYBJ, &lstViewCYZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYFX2CYZClick(TObject *Sender)
{
        AnsiString newStatus = "预报检";
        ChangeStatusSelected(&lstViewCYZ, &lstViewYBJ, newStatus);
}
//---------------------------------------------------------------------------
void TAssignmentForm::getFirstContainerAndType(AnsiString cinfos, CString& rt_c, CString& rt_ctype)
{
        char cnt[10]; memset(cnt,sizeof(cnt),0x00);
        char body[2048]; memset(body,sizeof(body),0x00);
        sscanf(cinfos.c_str(),"%[^|]|",cnt);
        sscanf(cinfos.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);


        for (int i =0; i<num && i<1; ++i){
                char str1[100],str2[100],str3[100], strTmp[2048];
                memset(str1,sizeof(str1),0x00);
                memset(str2,sizeof(str2),0x00);
                memset(str3,sizeof(str3),0x00);
                memset(strTmp,sizeof(strTmp),0x00);
                strcpy(strTmp,strTmp1);
                sscanf(strTmp,"%[^#]#",str1);
                sscanf(str1,"%s %s ",str2,str3);
                rt_c = str2;
                rt_ctype = str3;
        }
        return ;
}

AnsiString TAssignmentForm::mnameFilter(AnsiString mname)
{
        AnsiString rt_mname = mname;
                int pStar=mname.Pos(AnsiString("*"));
                if (pStar!=0){
                        rt_mname=mname.SubString(pStar+1, mname.Length()-1);
                }
                int pPoint=rt_mname.Pos(AnsiString("."));
                if (pPoint!=0){
                        rt_mname=rt_mname.SubString(0, rt_mname.Length()-1);
                }

        return rt_mname;
}

void __fastcall TAssignmentForm::Button1Click(TObject *Sender)
{
        //create dir
        AnsiString dirPath = "d:\\润顺_预配舱单\\";
        if (!ForceDirectories(dirPath))
        {
                ShowMessage(AnsiString("创建导出目录失败"));
                return;
        }
        AnsiString suffix = AnsiString(GetSysTime2());

        //check which to export
        std::map<AnsiString, int> map_target;
        map_target.clear();
        TListItem *pItem;
        for(int i=0;i<lstView->Items->Count;i++)
        {
                pItem=lstView->Items->Item[i];
                if (pItem->Checked){
                        map_target.insert(std::make_pair(pItem->SubItems->Strings[7], 1));
                }
        }
/*        for (std::map<AnsiString, int>::iterator it=map_target.begin(); it!=map_target.end(); ++it){
                ShowMessage(it->first);
        }
*/
        //~
        std::map<AnsiString, int>::iterator fit = NULL;
        /////////////////////// 俊励 SHIP_AGENT_JL///////////////////////////////////////////
    if(map_target.find("俊励") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "X", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("提单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人地址及联系人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人地址及联系人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("包装"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("毛重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货物海关状态"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("柜号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("尺寸"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("空重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("封条"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("装货码头"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("卸货港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("目的港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("船名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("航次"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("营运人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("报关公司"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知方"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知方地址及联系人"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "俊励"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select shanghao,ladingid, operunit,tbl_sum.sum_casescnt,tbl_sum.sum_grossweight,\
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '%s__' and cmid=mid order by cdid) as mname, \
                                containerinfo,sealid,boatname,boatorder \
                                from customs,\
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str());

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("TO ORDER"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("shanghao")->AsString, iRows, tmp_column++);
                                        AnsiString smname = mnameFilter(dm1->Query1->FieldByName("mname")->AsString);
                                        ole_helper_raw.write(smname.c_str(), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsFloat, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("件"), iRows, tmp_column++);             
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsFloat, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("1"), iRows, tmp_column++);

                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);
                                        ole_helper_raw.write(rt_ctype=="S"?AnsiString("20"):AnsiString(40), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("GP"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("F"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("NSA"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatname")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatorder")->AsString, iRows, tmp_column++);  
                                        ole_helper_raw.write(AnsiString("DCCMA"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("DCGZYS"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("THE SAME AS CONSIGNEE"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        iRows++;
                                }
                        }
                }

                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "X", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                //save file
                AnsiString sfile = dirPath+ AnsiString("\俊励(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
        } catch(...){
                ShowMessage("导出 俊励 失败");
        }
    }

        /////////////////////// 外代 ///////////////////////////////////////////
    if(map_target.find("外代") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "Y", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);

                        AnsiString srange = "A1:A1";
                        Variant m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Color", RGB(225,0,0));

                        srange = "G1:J1";
                        m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Color", RGB(225,0,0));

                        srange = "L1:L1";
                        m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Color", RGB(225,0,0));

                        srange = "S1:W1";
                        m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Color", RGB(225,0,0));

                        srange = "Y1:Y1";
                        m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Color", RGB(225,0,0));

                        srange = "A1:Y1";
                        m_vRange =  vSheet.OlePropertyGet("Range", srange.c_str());
                        m_vRange.OlePropertyGet("Interior").OlePropertySet("ColorIndex",6);

                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("放行条(提单号)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("BOOKING_NO"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("POL（装货港）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("POD（卸货港）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("FPOD（最终目的港）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("FDEST"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("CNTR_NO(集装箱号)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("SEAL_NO(封号)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("SZTP(箱型尺寸)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("F/E/P"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("OPR（箱属）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("WEIGHT（重量）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("TEMP（冷柜温度）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("IMDG（危品类别）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("UNNO"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("ovH(货物超高尺寸)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("ovP(货物左超宽尺寸)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("ovS(货物右超宽尺寸)"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("船编 航次"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货名+报关单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("报关行"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("PKG件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("包装类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("报关类型"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "外代"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select declareid,shanghao,ladingid, containerinfo,sealid,\
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '%s__' and cmid=mid order by cdid) as mname, \
                                tbl_sum.sum_casescnt,tbl_sum.sum_grossweight,boatno,boatorder \
                                from customs, \
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str()
                                );
//                                ShowMessage(AnsiString(szSQL));
//                                edtDebug->Text = AnsiString(szSQL);

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(rt_ctype=="S"?AnsiString("20"):AnsiString(40), iRows, tmp_column++);

                                        ole_helper_raw.write(AnsiString("F"), iRows, tmp_column++);  
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);

                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);

                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatno")->AsString+\
                                                AnsiString("/")+\
                                                dm1->Query1->FieldByName("boatorder")->AsString, iRows, tmp_column++);
//       pForm->qrlDeclareId->Caption = (edtDeclareid->Text.Length() > 9)? \
//                                        edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9):edtDeclareid->Text;
                                        AnsiString declareid_last9 = dm1->Query1->FieldByName("declareid")->AsString;
                                        declareid_last9 =  declareid_last9.Length() > 9 ?\
                                                                declareid_last9.SubString(declareid_last9.Length()-9+1, 9):declareid_last9;


                                        AnsiString smname = mnameFilter(dm1->Query1->FieldByName("mname")->AsString);
                                        ole_helper_raw.write(smname+\
                                        AnsiString("/")+\
                                        declareid_last9, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("shanghao")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);           
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("1"), iRows, tmp_column++);
                                        iRows++;
                                }
                        }
                }

                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "U", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                //save file
                AnsiString sfile = dirPath+ AnsiString("\外代(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
        } catch(...){
                ShowMessage("导出 外代 失败");
        }
    }
        /////////////////////// 中海 ///////////////////////////////////////////
    if(map_target.find("中海") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "AB", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("数据类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("船名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("航次"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("放行条提单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("柜号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("拼箱(Y/N）"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("封条号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("尺寸"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("包装方式"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("体积"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("重量"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("起运港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("目的港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("提单类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("唛头"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱属"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("重吉状态E/F"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人名称"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人地址"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人名称"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人地址"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知人名称"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知人地址"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("是否危品Y/N"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("是否货主自有箱Y/N"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "中海"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select boatname,boatorder,ladingid,containerinfo,sealid,operunit,shanghao,sum_casescnt,sum_grossweight, \
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '%s__' and cmid=mid order by cdid) as mname \
                                from customs, \
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str()
                                );
//                                ShowMessage(AnsiString(szSQL));
//                                edtDebug->Text = AnsiString(szSQL);

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;
                                        ole_helper_raw.write(AnsiString("预配"), iRows, tmp_column++);

                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatname")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatorder")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);

                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("N"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(rt_ctype=="S"?AnsiString("20"):AnsiString(40), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsString, iRows, tmp_column++);

                                        ole_helper_raw.write(AnsiString("件"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);

                                        ole_helper_raw.write(AnsiString("CNNSA"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);

                                        ole_helper_raw.write(mnameFilter(dm1->Query1->FieldByName("mname")->AsString), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("本地出口"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("N/M"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("CSC"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("F"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("shanghao")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("N"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("N"), iRows, tmp_column++);

                                        iRows++;
                                }
                        }
                }

                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "AB", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                //save file
                AnsiString sfile = dirPath+ AnsiString("\中海(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
        } catch(...){
                ShowMessage("导出 中海 失败");
        }
    }
       /////////////////////// 航商 ///////////////////////////////////////////
    if(map_target.find("航商") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "U", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("报关行名称"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("船名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("航次"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("流水号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("提单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("唛头"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("装货泊位"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("卸货港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("目的港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("柜号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("封条号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("尺寸类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱状态"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("包装"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("毛重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱毛重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("提单类型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱属"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "航商"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select boatname,boatorder,ladingid,containerinfo,sealid,operunit,sum_casescnt,sum_grossweight, \
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '2014051015__' and cmid=mid order by cdid) as mname \
                                from customs, \
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum   \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str()
                                );
//                                ShowMessage(AnsiString(szSQL));
//                                edtDebug->Text = AnsiString(szSQL);

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;
                                        ole_helper_raw.write(AnsiString("广州润顺国际货运代理有限公司"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatname")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatorder")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("N/M"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(mnameFilter(dm1->Query1->FieldByName("mname")->AsString), iRows, tmp_column++);  
                                        ole_helper_raw.write(AnsiString("南沙新港"), iRows, tmp_column++);   
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);

                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(rt_ctype=="S"?AnsiString("20"):AnsiString(40), iRows, tmp_column++);

                                        ole_helper_raw.write(AnsiString("F"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("纸箱"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);

                                        ole_helper_raw.write(AnsiString("海运直出"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("PIL"), iRows, tmp_column++);

                                        iRows++;
                                }
                        }
                }

                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "U", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                //save file
                AnsiString sfile = dirPath+ AnsiString("\航商(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
        } catch(...){
                ShowMessage("导出 航商 失败");
        }
    }
    /////////////////////// 联合 ///////////////////////////////////////////
    if(map_target.find("联合") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "X", iRows);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }
                int tmp_column=1;        
                ole_helper_raw.write(AnsiString("提单号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("发货人地址及联系人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人地址及联系人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("件数"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("包装"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("毛重"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("货物海关状态"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("柜号"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("尺寸"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("箱型"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("空重"), iRows, tmp_column++);                
                ole_helper_raw.write(AnsiString("封条"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("装货码头"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("卸货港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("目的港"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("船名"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("航次"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("营运人"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("报关公司"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知方"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("通知方地址及联系人"), iRows, tmp_column++);

                ++iRows;
                int start_row = iRows;
                int pos=0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "联合"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select boatname,boatorder,ladingid,containerinfo,sealid,shanghao,operunit,sum_casescnt,sum_grossweight, \
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '%s__' and cmid=mid order by cdid) as mname \
                                from customs, \
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str()
                                );
//                                ShowMessage(AnsiString(szSQL));
//                                edtDebug->Text = AnsiString(szSQL);

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;

                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++); 
                                        ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++);     
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);                                
                                        ole_helper_raw.write(dm1->Query1->FieldByName("shanghao")->AsString, iRows, tmp_column++);  
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(mnameFilter(dm1->Query1->FieldByName("mname")->AsString), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsString, iRows, tmp_column++); 
                                        ole_helper_raw.write(AnsiString("件"), iRows, tmp_column++);                         
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);   
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                                                                           
                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);
                                        ole_helper_raw.write(rt_ctype=="S"?AnsiString("20"):AnsiString(40), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("GP"), iRows, tmp_column++);                                         
                                        ole_helper_raw.write(AnsiString("F"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("CNNSA"), iRows, tmp_column++);   
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatname")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("boatorder")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("广州润顺国际货运代理有限公司"), iRows, tmp_column++);  
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);

                                        iRows++;
                                }
                        }
                }

                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "X", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                //save file
                AnsiString sfile = dirPath+ AnsiString("\联合(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;
        } catch(...){
                ShowMessage("导出 联合 失败");
        }
    }
    /////////////////////// 创富 ///////////////////////////////////////////
    if(map_target.find("创富") != map_target.end())
    {
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vWorkBook = vExcel.OlePropertyGet("ActiveWorkbook");
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
//                vExcel.OlePropertySet("Visible",true);
                vExcel.OlePropertySet("DisplayAlerts",false);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows").OlePropertySet("RowHeight",14);//设置所有列的列宽为28

//                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                {
                        AnsiString s = "预配头程日期﹕      装货港：      码头  目的港﹕       （香港或蛇口）      联系人：                        联系电话：                                              注意：合单报关及拼票务必注明";
                        OleHelper ole_helper(vSheet, "B", iRows, "L", iRows);
                        ole_helper.merge().set_font_type("楷体_GB2312").write(s);
                }

                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                int tmp_column=1;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "A", iRows+1);
                        ole_helper.merge(false).write(AnsiString("序号"));
                        tmp_column++;
                }
                ole_helper_raw.write(AnsiString("报关提单号"), iRows, tmp_column);
                ole_helper_raw.write(AnsiString("以订舱单号作为报关单号"), iRows+1, tmp_column++);
                {
                        OleHelper ole_helper(vSheet, "C", iRows, "C", iRows+1);
                        ole_helper.merge(false).write(AnsiString("柜号"));      
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "D", iRows, "D", iRows+1);
                        ole_helper.merge(false).write(AnsiString("装船封号"));
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "E", iRows, "E", iRows+1);   
                        ole_helper.merge(false).write(AnsiString("柜型"));
                        tmp_column++;                        
                }
                {
                        OleHelper ole_helper(vSheet, "F", iRows, "F", iRows+1);
                        ole_helper.merge(false).write(AnsiString("报关毛重（kgs）"));
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "G", iRows, "G", iRows+1);
                        ole_helper.merge(false).write(AnsiString("报关货名"));
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "H", iRows, "H", iRows+1);
                        ole_helper.merge(false).write(AnsiString("报关件数"));
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "I", iRows, "I", iRows+1);
                        ole_helper.merge(false).write(AnsiString("包装种类"));
                        tmp_column++;
                }
                {
                        OleHelper ole_helper(vSheet, "J", iRows, "K", iRows);
                        ole_helper.merge().write(AnsiString("运費支付方式"));
                }
                ole_helper_raw.write(AnsiString("预付"), iRows+1, tmp_column++);
                ole_helper_raw.write(AnsiString("到付"), iRows+1, tmp_column++);

                ole_helper_raw.write(AnsiString("付货人地址及姓名"), iRows, tmp_column);
                ole_helper_raw.write(AnsiString("即报关单上的发货单位"), iRows+1, tmp_column++);
                ole_helper_raw.write(AnsiString("收货人地址及姓名"), iRows, tmp_column);
                ole_helper_raw.write(AnsiString("东方海外货柜航运香港分行（香港中转货物）"), iRows+1, tmp_column++);

              

                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "M", iRows+1);
                        ole_helper.write_box().set_font_type("楷体_GB2312").set_font_style("加粗").set_alignment(3);
                }



                ++iRows;
                ++iRows;
                int start_row = iRows;
                int pos=0;
                int cnt_20 = 0;
                int cnt_40 = 0;

                //qry result according row'checkbox
                TListItem *pItem;
                for(int i=0;i<lstView->Items->Count;i++)
                {
                        pItem=lstView->Items->Item[i];
                        if (pItem->Checked && pItem->SubItems->Strings[7] == "创富"){
                                AnsiString cid = pItem->SubItems->Strings[0];
                                CString szSQL;
                                szSQL.Format("select boatname,boatorder,ladingid,containerinfo,sealid,shanghao, operunit,sum_casescnt,sum_grossweight, \
                                (select top 1 isnull(mname,'') as mname from customs_detail, merchandise where cdid like '%s__' and cmid=mid order by cdid) as mname \
                                from customs,\
                                (select '%s' as cid, isnull(sum(casescnt),0) as sum_casescnt, isnull(sum(grossweight),0) as sum_grossweight from customs_detail where cdid like '%s__') as tbl_sum \
                                where customs.cid = '%s' and customs.cid=tbl_sum.cid",
                                cid.c_str(), cid.c_str(), cid.c_str(), cid.c_str()
                                );
//                                ShowMessage(AnsiString(szSQL));
//                                edtDebug->Text = AnsiString(szSQL);

                                RunSQL(dm1->Query1,szSQL,true);
                                if (!dm1->Query1->Eof){
                                        tmp_column=1;

                                        ole_helper_raw.write(AnsiString(++pos)+AnsiString("#"), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("ladingid")->AsString, iRows, tmp_column++);

                                        AnsiString cinfos = dm1->Query1->FieldByName("containerinfo")->AsString;
                                        CString rt_c = "";
                                        CString rt_ctype = "";
                                        getFirstContainerAndType(cinfos, rt_c, rt_ctype);

                                        ole_helper_raw.write(AnsiString(rt_c), iRows, tmp_column++);  
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sealid")->AsString, iRows, tmp_column++);
                                        if (rt_ctype=="S"){
                                                cnt_20++;
                                                ole_helper_raw.write(AnsiString("20"), iRows, tmp_column++);
                                        }else{
                                                cnt_40++;
                                                ole_helper_raw.write(AnsiString("40"), iRows, tmp_column++);                                                
                                        }

                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_grossweight")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(mnameFilter(dm1->Query1->FieldByName("mname")->AsString), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("sum_casescnt")->AsString, iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("件"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString("*"), iRows, tmp_column++);
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        ole_helper_raw.write(dm1->Query1->FieldByName("operunit")->AsString, iRows, tmp_column++); 
                                        ole_helper_raw.write(AnsiString(""), iRows, tmp_column++);
                                        iRows++;
                                }
                        }
                }

                ole_helper_raw.write(AnsiString("合计:"), iRows, 2);
                {
                        OleHelper ole_helper(vSheet, "C", iRows, "D", iRows);
                        CString s;
                        s.Format("--%dX20' & --%dX40'", cnt_20, cnt_40);
                        ole_helper.merge().write(AnsiString(s));
                        tmp_column++;
                }
                iRows++;
                //write box
                {
                        OleHelper ole_helper(vSheet, "A", start_row, "M", iRows-1);
                        ole_helper.set_alignment(3).write_box();
                }
                ole_helper_raw.write(AnsiString("公司盖章:"), iRows, 2);
               
                //save file
                AnsiString sfile = dirPath+ AnsiString("\创富(润顺)_")+ suffix+".xls";
                vSheet.OleProcedure("SaveAs", sfile.c_str());
                vWorkBook.OleProcedure("Close");
                vExcel.OleFunction("Quit");
                vWorkBook = Unassigned;
                vExcel = Unassigned;

        } catch(...){
                ShowMessage("导出 创富 失败");
        }
    }
    ShowMessage("导出完毕");    
}
//---------------------------------------------------------------------------




