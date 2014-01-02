//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vector>
#include "Tailer.h"

#include "PrnCYD.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common_busi.hpp"
#include "common.hpp"
#include <assert.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TTailerForm *TailerForm;

#define DECIMAL_PLACE_FARE 2
#define DECIMAL_PLACE_CHARGE 2
#define DECIMAL_PLACE_COST 2

enum E_TAILER_COL_NAME{
	COL_OPDATE = 0,
        COL_CLIENT,
        COL_LADING,
        COL_CONTAINER_NO,
        COL_SEALID,
        COL_CONTAINER_TYPE,
        COL_CONTAINER_CNT,
        COL_TRANCOMPANY,
        COL_DRIVER,
        COL_CARNO,
        COL_GOODSPERF,
        COL_FARE,
        COL_FAREOUT,
        COL_TOTAL_CHARGE,
        COL_TOTAL_COST,
        COL_LIRUN,
        COL_CONTAINERINFO,
        COL_LOADADDRESS,
        COL_LOADLINKMAN,
        COL_LOADTEL,
        COL_BEIZHU,
        COL_CHARGE_COST,
        COL_ID,
};
//---------------------------------------------------------------------------
void Tailer(int nAuth)
{
        CALL_FORM(TTailerForm);
}
__fastcall TTailerForm::TTailerForm(TComponent* Owner)
        : TForm(Owner)
{
        m_enWorkState=EN_IDLE;
        m_selected_id = 0;
        m_mVarCharge.clear();
        int i=1;
        m_mVarCharge.insert(std::make_pair(i++, new CVarCharge(cbbVarChargeName1, edtCharge1, edtCost1)));
        m_mVarCharge.insert(std::make_pair(i++, new CVarCharge(cbbVarChargeName2, edtCharge2, edtCost2)));
        m_mVarCharge.insert(std::make_pair(i++, new CVarCharge(cbbVarChargeName3, edtCharge3, edtCost3)));
        m_mVarCharge.insert(std::make_pair(i++, new CVarCharge(cbbVarChargeName4, edtCharge4, edtCost4)));
        m_mVarCharge.insert(std::make_pair(i++, new CVarCharge(cbbVarChargeName5, edtCharge5, edtCost5)));
}

__fastcall TTailerForm::~TTailerForm(void){
        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end(); ++it){
                CVarCharge *d = it->second;
                delete d;
                d=NULL;
        }
}
//---------------------------------------------------------------------------
void TTailerForm::clean_input(){
        cbbClient->Text = "";
        edtLading->Text = "";
        edtLoadAddress->Text = "";
        cbbGoodsPerf->ItemIndex = -1;
        cbbGoodsPerf->Text = "";
        edtLoadLinkMan->Text = "";
        edtLoadTel->Text = "";
        edtTranCompany->Text = "";
        edtFare->Text = "";
        edtFareOut->Text = "";
        edtCarNo->Text = "";
        edtDriver->Text = "";
        edtBeiZhu->Text = "";
        edtContainerNo->Text = "";
        edtSealId->Text = "";
        lstViewContainer->Clear();        

        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpOpDateYYYYMMDD->DateTime=tNow;
        dtpOpDateHHMM->Time = EncodeTime(17,00,00,0);

        // var charge
        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end(); it++){
                CVarCharge *d = it->second;
                d->cbbName->ItemIndex = 0;
                d->edtCharge->Text = "";
                d->edtCost->Text = "";
        }

}
//---------------------------------------------------------------------------
void TTailerForm::clean_query(){
        cbbQryClient->ItemIndex = -1;
        cbbQryClient->Text = "";
        edtQryLading->Text = "";
        edtQryJZS->Text = "";
        cbbQryGoodsPerf->ItemIndex = -1;
        cbbQryGoodsPerf->Text = "";
        edtQryTranCompany->Text = "";
        edtQryDriver->Text = "";
        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpQryOpDate->DateTime=tNow;
        dtpQryOpDateEnd->DateTime=tNow;
}
//---------------------------------------------------------------------------
void __fastcall TTailerForm::FormShow(TObject *Sender)
{
        lstViewDown->Clear();
        //init varcharname first
        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                CVarCharge *d = it->second;
                d->cbbName->Items->Add("");
        }

        CString szSQL;
        szSQL.Format("select * from charges order by chid");
        RunSQL(dm1->Query1,szSQL,true);

        while(!dm1->Query1->Eof)
        {
                int chid = dm1->Query1->FieldByName("chid")->AsInteger;
                AnsiString chname = dm1->Query1->FieldByName("chname")->AsString;

                for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                        CVarCharge *d = it->second;
                        d->cbbName->Items->Add(chname);
                }
                dm1->Query1->Next();
        }
        //~
        clean_input();
        clean_query();              
        m_enWorkState=EN_IDLE;
        ResetCtrl();
}
//---------------------------------------------------------------------------


