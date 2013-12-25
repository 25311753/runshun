//---------------------------------------------------------------------------

#ifndef TailerH
#define TailerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TTailerForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelUp;
        TComboBox *cbbClient;
        TEdit *edtLading;
        TEdit *edtCliWorkid;
        TEdit *edtBeiZhu;
        TComboBox *cbbGoodsPerf;
        TDateTimePicker *dtpEndDateHHMM;
        TEdit *edtContainerNo;
        TComboBox *cbbContainerType;
        TButton *btnAddContainer;
        TListView *lstViewContainer;
        TButton *btnModContainer;
        TButton *btnDelContainer;
        TEdit *edtSealId;
        TDateTimePicker *dtpEndDateYYYYMMDD;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel10;
        TPanel *Panel11;
        TPanel *Panel13;
        TPanel *Panel14;
        TEdit *edtBoatNo;
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnDel;
        TPanel *PanelUpQuery;
        TEdit *edtQryLading;
        TEdit *edtQryJZS;
        TButton *btnQuery;
        TDateTimePicker *dtpQryAcceptDate;
        TDateTimePicker *dtpQryAcceptDateEnd;
        TComboBox *cbbQryClient;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel20;
        TPanel *Panel23;
        TComboBox *cbbGoodsPerfQry;
        TButton *btnClearQryCond;
        TButton *btnCancel;
        TButton *btnOK;
        TButton *Button1;
        TListView *lstViewDown;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TButton *btnPrnOutCar;
        TPanel *Panel1;
        TEdit *Edit1;
        TPanel *Panel8;
        TEdit *Edit2;
        TPanel *Panel9;
        TEdit *Edit3;
        TPanel *Panel12;
        TEdit *Edit4;
        TPanel *Panel24;
        TEdit *Edit5;
        TPanel *Panel25;
        TEdit *Edit6;
        TPanel *Panel26;
        TComboBox *cbb1;
        TEdit *edtCharge1;
        TPanel *Panel21;
        TEdit *Edit7;
        TComboBox *ComboBox1;
        TPanel *Panel27;
        TEdit *Edit8;
        TEdit *Edit9;
        TComboBox *ComboBox4;
        TEdit *Edit14;
        TEdit *Edit15;
        TPanel *Panel30;
        TComboBox *ComboBox2;
        TPanel *Panel28;
        TEdit *Edit10;
        TEdit *Edit11;
        TComboBox *ComboBox3;
        TPanel *Panel29;
        TEdit *Edit12;
        TEdit *Edit13;
        TPanel *Panel31;
        TEdit *Edit16;
        TPanel *Panel32;
        TEdit *Edit17;
        TPanel *Panel15;
        TEdit *Edit18;
        TPanel *Panel19;
        TEdit *Edit19;
        TPanel *Panel45;
private:	// User declarations
public:		// User declarations
        __fastcall TTailerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTailerForm *TailerForm;
//---------------------------------------------------------------------------
#endif
