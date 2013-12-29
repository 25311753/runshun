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
        TEdit *edtTranCompany;
        TEdit *edtBeiZhu;
        TComboBox *cbbGoodsPerf;
        TDateTimePicker *dtpOpDateHHMM;
        TEdit *edtContainerNo;
        TComboBox *cbbContainerType;
        TButton *btnAddContainer;
        TListView *lstViewContainer;
        TButton *btnModContainer;
        TButton *btnDelContainer;
        TEdit *edtSealId;
        TDateTimePicker *dtpOpDateYYYYMMDD;
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
        TEdit *edtLoadLinkMan;
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnDel;
        TPanel *pl_query;
        TEdit *edtQryLading;
        TEdit *edtQryJZS;
        TButton *btnQuery;
        TDateTimePicker *dtpQryOpDate;
        TDateTimePicker *dtpQryOpDateEnd;
        TComboBox *cbbQryClient;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel20;
        TPanel *Panel23;
        TComboBox *cbbQryGoodsPerf;
        TButton *btnClearQryCond;
        TButton *btnCancel;
        TButton *btnOK;
        TButton *Button1;
        TListView *lstViewDown;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TButton *btnPrnOutCar;
        TPanel *Panel1;
        TEdit *edtLoadAddress;
        TPanel *Panel8;
        TEdit *edtLoadTel;
        TPanel *Panel9;
        TEdit *edtFare;
        TPanel *Panel12;
        TEdit *edtFareOut;
        TPanel *Panel24;
        TEdit *edtCarNo;
        TPanel *Panel25;
        TEdit *edtDriver;
        TPanel *pl_input_varcharge;
        TComboBox *cbbVarChargeName1;
        TEdit *edtCharge1;
        TPanel *Panel21;
        TEdit *edtCost1;
        TComboBox *cbbVarChargeName2;
        TPanel *Panel27;
        TEdit *edtCost2;
        TEdit *edtCharge2;
        TComboBox *cbbVarChargeName5;
        TEdit *edtCharge5;
        TEdit *edtCost5;
        TPanel *Panel30;
        TComboBox *cbbVarChargeName3;
        TPanel *Panel28;
        TEdit *edtCost3;
        TEdit *edtCharge3;
        TComboBox *cbbVarChargeName4;
        TPanel *Panel29;
        TEdit *edtCost4;
        TEdit *edtCharge4;
        TPanel *Panel31;
        TEdit *edtTotalCharge;
        TPanel *Panel32;
        TEdit *edtTotalCost;
        TPanel *Panel15;
        TEdit *edtQryTranCompany;
        TPanel *Panel19;
        TEdit *edtQryDriver;
        TPanel *pl_input;
        TPanel *Panel45;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnClearQryCondClick(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall cbbClientSelect(TObject *Sender);
        void __fastcall cbbClientChange(TObject *Sender);
        void __fastcall cbbQryClientSelect(TObject *Sender);
        void __fastcall cbbQryClientChange(TObject *Sender);
        void __fastcall lstViewContainerSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnAddContainerClick(TObject *Sender);
        void __fastcall btnModContainerClick(TObject *Sender);
        void __fastcall btnDelContainerClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall edtCharge1Change(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState; //�ӵ�����״̬
public:		// User declarations
        __fastcall TTailerForm(TComponent* Owner);
        void clean_input();
        void clean_query();
        void ResetCtrl();
        int add(TObject *Sender);
        void mod(TObject *Sender);
        void refreshMod();           
};
//---------------------------------------------------------------------------
extern PACKAGE TTailerForm *TailerForm;
//---------------------------------------------------------------------------
#endif
