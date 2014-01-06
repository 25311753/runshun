//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <map>
#include <vector>
#include "Receivables.h"  
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

#define DECIMAL_PLACE_CHARGE 2
#define EXTEND_YYYYMM_HEAD 3
#define EXTEND_YYYYMM_TAIL 3

enum E_RECVCHARGE_COL_NAME{
	COL_CLIENT = 0,
};

TReceivablesForm *ReceivablesForm;
void Receivables(int nAuth)
{
        CALL_FORM(TReceivablesForm);
}
//---------------------------------------------------------------------------
__fastcall TReceivablesForm::TReceivablesForm(TComponent* Owner)
        : TForm(Owner)
{
        m_enWorkState=EN_IDLE;
//        m_highlight = false;
        m_hl_col = -1;
}
//---------------------------------------------------------------------------
void TReceivablesForm::clean_input(){
        cbbClient->Text = "";
        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpShouldRecvDate->DateTime=tNow;
        dtpRecvDate->DateTime=tNow;
        dtpRecvDate->Visible=false;
        edtCharge->Text = "";
        cbbStatus->ItemIndex=0;
        cbRecvFlag->Checked = false;
        edtBeiZhu->Text = "";

}
void TReceivablesForm::clean_query(){
        cbbQryClient->ItemIndex = -1;
        cbbQryClient->Text = "";

        cbbQryStatus->ItemIndex = -1;
        cbbQryStatus->Text = "";

        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpQryShouldRecvDate->DateTime=tNow;
        dtpQryShouldRecvDateEnd->DateTime=tNow;
        cbIsQryByDate->Checked = false;
}

void __fastcall TReceivablesForm::btnCleanQryClick(TObject *Sender)
{
        clean_query();        
}
//---------------------------------------------------------------------------
void TReceivablesForm::clean_listview(){
        lstViewDown->Clear();
        lstViewDown->Columns->Clear();
}
void __fastcall TReceivablesForm::FormShow(TObject *Sender)
{
        clean_input();
        clean_query();
        clean_listview();
        m_enWorkState=EN_IDLE;
        ResetCtrl();       
}
//---------------------------------------------------------------------------


void __fastcall TReceivablesForm::cbbQryClientSelect(TObject *Sender)
{
        int nSel = cbbQryClient->ItemIndex;
        if (nSel == -1)
                return;         
}
//---------------------------------------------------------------------------

void __fastcall TReceivablesForm::cbbQryClientChange(TObject *Sender)
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
void TReceivablesForm::draw_column(TListView *lv, int start_date, int end_date){
        int col_order = 0;//!start with 0!
        lv->Clear();
        lv->Columns->Clear();
        lv->Columns->Add();
        lv->Columns->Add();
        lv->Columns->Items[col_order++]->Caption="N";
        lv->Columns->Items[col_order++]->Caption="客户";
        //draw lstview column
        for (int i=start_date; i<=end_date;){

                lv->Columns->Add();
                lv->Columns->Items[col_order++]->Caption=AnsiString(IntToStr(i));
                if ( 0 == ((i%100)%12)){
                        i += 100;
                        i -= 11;
                }else{                    
                        ++i;
                }
        }  
        lv->Columns->Add();
        lv->Columns->Items[col_order++]->Caption="合计";

}
int TReceivablesForm::get_col_pos(int recv_date){
        int rt_pos = 0;
        for (rt_pos; rt_pos<lstViewDown->Columns->Count; ++rt_pos){
                if (lstViewDown->Columns->Items[rt_pos]->Caption == AnsiString(IntToStr(recv_date))){
                        break;
                }
        }

        //should not come here!!
        return rt_pos-1;
}

int TReceivablesForm::add_empty_row(){
        int column_no = lstViewDown->Items->Count;
        TListItem *pItem =lstViewDown->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=AnsiString(column_no+1);

        for (int i=0; i<lstViewDown->Columns->Count; ++i){
                pItem->SubItems->Add("");
        }
        return  lstViewDown->Items->Count -1;

}