void __fastcall TTailerForm::btnClearQryCondClick(TObject *Sender)
{
        clean_query();        
}
//---------------------------------------------------------------------------
void TTailerForm::ResetCtrl(){
  if(m_enWorkState==EN_IDLE)
  {
    bool isSelected = (lstViewDown->Selected!=NULL);
    lstViewDown->Enabled = true;

    //btn
    btnAdd->Enabled=true;
    btnMod->Enabled=isSelected;
    btnDel->Enabled=isSelected;
    btnOK->Enabled =false;
    btnCancel->Enabled=false;

    //input all disable
    pl_input->Enabled = false; 
    pl_input_varcharge->Enabled = false;

    //qry area  enable
    pl_query->Enabled = true; 

    

  }
  else
  {
    //btn
    btnAdd->Enabled=false;
    btnMod->Enabled=false;
    btnDel->Enabled=false;
    btnOK->Enabled =true;
    btnCancel->Enabled=true;

    lstViewDown->Enabled=false;

    //input all enable
    pl_input->Enabled = true;
    pl_input_varcharge->Enabled = true;

    //qry area disable
    pl_query->Enabled = false;
  }
}

//---------------------------------------------------------------------------



void __fastcall TTailerForm::btnAddClick(TObject *Sender)
{
        clean_input();
	ResetCtrl();
        if(cbbClient->CanFocus())
                cbbClient->SetFocus();
        m_enWorkState=EN_ADDNEW;
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnQueryClick(TObject *Sender)
{
        unsigned short year0,month0,day0;
	dtpQryOpDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryOpDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d-%02d-%02d 23:59:59",year1,month1,day1);

        //
        CString szSQL;
        szSQL="select *,substring(containerinfo,0,charindex('|',containerinfo)) as cnt_con \
                from tailer where 1=1 ";
        if (!cbbQryClient->Text.IsEmpty()) {
                szSQL += " and client="; szSQL += Str2DBString(cbbQryClient->Text.c_str());
        }
        if (!edtQryLading->Text.IsEmpty())   {
                szSQL += " and ladingid="; szSQL += Str2DBString(edtQryLading->Text.c_str());
        }
        if (!edtQryJZS->Text.IsEmpty()){
                szSQL += " and containerinfo like'%"; szSQL += edtQryJZS->Text.c_str(); szSQL+="%'";
        }
        if (!edtQryTranCompany->Text.IsEmpty()){
                szSQL += " and trancompany="; szSQL += Str2DBString(edtQryTranCompany->Text.c_str());
        }
        if (!edtQryDriver->Text.IsEmpty()){
                szSQL += " and driver="; szSQL += Str2DBString(edtQryDriver->Text.c_str());
        }
        if (!cbbQryGoodsPerf->Text.IsEmpty()){
                szSQL += " and goodsperf="; szSQL += Str2DBString(cbbQryGoodsPerf->Text.c_str());
        }

        if (cbIsQryByDate->Checked) {
                szSQL += " and opdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
        }
//        szSQL += " order by CONVERT(varchar(100), acceptdate, 23), endcustdate";   //accpetdate格式化yyyymmdd排序，以免endcustdate排序受干扰
        szSQL += " order by opdate";
        TListItem *pItem;
        lstViewDown->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);

        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                return;
        }

        int column_no = 0;
	while(!dm1->Query1->Eof)
	{
                column_no++;
                pItem=lstViewDown->Items->Add();
                pItem->Caption= column_no;
                pItem->SubItems->Add(dm1->Query1->FieldByName("opdate")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("client")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("ladingid")->AsString);
                int cnt = 0;
                AnsiString containerno = "";
                AnsiString type = "";
                AnsiString sealid = "";
                getFirstContainerUnit(dm1->Query1->FieldByName("containerinfo")->AsString, cnt, containerno, type, sealid);
                pItem->SubItems->Add(containerno);
                pItem->SubItems->Add(sealid);
                pItem->SubItems->Add(type);
                pItem->SubItems->Add(cnt);
		pItem->SubItems->Add(dm1->Query1->FieldByName("trancompany")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("driver")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("carno")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goodsperf")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("fare")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("fareout")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("total_charge")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("total_cost")->AsFloat);
                double lirun = dm1->Query1->FieldByName("fare")->AsFloat - \
                               dm1->Query1->FieldByName("fareout")->AsFloat + \
                               dm1->Query1->FieldByName("total_charge")->AsFloat - \
                               dm1->Query1->FieldByName("total_cost")->AsFloat ;
                pItem->SubItems->Add(lirun);
                pItem->SubItems->Add(dm1->Query1->FieldByName("containerinfo")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("loadaddress")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("loadlinkman")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("loadtel")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("beizhu")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("charge_cost")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("tid")->AsInteger);

                lstViewContainer->Items->Clear();

		dm1->Query1->Next();
	}
       	ResetCtrl();
        clean_input();
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnModClick(TObject *Sender)
{
        m_enWorkState=EN_EDIT;
        ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbClientSelect(TObject *Sender)
{
        int nSel = cbbClient->ItemIndex;
        if (nSel == -1)
                return;        
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbClientChange(TObject *Sender)
{
        cbbClient->Items->Clear();

        AnsiString val = cbbClient->Text;
        if (cbbClient->Text.IsEmpty()) {
                return;
        }
        cbbClient->SelStart = AnsiString(cbbClient->Text).Length();
        CString szSQL;
	szSQL.Format("select shortname,customs_charge from client where shortname like '%%%s%%'", cbbClient->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

	while(!dm1->Query1->Eof)
	{
                cbbClient->Items->Add(dm1->Query1->FieldByName("shortname")->AsString); //0107
		dm1->Query1->Next();
        }

        cbbClient->Text = val;
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbQryClientSelect(TObject *Sender)
{
        int nSel = cbbQryClient->ItemIndex;
        if (nSel == -1)
                return;           
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbQryClientChange(TObject *Sender)
{
        cbbQryClient->Items->Clear();

        AnsiString val = cbbQryClient->Text;
        if (cbbQryClient->Text.IsEmpty()) {
                return;
        }
        cbbQryClient->SelStart = AnsiString(cbbQryClient->Text).Length();
        CString szSQL;
	szSQL.Format("select shortname,customs_charge from client where shortname like '%%%s%%'", cbbClient->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

	while(!dm1->Query1->Eof)
	{
                cbbQryClient->Items->Add(dm1->Query1->FieldByName("shortname")->AsString); //0107
		dm1->Query1->Next();
        }

        cbbQryClient->Text = val;
}
//---------------------------------------------------------------------------


void __fastcall TTailerForm::lstViewContainerSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        edtContainerNo->Text = Item->Caption;
        cbbContainerType->ItemIndex=cbbContainerType->Items->IndexOf(Item->SubItems->Strings[0]);
        edtSealId->Text = Item->SubItems->Strings[1];
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnAddContainerClick(TObject *Sender)
{
        edtContainerNo->Text = Trim(edtContainerNo->Text);
        if(edtContainerNo->Text.IsEmpty() || edtSealId->Text.IsEmpty()){
                ShowMessage("请输入箱号和封条号");
                if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
                return;
        }
        if (!chkFormatContainerNo(edtContainerNo->Text)){
                return;
        }

	TListItem *pItem =lstViewContainer->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=edtContainerNo->Text;
        pItem->SubItems->Add(cbbContainerType->Text);
        pItem->SubItems->Add(edtSealId->Text);

        edtContainerNo->Text = "";
        edtSealId->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnModContainerClick(TObject *Sender)
{
  if(lstViewContainer->Selected == NULL)
  {
    ShowMessage("请选择记录");
    if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
    return;
  }
  for(int i=0;i<lstViewContainer->Items->Count;i++) {
      TListItem *pItem;
      pItem = lstViewContainer->Items->Item[i];
      if (pItem!=lstViewContainer->Selected && pItem->Caption == edtContainerNo->Text) {
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n 柜号“%s”有重复,继续修改吗？  \n",edtContainerNo->Text.c_str());
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
      }
  }
  if (!chkFormatContainerNo(edtContainerNo->Text)){
        return;
  }
        TListItem *pItem;
        pItem = lstViewContainer->Selected;
        if (pItem!=NULL){
                pItem->Caption = edtContainerNo->Text;
                pItem->SubItems->Strings[0] = cbbContainerType->Text;
                pItem->SubItems->Strings[1] = edtSealId->Text;

        }
                
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnDelContainerClick(TObject *Sender)
{
  if(lstViewContainer->Selected == NULL)
  {
    ShowMessage("请选择记录");
    if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
    return;
  }
          lstViewContainer->Selected->Delete();           
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;
  int oldState=m_enWorkState;
  
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      if (-1 == addData(Sender))
        return;
      break;
    case EN_EDIT:
       modData(Sender);
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }
  TListItem *pItem;
  if(m_enWorkState==EN_ADDNEW)
  {
//     pItem=lstViewdown->Items->Add();
//    pItem->Caption=edtName->Text;
//    lstViewdown->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
        refreshMod();
  }
  m_enWorkState=EN_IDLE;
  ResetCtrl();
//      btnMod->Enabled=false;
//    btnDel->Enabled=false;
    if(oldState==EN_EDIT){
       lstViewDown->Selected=NULL;
    }        
}
//---------------------------------------------------------------------------
int TTailerForm::addData(TObject *Sender){
        int rt = -1;

        if(cbbClient->Text.IsEmpty() || edtLading->Text.IsEmpty() || edtLoadAddress->Text.IsEmpty() || \
              edtLoadLinkMan->Text.IsEmpty() || edtLoadTel->Text.IsEmpty() || edtTranCompany->Text.IsEmpty() || \
              edtFare->Text.IsEmpty() || edtFareOut->Text.IsEmpty() || edtCarNo->Text.IsEmpty() || edtDriver->Text.IsEmpty() || \
              lstViewContainer->Items->Count == 0)
        {
                ShowMessage("请检查你的输入信息");
                return rt;
        }

        if (!chk_charge_valid()){
                ShowMessage("请检查费用输入部分(空输入或费用有重复)");
                return rt;
        }

        //gen date        
        CString szSQL;
        szSQL="insert into tailer(client, opdate, ladingid, loadaddress, loadlinkman, loadtel, \
                                containerinfo, fare, fareout, charge_cost, total_charge,\
                                total_cost, trancompany, carno, driver, beizhu, goodsperf) \
                        values(";
        szSQL += Str2DBString(cbbClient->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM));
        szSQL +=","; szSQL += Str2DBString(edtLading->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtLoadAddress->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtLoadLinkMan->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtLoadTel->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(GetContainerInfo(lstViewContainer));
        szSQL +=","; szSQL += Text2DBFloat(edtFare->Text.IsEmpty()?AnsiString("0"):edtFare->Text,4).c_str();
        szSQL +=","; szSQL += Text2DBFloat(edtFareOut->Text.IsEmpty()?AnsiString("0"):edtFareOut->Text,4).c_str();
        szSQL +=","; szSQL += Str2DBString(GetTailerChargeInfo());
        szSQL +=","; szSQL += Text2DBFloat(edtTotalCharge->Text.IsEmpty()?AnsiString("0"):edtTotalCharge->Text,DECIMAL_PLACE_CHARGE).c_str();
        szSQL +=","; szSQL += Text2DBFloat(edtTotalCost->Text.IsEmpty()?AnsiString("0"):edtTotalCost->Text,DECIMAL_PLACE_COST).c_str();
        szSQL +=","; szSQL += Str2DBString(edtTranCompany->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtCarNo->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtDriver->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(cbbGoodsPerf->Text.c_str());

        szSQL +=")";

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return rt;
        }

        //query auto-icr-key
        //select @@identity
        szSQL = "select @@identity as autokey";
        RunSQL(dm1->Query1,szSQL,true);        
        if(dm1->Query1->Eof)
        {
                ShowMessage("insert fail(akey)!") ;
                return rt;
        }

        int autokey = dm1->Query1->FieldByName("autokey")->AsInteger;
        int column_no = lstViewDown->Items->Count;
        int cnt_con = lstViewContainer->Items->Count;
        TListItem *pItem =lstViewDown->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=(column_no+1);
        pItem->SubItems->Add(AnsiString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM)));
        pItem->SubItems->Add(cbbClient->Text);
        pItem->SubItems->Add(edtLading->Text);
        pItem->SubItems->Add(lstViewContainer->Items->Item[0]->Caption);
        pItem->SubItems->Add(lstViewContainer->Items->Item[0]->SubItems->Strings[1].c_str());
        pItem->SubItems->Add(lstViewContainer->Items->Item[0]->SubItems->Strings[0].c_str());
        pItem->SubItems->Add(IntToStr(cnt_con));
        pItem->SubItems->Add(edtTranCompany->Text);
        pItem->SubItems->Add(edtDriver->Text);
        pItem->SubItems->Add(edtCarNo->Text);
        pItem->SubItems->Add(cbbGoodsPerf->Text);

        pItem->SubItems->Add(edtFare->Text);
        pItem->SubItems->Add(edtFareOut->Text);
        pItem->SubItems->Add(edtTotalCharge->Text);
        pItem->SubItems->Add(edtTotalCost->Text);
        double lirun = edt2money(edtFare, DECIMAL_PLACE_CHARGE) - \
                       edt2money(edtFareOut, DECIMAL_PLACE_CHARGE) + \
                       edt2money(edtTotalCharge, DECIMAL_PLACE_CHARGE) - \
                       edt2money(edtTotalCost, DECIMAL_PLACE_CHARGE);
        pItem->SubItems->Add(lirun);
        pItem->SubItems->Add(AnsiString(GetContainerInfo(lstViewContainer)));
        pItem->SubItems->Add(edtLoadAddress->Text);
        pItem->SubItems->Add(edtLoadLinkMan->Text);
        pItem->SubItems->Add(edtLoadTel->Text);
        pItem->SubItems->Add(edtBeiZhu->Text);
        pItem->SubItems->Add(AnsiString(GetTailerChargeInfo()));

        pItem->SubItems->Add(autokey);
        rt = 0;
        return rt;
}
CString TTailerForm::GetContainerInfo_local(TListView *lv){
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
void  TTailerForm::modData(TObject *Sender){
/*        if (lstViewContainer->Items->Count == 0){
                ShowMessage("柜号信息不全");
                return;
        }
*/

        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要修改“%s”的记录吗？  \n",cbbClient->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
                
        if(cbbClient->Text.IsEmpty() || edtLading->Text.IsEmpty() || edtLoadAddress->Text.IsEmpty() || \
              edtLoadLinkMan->Text.IsEmpty() || edtLoadTel->Text.IsEmpty() || edtTranCompany->Text.IsEmpty() || \
              edtFare->Text.IsEmpty() || edtFareOut->Text.IsEmpty() || edtCarNo->Text.IsEmpty() || edtDriver->Text.IsEmpty() || \
              lstViewContainer->Items->Count == 0)
        {
                ShowMessage("请检查你的输入信息");
                return ;
        }

        if (!chk_charge_valid()){
                ShowMessage("请检查费用输入部分(空输入或费用有重复)");
                return ;
        }


        CString szSQL;
        szSQL="update tailer set ";     
        szSQL +="client="; szSQL += Str2DBString(cbbClient->Text.c_str());
        szSQL +=",opdate="; szSQL += Str2DBString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM));
        szSQL +=",ladingid="; szSQL += Str2DBString(edtLading->Text.c_str());
        szSQL +=",loadaddress="; szSQL += Str2DBString(edtLoadAddress->Text.c_str());
        szSQL +=",goodsperf="; szSQL += Str2DBString(cbbGoodsPerf->Text.c_str());
        szSQL +=",loadtel="; szSQL += Str2DBString(edtLoadTel->Text.c_str());
        szSQL +=",containerinfo="; szSQL += Str2DBString(GetContainerInfo_local(lstViewContainer));
        szSQL +=",fare="; szSQL += Text2DBFloat(edtFare->Text.IsEmpty()?AnsiString("0"):edtFare->Text,4).c_str();
        szSQL +=",fareout="; szSQL += Text2DBFloat(edtFareOut->Text.IsEmpty()?AnsiString("0"):edtFareOut->Text,4).c_str();
        szSQL +=",charge_cost="; szSQL += Str2DBString(GetTailerChargeInfo());

        szSQL +=",total_charge="; szSQL += Text2DBFloat(edtTotalCharge->Text.IsEmpty()?AnsiString("0"):edtTotalCharge->Text,DECIMAL_PLACE_CHARGE).c_str();
        szSQL +=",total_cost="; szSQL += Text2DBFloat(edtTotalCost->Text.IsEmpty()?AnsiString("0"):edtTotalCost->Text,DECIMAL_PLACE_COST).c_str();
        szSQL +=",trancompany="; szSQL += Str2DBString(edtTranCompany->Text.c_str());
        szSQL +=",carno="; szSQL += Str2DBString(edtCarNo->Text.c_str());
        szSQL +=",driver="; szSQL += Str2DBString(edtDriver->Text.c_str());
        szSQL +=",beizhu="; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL += " where tid="; szSQL+=Int2DBString(m_selected_id);

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;
                return;
        }

        ShowMessage("修改成功");
}

void  TTailerForm::refreshMod(){
/*        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d%02d%02d",year1,month1,day1);
*/
        TListItem *pItem  = lstViewDown->Selected;
        CString szSQL;
        szSQL="select *,substring(containerinfo,0,charindex('|',containerinfo)) as cnt_con \
                from tailer where 1=1 ";

        int tid = StrToInt(pItem->SubItems->Strings[COL_ID].c_str());
        szSQL +=" and tid="; szSQL += Int2DBString(tid);

	RunSQL(dm1->Query1,szSQL,true);
        
	if(!dm1->Query1->Eof)
	{
//        AnsiString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM))
//                pItem->Caption=dm1->Query1->FieldByName("cid")->AsString;
                pItem->SubItems->Strings[COL_OPDATE] = dm1->Query1->FieldByName("opdate")->AsString;
	        pItem->SubItems->Strings[COL_CLIENT] = dm1->Query1->FieldByName("client")->AsString;         

		pItem->SubItems->Strings[COL_LADING] = dm1->Query1->FieldByName("ladingid")->AsString;
                int cnt = 0;
                AnsiString containerno = "";
                AnsiString type = "";
                AnsiString sealid = "";
                getFirstContainerUnit(dm1->Query1->FieldByName("containerinfo")->AsString, cnt, containerno, type, sealid);

		pItem->SubItems->Strings[COL_CONTAINER_NO] = containerno;
		pItem->SubItems->Strings[COL_SEALID] = sealid;

		pItem->SubItems->Strings[COL_CONTAINER_TYPE] = type;
		pItem->SubItems->Strings[COL_CONTAINER_CNT] = IntToStr(cnt);
		pItem->SubItems->Strings[COL_TRANCOMPANY] = dm1->Query1->FieldByName("trancompany")->AsString;
		pItem->SubItems->Strings[COL_DRIVER] = dm1->Query1->FieldByName("driver")->AsString;
		pItem->SubItems->Strings[COL_CARNO] = dm1->Query1->FieldByName("carno")->AsString;
		pItem->SubItems->Strings[COL_GOODSPERF] = dm1->Query1->FieldByName("goodsperf")->AsString;
		pItem->SubItems->Strings[COL_FARE] = dm1->Query1->FieldByName("fare")->AsFloat;
		pItem->SubItems->Strings[COL_FAREOUT] = dm1->Query1->FieldByName("fareout")->AsFloat;

		pItem->SubItems->Strings[COL_TOTAL_CHARGE] = dm1->Query1->FieldByName("total_charge")->AsFloat;
		pItem->SubItems->Strings[COL_TOTAL_COST] = dm1->Query1->FieldByName("total_cost")->AsFloat;
                double lirun = dm1->Query1->FieldByName("fare")->AsFloat - \
                               dm1->Query1->FieldByName("fareout")->AsFloat + \
                               dm1->Query1->FieldByName("total_charge")->AsFloat - \
                               dm1->Query1->FieldByName("total_cost")->AsFloat ;
		pItem->SubItems->Strings[COL_LIRUN] = FloatToStr(lirun);
		pItem->SubItems->Strings[COL_CONTAINERINFO] = dm1->Query1->FieldByName("containerinfo")->AsString;
		pItem->SubItems->Strings[COL_LOADADDRESS] = dm1->Query1->FieldByName("loadaddress")->AsString;
              
		pItem->SubItems->Strings[COL_LOADLINKMAN] = dm1->Query1->FieldByName("loadlinkman")->AsString;
                pItem->SubItems->Strings[COL_LOADTEL] = dm1->Query1->FieldByName("loadtel")->AsString;
                pItem->SubItems->Strings[COL_BEIZHU] = dm1->Query1->FieldByName("beizhu")->AsString;
                pItem->SubItems->Strings[COL_CHARGE_COST] = dm1->Query1->FieldByName("charge_cost")->AsString;
//                pItem->SubItems->Strings[COL_ID] = dm1->Query1->FieldByName("containerinfo")->AsString; //not need
	}

}
void __fastcall TTailerForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
 lstViewDown->Selected=NULL;
//  Row2Editor();

  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW:
        if (btnAdd->CanFocus())
                btnAdd->SetFocus();
        break;
    case EN_EDIT:
        if (btnMod->CanFocus())
                btnMod->SetFocus();
        break;
    default:  break;
  }
//      btnMod->Enabled=false;
//    btnDel->Enabled=false;
}
//---------------------------------------------------------------------------

double  TTailerForm::sum_charge(){
        double total = 0;

        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                CVarCharge *d = it->second;
                total += edt2money(d->edtCharge, DECIMAL_PLACE_CHARGE);
	}
        return total;
}
double  TTailerForm::sum_cost(){
        double total = 0;

        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                CVarCharge *d = it->second;
                total += edt2money(d->edtCost, DECIMAL_PLACE_COST);
	}
        return total;
}
void  TTailerForm::cb_change_charge(int pos){
        std::map<int, CVarCharge*>::iterator it = m_mVarCharge.find(pos);
        if (it!=m_mVarCharge.end()){
                CVarCharge *d = it->second;
                if (!isMoney(d->edtCharge->Text, DECIMAL_PLACE_CHARGE)){
                        ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_CHARGE)+"位金额值");
                        return;
                }
                edtTotalCharge->Text = FloatToStr(sum_charge());
        }
}
void __fastcall TTailerForm::edtCharge1Change(TObject *Sender)
{
        cb_change_charge(1);
}
//---------------------------------------------------------------------------


