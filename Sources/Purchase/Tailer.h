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

#include "LfcString.h"
#include <map>
//---------------------------------------------------------------------------
class CVarCharge{
public:
        CVarCharge(TComboBox *_cbbName, TEdit *_edtCharge, TEdit *_edtCost){
                cbbName = _cbbName;
                edtCharge = _edtCharge;
                edtCost = _edtCost;
        }
        TComboBox *cbbName;
        TEdit *edtCharge;
        TEdit *edtCost;
};

class TTailerForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelUp;
        TComboBox *cbbClient;
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
        TCheckBox *cbIsQryByDate;
        TMemo *memoLoadAddress;
        TMemo *memoLading;
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
        void __fastcall edtCharge2Change(TObject *Sender);
        void __fastcall edtCharge3Change(TObject *Sender);
        void __fastcall edtCharge4Change(TObject *Sender);
        void __fastcall edtCharge5Change(TObject *Sender);
        void __fastcall edtCost1Change(TObject *Sender);
        void __fastcall edtCost2Change(TObject *Sender);
        void __fastcall edtCost3Change(TObject *Sender);
        void __fastcall edtCost4Change(TObject *Sender);
        void __fastcall edtCost5Change(TObject *Sender);
        void __fastcall cbbVarChargeName1Change(TObject *Sender);
        void __fastcall cbbVarChargeName2Change(TObject *Sender);
        void __fastcall cbbVarChargeName3Change(TObject *Sender);
        void __fastcall cbbVarChargeName4Change(TObject *Sender);
        void __fastcall cbbVarChargeName5Change(TObject *Sender);
        void __fastcall edtFareChange(TObject *Sender);
        void __fastcall edtFareOutChange(TObject *Sender);
        void __fastcall lstViewDownSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnPrnOutCarClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState; //接单上区状态
        int m_selected_id; //待删除的id，listview-selected时先清空，然后赋值
        CVarCharge *m_v1;
        CVarCharge *m_v2;
        CVarCharge *m_v3;
        CVarCharge *m_v4;
        CVarCharge *m_v5;

        std::map<int, CVarCharge*> m_mVarCharge;  //for CVarCharge
public:		// User declarations
        __fastcall TTailerForm(TComponent* Owner);

        __fastcall ~TTailerForm(void);
        void clean_input();
        void clean_query();
        void ResetCtrl();
        int addData(TObject *Sender);
        void modData(TObject *Sender);
        void refreshMod();
        double sum_charge();
        double sum_cost();
        CString GetTailerChargeInfo();
        bool chk_charge_valid();
        void flushContainer(AnsiString c);
        void _flushVarCharge(AnsiString name, AnsiString charge, AnsiString cost);
        void flushVarCharge(AnsiString c);
        void cb_change_name(int pos);
        void cb_change_charge(int pos);      
        void cb_change_cost(int pos);
        CString GetContainerInfo_local(TListView *lv);
        void getFirstContainerUnit(AnsiString c, int &_cnt, AnsiString &containerno, AnsiString &type, AnsiString &sealid);                
};
//---------------------------------------------------------------------------
extern PACKAGE TTailerForm *TailerForm;
//---------------------------------------------------------------------------
#endif