void __fastcall TReceivablesForm::btnQryClick(TObject *Sender)
{
        if (m_enWorkState==EN_EDIT){
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n 编辑状态，确定重新查询？\n");
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                        return;
        }
        //
        CString szSQL;
        szSQL="select * from recvcharge where 1=1 ";
        if (!cbbQryClient->Text.IsEmpty()) {
                szSQL += " and client="; szSQL += Str2DBString(cbbQryClient->Text.c_str());
        }
        if (!cbbQryStatus->Text.IsEmpty()){
                szSQL += " and status="; szSQL += Str2DBString(cbbQryStatus->Text.c_str());
        }

        int start_recv_date = GetYYYYMM(dtpQryShouldRecvDate);
        int end_recv_date   = GetYYYYMM(dtpQryShouldRecvDateEnd);
        if (cbIsQryByDate->Checked) {
                szSQL += " and recvdate between "; szSQL += Int2DBString(start_recv_date);
                szSQL += " and ";
                szSQL += Int2DBString(end_recv_date);
        }
        szSQL += " order by recvdate";
//        Edit1->Text = AnsiString(szSQL);
        TListItem *pItem;
        lstViewDown->Items->Clear();
        clean_input();
	RunSQL(dm1->Query1,szSQL,true);

        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                clean_listview();
                return;
        }
        //buf data first
        std::map<AnsiString, std::map<int, double> > map_recv;   
        map_recv.clear();
	while(!dm1->Query1->Eof)
	{
                AnsiString client = dm1->Query1->FieldByName("client")->AsString;
                int recv_date = dm1->Query1->FieldByName("recvdate")->AsInteger;
                double charge = dm1->Query1->FieldByName("charge")->AsFloat;

                std::map<AnsiString, std::map<int, double> >::iterator it = map_recv.find(client);
                map_recv[client].insert(std::make_pair(recv_date, charge));

		dm1->Query1->Next();
	}


        if (!cbIsQryByDate->Checked){
                int min_recv_date = 0;
                int max_recv_date = 0;
                //if qry all, mod date scope
                for (std::map<AnsiString, std::map<int, double> >::iterator it = map_recv.begin(); \
                                                                it != map_recv.end(); \
                                                                ++it)

                {
                        for (std::map<int, double>::iterator it_date_charge = it->second.begin(); it_date_charge!=it->second.end(); ++it_date_charge){
                                int recv_date = it_date_charge->first;
                                //init
                                if (min_recv_date==0){
                                    min_recv_date =  recv_date;
                                }
                                if (max_recv_date==0){
                                    max_recv_date =  recv_date;
                                }
                                if (recv_date < min_recv_date){
                                        min_recv_date = recv_date;
                                }
                                if (recv_date > max_recv_date){
                                        max_recv_date = recv_date;
                                }
                        }
                }
                start_recv_date = min_recv_date;
                end_recv_date = max_recv_date;
        }
        
        draw_column(lstViewDown, start_recv_date, end_recv_date);

        //fill data

        for (std::map<AnsiString, std::map<int, double> >::iterator it = map_recv.begin(); \
                                                                it != map_recv.end(); \
                                                                ++it)
        {
                int row = add_empty_row();
                TListItem *pItem = lstViewDown->Items->Item[row];
                AnsiString client = it->first;
                double total_row = 0;
                for (std::map<int, double>::iterator it2 = it->second.begin(); \
                                                                it2 != it->second.end(); \
                                                                ++it2)
                {
                        pItem->SubItems->Strings[0] = client;
                        pItem->SubItems->Strings[get_col_pos(it2->first)] = it2->second;
                        total_row += it2->second;
                }
//                 pItem->SubItems->Strings[lstViewDown->Columns->Count -2] = AnsiString(total_row);
                flush_total_row(row);
        }
        //add total_col
        int row_total = add_empty_row();
        TListItem *pItem_row_total = lstViewDown->Items->Item[row_total];
        pItem_row_total->Caption = "合计";

        for (int pos_col=COL_CLIENT+1; pos_col<lstViewDown->Columns->Count-1; ++pos_col){
                double sum_col = 0;
                for(int i=2;i<lstViewDown->Items->Count;i++)
                {
                        AnsiString str_charge = lstViewDown->Items->Item[i]->SubItems->Strings[pos_col];
                        sum_col += str_charge.IsEmpty()?0:StrToFloat(str_charge.c_str());
                }
                pItem_row_total->SubItems->Strings[pos_col] = sum_col;

        }

}
//---------------------------------------------------------------------------
void TReceivablesForm::flush_total_row(int row){
        TListItem *pItem = lstViewDown->Items->Item[row];
        double total_row = 0;
        for (int pos=COL_CLIENT+1; pos<lstViewDown->Columns->Count-2; ++pos){
                AnsiString str_charge = pItem->SubItems->Strings[pos];
                if (!str_charge.IsEmpty()){
                        total_row += StrToFloat(str_charge.c_str());
                }

        }
        pItem->SubItems->Strings[lstViewDown->Columns->Count-2] = total_row;
}

