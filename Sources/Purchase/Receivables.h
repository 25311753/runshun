//---------------------------------------------------------------------------

#ifndef ReceivablesH
#define ReceivablesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TReceivablesForm : public TForm
{
__published:	// IDE-managed Components
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TButton *Button1;
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnNew;
        TButton *btnOK;
        TPanel *pl;
        TPanel *pl_input;
        TPanel *pl_query;
        TListView *lstViewDown;
        TPanel *Panel2;
        TComboBox *cbbClient;
        TPanel *Panel20;
        TDateTimePicker *dtpShouldRecvDate;
        TPanel *Panel9;
        TEdit *edtCharge;
        TPanel *Panel5;
        TComboBox *cbbStatus;
        TPanel *Panel13;
        TDateTimePicker *dtpRecvDate;
        TPanel *Panel14;
        TEdit *edtBeiZhu;
        TPanel *Panel1;
        TComboBox *cbbQryClient;
        TDateTimePicker *dtpQryRecvDateEnd;
        TPanel *Panel4;
        TDateTimePicker *dtpQryRecvDate;
        TPanel *Panel3;
        TComboBox *cbbQryStatus;
        TButton *btnQry;
private:	// User declarations
public:		// User declarations
        __fastcall TReceivablesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReceivablesForm *ReceivablesForm;
//---------------------------------------------------------------------------
#endif
