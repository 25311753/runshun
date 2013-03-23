//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

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
                ShowMessage("��¼������");
	}
	while(!dm1->Query1->Eof)
	{
                AnsiString szStatus = dm1->Query1->FieldByName("status")->AsString;
                TListView *plv = NULL;
                if (szStatus == "�ѽӵ�"){
                  plv = lstViewYJD;
                } else if (szStatus == "��֤������"){
                  plv = lstViewDZCLZ;
                } else if (szStatus == "���������"){
                  plv = lstViewSH;
                } else if (szStatus == "������") {
                  plv = lstViewCYZ;
                } else if (szStatus == "�ѷ���"){
                  plv = lstViewYFX;
                } else if (szStatus == "�ѽ�������"){
                  plv = lstViewYJCZ;
                } else if (szStatus == "�ѽ��"){
                  plv = lstViewYJH;
                }
                /*else
                {   //�սӵ�
                        AnsiString cid = edtCid->Text.c_str();
                        if (cid != "") {
                                  ShowMessage(cid+AnsiString(" :δ����"));
                        }

                } */
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
        if (newStatus == "�ѷ���"){
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
        AnsiString newStatus = "������";
        ChangeStatusSelected(&lstViewSH, &lstViewCYZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnPassClick(TObject *Sender)
{
        AnsiString newStatus = "�ѷ���";
        ChangeStatusSelectedPass(&lstViewSH, &lstViewYFX, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnPass1Click(TObject *Sender)
{
        AnsiString newStatus = "�ѷ���";
        ChangeStatusSelected(&lstViewCYZ, &lstViewYFX, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJCZClick(TObject *Sender)
{
        AnsiString newStatus = "�ѽ�������";
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

        //����
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
        AnsiString newStatus = "���������";
        ChangeStatusSelected(&lstViewDZCLZ, &lstViewSH, newStatus);
}
//---------------------------------------------------------------------------

/*
static String cstr[]={"��","Ҽ","��","��","��", "��", "½","��","��","��"};
static String wstr[] ={ "", "", "ʰ", "��", "Ǫ", "��", "ʰ", "��", "Ǫ", "��", "ʰ", "��", "Ǫ" };

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
        ShowMessage("���ָ�ʽ����ȷ��");
    }
    //��������
    String str = strList->Strings[0];
    if (str.Length() > 12) {
        ShowMessage("����̫�󣬲��ܴ���");
    }

    //������������
    int len = str.Length();
    String tmpstr, rstr;
    rstr="";

    TReplaceFlags   rf;
    rf   <<   rfReplaceAll;
    for (int i = 1; i <= len; i++) {
        tmpstr = str.SubString(len - i + 1, 1);
        rstr = cstr[StrToInt(tmpstr)] + wstr[i] + rstr;
    }

    rstr=StringReplace(rstr, "ʰ��", "ʰ", rf);
    rstr=StringReplace(rstr, "��ʰ", "��", rf);
    rstr=StringReplace(rstr, "���", "��", rf);
    rstr=StringReplace(rstr, "��Ǫ", "��", rf);
    rstr=StringReplace(rstr, "����", "��", rf);
    for (int i = 1; i <= 6; i++) {
        rstr = StringReplace(rstr, "����", "��", rf);
    }
    rstr=StringReplace(rstr, "����", "��", rf);
    rstr = StringReplace(rstr, "����", "��", rf);
    rstr=StringReplace(rstr, "����", "��", rf);
    rstr+="Բ";

        //С������
    if (count == 2) {
        String strXiaoshu = strList->Strings[1];
        int xiaoshuLength = strXiaoshu.Length();
        if (xiaoshuLength == 1) {
            rstr += cstr[StrToInt(strXiaoshu)] + "��";
        } else if (xiaoshuLength >= 2 ) {
            rstr += cstr[StrToInt(strXiaoshu[1])] + "��" + cstr[StrToInt(strXiaoshu[2])] + "��";;
        } else if  (xiaoshuLength == 0) {
            rstr += "��";
        }
    }
    return rstr;
}



void __fastcall TAssignmentForm::btnSH2DZCLZClick(TObject *Sender)
{
        AnsiString newStatus = "��֤������";
        ChangeStatusSelected(&lstViewSH, &lstViewDZCLZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYFX2SHClick(TObject *Sender)
{
        AnsiString newStatus = "���������";
        ChangeStatusSelectedPass(&lstViewYFX, &lstViewSH, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJCZ2YFXClick(TObject *Sender)
{
        AnsiString newStatus = "�ѷ���";
        ChangeStatusSelected(&lstViewYJCZ, &lstViewYFX, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYFX2CYZClick(TObject *Sender)
{
        AnsiString newStatus = "������";
        ChangeStatusSelected(&lstViewYFX, &lstViewCYZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnCYZ2SHClick(TObject *Sender)
{
        AnsiString newStatus = "���������";
        ChangeStatusSelected(&lstViewCYZ, &lstViewSH, newStatus);
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
                szSQL += " order by endcustdate";
        }

        TListItem *pItem;
        lstView->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);

        if (dm1->Query1->Eof){
                ShowMessage("��¼������");
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
        AnsiString newStatus = "�ѽ��";
        ChangeStatusSelected(&lstViewYJCZ, &lstViewYJH, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnYJH2YJCZClick(TObject *Sender)
{
        AnsiString newStatus = "�ѽ�������";
        ChangeStatusSelected(&lstViewYJH, &lstViewYJCZ, newStatus);
}
//---------------------------------------------------------------------------


void __fastcall TAssignmentForm::btnDZCLZClick(TObject *Sender)
{
        AnsiString newStatus = "��֤������";
        ChangeStatusSelected(&lstViewYJD, &lstViewDZCLZ, newStatus);
}
//---------------------------------------------------------------------------

void __fastcall TAssignmentForm::btnDZCLZ2YJDClick(TObject *Sender)
{
        AnsiString newStatus = "�ѽӵ�";
        ChangeStatusSelected(&lstViewDZCLZ, &lstViewYJD, newStatus);
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
                ShowMessage("��¼������");
                return;
        }

        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //��excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // ����������
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//�������������
                //������������
                vExcel.OlePropertySet("Visible",true);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//�������е�Ԫ����ı��Զ�����
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",20);//���������е��п�Ϊ28
                vSheet.OlePropertyGet("Columns").OlePropertyGet("Item",1).OlePropertySet("ColumnWidth",5);//���ø����п�
                vSheet.OlePropertyGet("Columns").OlePropertyGet("Item",3).OlePropertySet("NumberFormatLocal","@");//�������ָ�ʽ


                OleHelper ole_helper_raw(vSheet);
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_row_height(30).set_font_type("����_GB2312").\
                                           set_font_style("�Ӵ�").set_font_size(24).set_alignment(3).\
                                           write("���̱�");
                }

                ++iRows;
                //set style
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "N", iRows);
                        ole_helper.write_box().set_font_type("����_GB2312").set_font_style("�Ӵ�").set_alignment(3);
                }
                int tmp_column=1;
                ole_helper_raw.write(AnsiString("���"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("������"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("���ص���"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("��Ӫ��λ"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("�ᵥ��"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("��װ���"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("������"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("����"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("Ʒ��"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("����"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("ë��"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("�ع�����"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("״̬"), iRows, tmp_column++);
                ole_helper_raw.write(AnsiString("��ע"), iRows, tmp_column++);

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