void TReceivablesForm::flush_total_col(int col){

}


void TReceivablesForm::ResetCtrl(){
 
  if(m_enWorkState==EN_IDLE)
  {
    btnNew->Enabled=true;
    btnNewGoOn->Enabled=false;
    btnAdd->Enabled=false;
    btnMod->Enabled=false;
    cbbClient->Enabled = true;
    dtpShouldRecvDate->Enabled = true;
  }
  else if (m_enWorkState==EN_EDIT)
  {                         
    btnNew->Enabled=false;
    btnNewGoOn->Enabled=false;
    btnAdd->Enabled=false;
    btnMod->Enabled=true;
    cbbClient->Enabled = false;
    dtpShouldRecvDate->Enabled = false;
  }else if (m_enWorkState==EN_ADD){
    btnNew->Enabled=false;
    btnNewGoOn->Enabled=false;
    btnAdd->Enabled=true;
    btnMod->Enabled=false;
    cbbClient->Enabled = false;
    dtpShouldRecvDate->Enabled = false;
  }else if (m_enWorkState==EN_NEW){
    btnNew->Enabled=false;
    btnNewGoOn->Enabled=true;
    btnAdd->Enabled=false;
    btnMod->Enabled=false;
    cbbClient->Enabled = false;
    dtpShouldRecvDate->Enabled = false;
  }

}


bool TReceivablesForm::cell2input(AnsiString client, int recv_date){
        bool ret = false;
        CString szSQL;
        szSQL.Format("select * from recvcharge where client='%s' and recvdate=%d", client.c_str(), recv_date);
        RunSQL(dm1->Query1,szSQL,true);
        if(!dm1->Query1->Eof)
        {
                cbbClient->Text = dm1->Query1->FieldByName("client")->AsString;
                //cat be set outside!!
                CString sdate;
		sdate.Format("%04d-%02d-01 00:00:01",recv_date/100, recv_date%100);

                setDtp(dtpShouldRecvDate, AnsiString(sdate));
                edtCharge->Text = dm1->Query1->FieldByName("charge")->AsFloat;
                cbbStatus->ItemIndex=cbbStatus->Items->IndexOf(dm1->Query1->FieldByName("status")->AsString);

                cbRecvFlag->Checked = dm1->Query1->FieldByName("recv_flag")->AsInteger == 1;
                edtBeiZhu->Text = dm1->Query1->FieldByName("beizhu")->AsString;
                setDtp(dtpRecvDate, dm1->Query1->FieldByName("recveddate")->AsString);
                dtpRecvDate->Visible = cbbStatus->Text == "已收款";
                ret = true;
        }
        return ret;
}

