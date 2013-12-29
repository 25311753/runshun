//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Tailer.h"
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
#define DECIMAL_PLACE_CHARGE 2
//---------------------------------------------------------------------------
void Tailer(int nAuth)
{
        CALL_FORM(TTailerForm);
}
__fastcall TTailerForm::TTailerForm(TComponent* Owner)
        : TForm(Owner)
{
        m_enWorkState=EN_IDLE;
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
        cbbVarChargeName1->Text = "";
        edtCharge1->Text = "";
        edtCost1->Text = "";

        cbbVarChargeName2->Text = "";
        edtCharge2->Text = "";
        edtCost2->Text = "";

        cbbVarChargeName3->Text = "";
        edtCharge3->Text = "";
        edtCost3->Text = "";

        cbbVarChargeName4->Text = "";
        edtCharge4->Text = "";
        edtCost4->Text = "";

        cbbVarChargeName5->Text = "";
        edtCharge5->Text = "";
        edtCost5->Text = "";
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
        CString szSQL;
        szSQL.Format("select * from charges order by chid");
        RunSQL(dm1->Query1,szSQL,true);

        while(!dm1->Query1->Eof)
        {
                int chid = dm1->Query1->FieldByName("chid")->AsInteger;        
                AnsiString chname = dm1->Query1->FieldByName("chname")->AsString;
                cbbVarChargeName1->Items->Add(chname);
                cbbVarChargeName2->Items->Add(chname);
                cbbVarChargeName3->Items->Add(chname);
                cbbVarChargeName4->Items->Add(chname);
                cbbVarChargeName5->Items->Add(chname);
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
	ResetCtrl();
        if(cbbClient->CanFocus())
                cbbClient->SetFocus();
        m_enWorkState=EN_ADDNEW;
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTailerForm::btnQueryClick(TObject *Sender)
{
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
      if (-1 == add(Sender))
        return;
      break;
    case EN_EDIT:
       mod(Sender);
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
int TTailerForm::add(TObject *Sender){
        int rt = -1;

        if(cbbClient->Text.IsEmpty() || edtLading->Text.IsEmpty() || edtLoadAddress->Text.IsEmpty() || \
              edtLoadLinkMan->Text.IsEmpty() || edtLoadTel->Text.IsEmpty() || edtTranCompany->Text.IsEmpty() || \
              edtFare->Text.IsEmpty() || edtFareOut->Text.IsEmpty() || edtCarNo->Text.IsEmpty() || edtDriver->Text.IsEmpty() || \
              lstViewContainer->Items->Count == 0)
        {
                ShowMessage("请检查你的输入信息");
                return rt;
        }

        //gen date        
        CString szSQL;
        szSQL="insert into tailer(client, opdate, ladingid, loadaddress, loadlinkman, loadtel, \
                                containerinfo, fare, fareout, charge_cost, total_charge,\
                                total_cost, trancompany, carno, dirver, beizhu) \
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
        szSQL +=","; szSQL += "chargevar....";
        szSQL +=","; szSQL += "total charge....";
        szSQL +=","; szSQL += "total cost....";
        szSQL +=","; szSQL += Str2DBString(edtTranCompany->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtCarNo->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtDriver->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=")";

//        lbdebug->Caption = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return rt;
        }

        int column_no = lstViewDown->Items->Count;
        int cnt_con = lstViewContainer->Items->Count;
        TListItem *pItem =lstViewDown->Items->Add();
        assert(pItem!=NULL);

        pItem->Caption=(column_no+1);
        pItem->SubItems->Add(AnsiString(GetTimeBy2Dtp(dtpOpDateYYYYMMDD, dtpOpDateHHMM)));
        pItem->SubItems->Add(cbbClient->Text);
        pItem->SubItems->Add(edtLading->Text);
        pItem->SubItems->Add(lstViewContainer->Items->Item[0]->Caption);
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");        
        pItem->SubItems->Add(IntToStr(cnt_con));
        pItem->SubItems->Add(edtTranCompany->Text);
        pItem->SubItems->Add(edtDriver->Text);
        pItem->SubItems->Add(edtCarNo->Text);
        pItem->SubItems->Add(cbbGoodsPerf->Text);
        pItem->SubItems->Add(edtFare->Text);
        pItem->SubItems->Add(edtFareOut->Text);
        pItem->SubItems->Add(edtTotalCharge->Text);
        pItem->SubItems->Add(edtTotalCost->Text);
        double lirun = StrToFloat(edtFare->Text.c_str())-StrToFloat(edtFareOut->Text.c_str())+ \
                        StrToFloat(edtTotalCharge->Text.c_str())-StrToFloat(edtTotalCost->Text.c_str());
        pItem->SubItems->Add(lirun);

        rt = 0;
        return rt;
}
void  TTailerForm::mod(TObject *Sender){

}

void  TTailerForm::refreshMod(){

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


void __fastcall TTailerForm::edtCharge1Change(TObject *Sender)
{
        if (!isMoney(edtCharge1->Text, DECIMAL_PLACE_CHARGE)){
                ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_CHARGE)+"位金额值");
                return;
        }
        double total_charge = edt2money(edtCharge1, DECIMAL_PLACE_CHARGE) + \
                                edt2money(edtCharge2, DECIMAL_PLACE_CHARGE) +\
                                edt2money(edtCharge3, DECIMAL_PLACE_CHARGE) + \
                                edt2money(edtCharge4, DECIMAL_PLACE_CHARGE)+\
                                edt2money(edtCharge5, DECIMAL_PLACE_CHARGE);
        edtTotalCharge->Text = FloatToStr(total_charge);
}
//---------------------------------------------------------------------------