void __fastcall TTailerForm::edtCharge2Change(TObject *Sender)
{
        cb_change_charge(2);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCharge3Change(TObject *Sender)
{
        cb_change_charge(3);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCharge4Change(TObject *Sender)
{
        cb_change_charge(4);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCharge5Change(TObject *Sender)
{
        cb_change_charge(5);
}
//---------------------------------------------------------------------------
void  TTailerForm::cb_change_cost(int pos){
        std::map<int, CVarCharge*>::iterator it = m_mVarCharge.find(pos);
        if (it!=m_mVarCharge.end()){
                CVarCharge *d = it->second;
                if (!isMoney(d->edtCost->Text, DECIMAL_PLACE_COST)){
                        ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_COST)+"位金额值");
                        return;
                }
                edtTotalCost->Text = FloatToStr(sum_cost());
        }
}

void __fastcall TTailerForm::edtCost1Change(TObject *Sender)
{
        cb_change_cost(1);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCost2Change(TObject *Sender)
{
        cb_change_cost(2);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCost3Change(TObject *Sender)
{
       cb_change_cost(3);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCost4Change(TObject *Sender)
{
        cb_change_cost(4);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtCost5Change(TObject *Sender)
{
        cb_change_cost(5);
}
//---------------------------------------------------------------------------
void TTailerForm::cb_change_name(int pos){
        std::map<int, CVarCharge*>::iterator it = m_mVarCharge.find(pos);
        if (it!=m_mVarCharge.end()){
                CVarCharge *d = it->second;
                bool b_charge_empty = (d->cbbName->ItemIndex ==0);
                d->edtCharge->ReadOnly = b_charge_empty;
                d->edtCost->ReadOnly = b_charge_empty;
                if (b_charge_empty){
                        d->edtCharge->Text = "";
                        d->edtCost->Text = "";
                }
        }
}

void __fastcall TTailerForm::cbbVarChargeName1Change(TObject *Sender)
{
        cb_change_name(1);

}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbVarChargeName2Change(TObject *Sender)
{
        cb_change_name(2);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbVarChargeName3Change(TObject *Sender)
{
        cb_change_name(3);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbVarChargeName4Change(TObject *Sender)
{
        cb_change_name(4);
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::cbbVarChargeName5Change(TObject *Sender)
{
        cb_change_name(5);
}
//---------------------------------------------------------------------------

//组装拖车费用:“费用个数|费用名称 费用 成本#费用名称 费用 成本#@”
CString TTailerForm::GetTailerChargeInfo(){
        int n_valid_charge = 0;
        CString _szContInfo;        
        CString szContInfo;

        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                CVarCharge *d = it->second;

                if (d->cbbName->ItemIndex != 0) {
                        n_valid_charge++;
                        szContInfo += d->cbbName->Text.c_str();
                        szContInfo += ' ';
                        szContInfo += d->edtCharge->Text.c_str();
                        szContInfo += ' ';
                        szContInfo += d->edtCost->Text.c_str();
                        szContInfo += '#';
                }
        }
        szContInfo += '@';
        _szContInfo += (IntToStr(n_valid_charge).c_str());
        _szContInfo += '|';
        _szContInfo += szContInfo;
        return _szContInfo;
}


bool TTailerForm::chk_charge_valid(){
        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end(); it++ ){
                CVarCharge *d = it->second;
                //empty check
                if (d->cbbName->ItemIndex != 0){
                        //dup check
                        for (std::map<int, CVarCharge*>::iterator it2 = m_mVarCharge.begin(); it2 != m_mVarCharge.end(); it2++ ){
                                //skip mysell
                                if (it->second == it2->second){
                                        continue;
                                }
                                if (it2->second->cbbName->ItemIndex == d->cbbName->ItemIndex){
                                        ShowMessage(AnsiString(IntToStr(it2->second->cbbName->ItemIndex)));
                                        ShowMessage(AnsiString(IntToStr(it->second->cbbName->ItemIndex)));
                                        return false;
                                }
                        }
                        //empty check
                        if (d->edtCharge->Text.IsEmpty() && d->edtCost->Text.IsEmpty()){
                                return false;
                        }
                        if (!isMoney(d->edtCharge->Text, DECIMAL_PLACE_CHARGE) && !isMoney(d->edtCost->Text, DECIMAL_PLACE_COST) ){
                                return false;
                        }

                }

        }

        return true;
}
void __fastcall TTailerForm::edtFareChange(TObject *Sender)
{
        if (!isMoney(edtFare->Text, DECIMAL_PLACE_CHARGE)){
                ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_CHARGE)+"位金额值");
                return;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::edtFareOutChange(TObject *Sender)
{
        if (!isMoney(edtFareOut->Text, DECIMAL_PLACE_CHARGE)){
                ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_CHARGE)+"位金额值");
                return;
        }
}
//---------------------------------------------------------------------------
void TTailerForm::flushContainer(AnsiString c){
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


        if (lstViewContainer->Items->Count>0){
                edtContainerNo->Text = lstViewContainer->Items->Item[0]->Caption;
                cbbContainerType->ItemIndex=cbbContainerType->Items->IndexOf(lstViewContainer->Items->Item[0]->SubItems->Strings[0]);
                edtSealId->Text = lstViewContainer->Items->Item[0]->SubItems->Strings[1];
        }

}
void TTailerForm::_flushVarCharge(AnsiString name, AnsiString charge, AnsiString cost){
        if (name == "" || charge == "" || cost == ""){
                return;
        }
        for (std::map<int, CVarCharge*>::iterator it = m_mVarCharge.begin(); it != m_mVarCharge.end();  it++){
                CVarCharge *d = it->second;
                if (d->cbbName->ItemIndex == 0){
                        d->cbbName->ItemIndex=d->cbbName->Items->IndexOf(name);
                        d->edtCharge->Text = charge;
                        d->edtCost->Text = cost;
                        return;
                }
	}

}
void TTailerForm::flushVarCharge(AnsiString c){
		char cnt[10];memset(cnt,sizeof(cnt),0x00);
		char body[2048];memset(body,sizeof(body),0x00);
		sscanf(c.c_str(),"%[^|]|",cnt);
		sscanf(c.c_str(),"%*[^|]|%[^@]",body);

		char strTmp1[2048];
		memset(strTmp1,sizeof(strTmp1),0x00);
		strcpy(strTmp1,body);
                int num = StrToInt(cnt);
		for (int i =0; i<num; ++i){
			char str1[100],str2[100],str3[100],str4[100],strTmp[2048],strCost[100];
			memset(str1,sizeof(str1),0x00);
			memset(str2,sizeof(str2),0x00);
			memset(str3,sizeof(str3),0x00);
			memset(str4,sizeof(str4),0x00);
			memset(strCost,sizeof(strCost),0x00);

			memset(strTmp,sizeof(strTmp),0x00);
			strcpy(strTmp,strTmp1);
			sscanf(strTmp,"%[^#]#",str1);
			sscanf(str1,"%s %s %s",str3,str4,strCost);
			sscanf(strTmp,"%*[^#]#%[^@]",strTmp1);

//                        TListItem *pItem =lstViewContainer->Items->Add();
//                        assert(pItem!=NULL);
                        _flushVarCharge(AnsiString(str3), AnsiString(str4), AnsiString(strCost));
		}
}
void __fastcall TTailerForm::lstViewDownSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
  if(Selected!=NULL){
        clean_input();
        TDateTime tDate;
        tDate=StrToDateTime(Item->SubItems->Strings[COL_OPDATE].c_str());
        dtpOpDateYYYYMMDD->DateTime=tDate;
        dtpOpDateHHMM->Time=tDate;

        cbbClient->Text = Item->SubItems->Strings[COL_CLIENT].c_str();
        edtLading->Text = Item->SubItems->Strings[COL_LADING].c_str();
        edtLoadAddress->Text = Item->SubItems->Strings[COL_LOADADDRESS].c_str();
        edtLoadLinkMan->Text = Item->SubItems->Strings[COL_LOADLINKMAN].c_str();
        edtLoadTel->Text = Item->SubItems->Strings[COL_LOADTEL].c_str();
        edtTranCompany->Text = Item->SubItems->Strings[COL_TRANCOMPANY].c_str();
        edtFare->Text = Item->SubItems->Strings[COL_FARE].c_str();
        edtFareOut->Text = Item->SubItems->Strings[COL_FAREOUT].c_str();
        edtCarNo->Text = Item->SubItems->Strings[COL_CARNO].c_str();
        edtDriver->Text = Item->SubItems->Strings[COL_DRIVER].c_str();
        
        edtBeiZhu->Text = Item->SubItems->Strings[COL_BEIZHU].c_str();

        cbbGoodsPerf->ItemIndex=cbbGoodsPerf->Items->IndexOf(Item->SubItems->Strings[COL_GOODSPERF]);
        flushContainer(AnsiString(Item->SubItems->Strings[COL_CONTAINERINFO].c_str()));
        flushVarCharge(AnsiString(Item->SubItems->Strings[COL_CHARGE_COST].c_str()));
        m_selected_id = StrToInt(Item->SubItems->Strings[COL_ID].c_str());
  }
        ResetCtrl();
}
//---------------------------------------------------------------------------


void __fastcall TTailerForm::btnDelClick(TObject *Sender)
{
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要删除“%s”的记录吗？  \n",cbbClient->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        CString szSQL;
        szSQL.Format("delete tailer where tid=%d", m_selected_id);
        if(!RunSQL(dm1->Query1,szSQL))
                ShowMessage("delete fail!");
        //btnQueryClick(Sender);
        delLvItem(lstViewDown);
        m_selected_id = 0;
        ShowMessage("删除成功");
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnPrnOutCarClick(TObject *Sender)
{
        TPrnCYDForm *pForm;
 	pForm=new TPrnCYDForm(this);
        assert(pForm!=NULL);

        pForm->qrlOpDate->Caption = AnsiString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM));
        pForm->qrlCarNo->Caption  = edtCarNo->Text;
        pForm->qrlLoadAddress->Caption = edtLoadAddress->Text;
        pForm->qrlLading->Caption = edtLading->Text;
        pForm->qrlBeiZhu->Caption = edtBeiZhu->Text;
        pForm->qrl_date->Caption = AnsiString(GetSysDate());
        pForm->qrlContainerType->Caption = lstViewContainer->Items->Item[0]->SubItems->Strings[0].c_str();


        
        //copy data
        pForm->qrlOpDate2->Caption = pForm->qrlOpDate->Caption;
        pForm->qrlCarNo2->Caption  = pForm->qrlCarNo->Caption;
        pForm->qrlLoadAddress2->Caption = pForm->qrlLoadAddress->Caption;
        pForm->qrlLading2->Caption = pForm->qrlLading->Caption;
        pForm->qrlBeiZhu2->Caption = pForm->qrlBeiZhu->Caption;
        pForm->qrl_date2->Caption = pForm->qrl_date->Caption;
        pForm->qrlContainerType2->Caption = pForm->qrlContainerType->Caption;         
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();        
}
//---------------------------------------------------------------------------


void TTailerForm::getFirstContainerUnit(AnsiString c, int &_cnt, AnsiString &containerno, AnsiString &type, AnsiString &sealid)
{

        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        _cnt = num;
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
                containerno = AnsiString(str3);
                type = AnsiString(str4);
                sealid = AnsiString(strSealId);
        }
}