void __fastcall TReceivablesForm::lstViewDownMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        m_enWorkState=EN_IDLE;
        clean_input();
        if(Button == mbLeft)
        {
                if (lstViewDown->Selected){
                        AnsiString client = lstViewDown->Selected->SubItems->Strings[COL_CLIENT];
                        cbbClient->Text = client;
                        int column = 0;
                        int total = 0;
                        int delta_scroll = GetScrollPos(lstViewDown->Handle,SB_HORZ);
                        int real_x = X+ delta_scroll;
                        for (int i=0; i< lstViewDown->Columns->Count; ++i){
                                total = total +lstViewDown->Columns->Items[i]->Width;
                                if (real_x<total){
                                        column=i;
                                        if (1<column && column<lstViewDown->Columns->Count-1){

                                                int recv_date = StrToInt(lstViewDown->Columns->Items[column]->Caption);
//                                                ShowMessage(AnsiString(column)+"~"+AnsiString(recv_date)+"~x:"+AnsiString(X)+"~total:"+AnsiString(total));
                                                bool b_have_data = cell2input(client, recv_date);  //may change workstate
                                                m_enWorkState= b_have_data?EN_EDIT:EN_ADD;

                                                //if b_have_data=false, this work!!
                                                CString sdate;
		                                sdate.Format("%04d-%02d-01 00:00:01",recv_date/100, recv_date%100);
                                                setDtp(dtpShouldRecvDate, AnsiString(sdate));

                m_hl_col = get_col_pos(StrToInt(lstViewDown->Columns->Items[column]->Caption));

                //只是为了触发重画
                lstViewDown->Selected->SubItems->Strings[m_hl_col] = \
                lstViewDown->Selected->SubItems->Strings[m_hl_col];

                                        }
//                                        cbbClient->Text = client;
                                        break;
                                }
                        }
                }
        }
        ResetCtrl();
}
//---------------------------------------------------------------------------
void  TReceivablesForm::refreshLvByInput(){
        if (lstViewDown->Selected){
                lstViewDown->Selected->SubItems->Strings[get_col_pos(GetYYYYMM(dtpShouldRecvDate))] = edtCharge->Text;
                flush_total_row(lstViewDown->Selected->Index);
        }
}
void __fastcall TReceivablesForm::btnModClick(TObject *Sender)
{
        int recv_date = GetYYYYMM(dtpShouldRecvDate);
        AnsiString status = cbbStatus->Text;
        AnsiString client = cbbClient->Text;
                
        if (!chk_input()){
                return;
        }
        
        CString szSQL;
        szSQL="update recvcharge set ";
        szSQL +="charge="; szSQL += Text2DBFloat(edtCharge->Text.IsEmpty()?AnsiString("0"):edtCharge->Text,DECIMAL_PLACE_CHARGE).c_str();
        szSQL +=",status="; szSQL += Str2DBString(status.c_str());
        szSQL +=",recveddate="; szSQL += Str2DBString(GetTime(dtpRecvDate));
        szSQL +=",beizhu="; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=",recv_flag="; szSQL += Int2DBString(cbRecvFlag->Checked?1:0);
        szSQL += " where client="; szSQL+=Str2DBString(client.c_str());
        szSQL += " and recvdate="; szSQL+=Int2DBString(recv_date);

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;
                return;
        }
        //reset charge in ori-cell by recv_date(column):
        refreshLvByInput();

        ShowMessage("修改成功");
        m_enWorkState=EN_IDLE;
        ResetCtrl();

}
//---------------------------------------------------------------------------

void __fastcall TReceivablesForm::edtChargeChange(TObject *Sender)
{
        if (!isMoney(edtCharge->Text, DECIMAL_PLACE_CHARGE)){
                ShowMessage("输入非法, 请输入"+AnsiString(DECIMAL_PLACE_CHARGE)+"位金额值");
                edtCharge->Text = 0;
                return;
        }
}
//---------------------------------------------------------------------------


void __fastcall TReceivablesForm::cbbStatusChange(TObject *Sender)
{
        dtpRecvDate->Visible = cbbStatus->Text == "已收款";
}
//---------------------------------------------------------------------------
bool TReceivablesForm::chk_input(){
        if (cbRecvFlag->Checked && cbbStatus->Text == "未收款"){
                ShowMessage("状态为[未收款],不能勾选确认收款！");
                return false;
        }
        if(edtCharge->Text.IsEmpty())
        {
                ShowMessage("请输入应收款");
                return false;
        }
        return true;
}

void __fastcall TReceivablesForm::btnAddClick(TObject *Sender)
{
        int recv_date = GetYYYYMM(dtpShouldRecvDate);
        AnsiString status = cbbStatus->Text;
        AnsiString client = cbbClient->Text;
                
        if (!chk_input()){
                return;
        }

       CString szSQL;
       szSQL="insert into recvcharge(client, recvdate, status, charge, \
                                        recveddate, beizhu, recv_flag) \
                        values(";
        szSQL += Str2DBString(cbbClient->Text.c_str());
        szSQL +=","; szSQL += Int2DBString(GetYYYYMM(dtpShouldRecvDate));
        szSQL +=","; szSQL += Str2DBString(cbbStatus->Text.c_str());
        szSQL +=","; szSQL += Text2DBFloat(edtCharge->Text.IsEmpty()?AnsiString("0"):edtCharge->Text,DECIMAL_PLACE_CHARGE).c_str();
        szSQL +=","; szSQL += Str2DBString(GetTime(dtpRecvDate));
        szSQL +=","; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=","; szSQL += Int2DBString(cbRecvFlag->Checked?1:0);
        szSQL +=")";
//        Edit1->Text = AnsiString(szSQL);
//        .... 错位 导致 key 冲突
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return;
        }
        refreshLvByInput();
        ShowMessage("添加成功");
        m_enWorkState=EN_IDLE;
        ResetCtrl();
}
//---------------------------------------------------------------------------





















void __fastcall TReceivablesForm::lstViewDownCustomDrawSubItem(
      TCustomListView *Sender, TListItem *Item, int SubItem,
      TCustomDrawState State, bool &DefaultDraw)
{

        return;
     if(SubItem==4)//2列
     {
//        ShowMessage(AnsiString(SubItem)+"-"+AnsiString(m_hl_col));
        lstViewDown->Canvas->Brush->Color   =   clLime   ;
     }

}
//---------------------------------------------------------------------------







void __fastcall TReceivablesForm::lstViewDownAdvancedCustomDrawSubItem(
      TCustomListView *Sender, TListItem *Item, int SubItem,
      TCustomDrawState State, TCustomDrawStage Stage, bool &DefaultDraw)
{
return;
   if(Item->Index==1)//1行 
  {

     if(SubItem==4)//2列
     {
//        ShowMessage(AnsiString(SubItem)+"-"+AnsiString(m_hl_col));
        lstViewDown->Canvas->Brush->Color   =   clLime   ;
     }
     else
     {
      lstViewDown->Canvas->Brush->Color   =   clWhite;
     }
    }
    m_hl_col=-1;

}
//---------------------------------------------------------------------------







void __fastcall TReceivablesForm::lstViewDownAdvancedCustomDrawItem(
      TCustomListView *Sender, TListItem *Item, TCustomDrawState State,
      TCustomDrawStage Stage, bool &DefaultDraw)
{
return;
   if (m_hl_col==-1){
        return;
   }
      ShowMessage(AnsiString(m_hl_col)+"-"+AnsiString(lstViewDown->Selected?1:0));

        lstViewDown->Canvas->Brush->Color   =   clLime   ;



   m_hl_col=-1;
}
//---------------------------------------------------------------------------






void __fastcall TReceivablesForm::btnNewClick(TObject *Sender)
{
/*
        int recv_date = GetYYYYMM(dtpShouldRecvDate);
        AnsiString status = cbbStatus->Text;
        AnsiString client = cbbClient->Text;
                
        if (!chk_input()){
                return;
        }

       CString szSQL;
       szSQL="insert into recvcharge(client, recvdate, status, charge, \
                                        recveddate, beizhu, recv_flag) \
                        values(";
        szSQL += Str2DBString(cbbClient->Text.c_str());
        szSQL +=","; szSQL += Int2DBString(GetYYYYMM(dtpShouldRecvDate));
        szSQL +=","; szSQL += Str2DBString(cbbStatus->Text.c_str());
        szSQL +=","; szSQL += Text2DBFloat(edtCharge->Text.IsEmpty()?AnsiString("0"):edtCharge->Text,DECIMAL_PLACE_CHARGE).c_str();
        szSQL +=","; szSQL += Str2DBString(GetTime(dtpRecvDate));
        szSQL +=","; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=","; szSQL += Int2DBString(cbRecvFlag->Checked?1:0);
        szSQL +=")";
//        Edit1->Text = AnsiString(szSQL);
//        .... 错位 导致 key 冲突
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return;
        }
        refreshLvByInput();
        ShowMessage("新增成功");
*/
        m_enWorkState=EN_NEW;
        ResetCtrl();

//        btnNew->Enabled = false;
//        btnNewGoOn->Enabled = !btnNew->Enabled;

}
//---------------------------------------------------------------------------

void __fastcall TReceivablesForm::btnNewGoOnClick(TObject *Sender)
{
        m_enWorkState=EN_IDLE;
        ResetCtrl();
//        btnNewGoOn->Enabled = false;
//        btnNew->Enabled = !btnNewGoOn->Enabled;
}
//---------------------------------------------------------------------------

