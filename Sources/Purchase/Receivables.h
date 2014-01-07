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
        TPanel *Panel3;
        TComboBox *cbbQryStatus;
        TButton *btnQry;
        TPanel *Panel4;
        TDateTimePicker *dtpQryShouldRecvDate;
        TDateTimePicker *dtpQryShouldRecvDateEnd;
        TCheckBox *cbIsQryByDate;
        TButton *btnCleanQry;
        TCheckBox *cbRecvFlag;
        TButton *btnNewGoOn;
        void __fastcall btnCleanQryClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall cbbQryClientSelect(TObject *Sender);
        void __fastcall cbbQryClientChange(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall lstViewDownMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall edtChargeChange(TObject *Sender);
        void __fastcall cbbStatusChange(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall lstViewDownCustomDrawSubItem(
          TCustomListView *Sender, TListItem *Item, int SubItem,
          TCustomDrawState State, bool &DefaultDraw);
        void __fastcall lstViewDownAdvancedCustomDrawSubItem(
          TCustomListView *Sender, TListItem *Item, int SubItem,
          TCustomDrawState State, TCustomDrawStage Stage,
          bool &DefaultDraw);
        void __fastcall lstViewDownAdvancedCustomDrawItem(
          TCustomListView *Sender, TListItem *Item, TCustomDrawState State,
          TCustomDrawStage Stage, bool &DefaultDraw);
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall btnNewGoOnClick(TObject *Sender);
        void __fastcall cbbClientChange(TObject *Sender);
        void __fastcall cbbClientSelect(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE, EN_EDIT, EN_ADD, EN_NEW } m_enWorkState;
        int m_hl_col;
//        bool m_cell_selected;
public:		// User declarations
        __fastcall TReceivablesForm(TComponent* Owner);
        void clean_query();
        void clean_input();
        void draw_column(TListView *lv, int start_date, int end_date);
        int add_empty_row();
        int get_col_pos(int redv_date);
        void ResetCtrl();
        void clean_listview();
        bool cell2input(AnsiString client, int recv_date);    //true-have data, edit status; false-no data, new status
        bool chk_input();
        void refreshLvByInput();
        void flush_total_row(int row);
        void flush_total_col(int col);
        void refreshLvByInputNew();

};
//---------------------------------------------------------------------------
extern PACKAGE TReceivablesForm *ReceivablesForm;
//---------------------------------------------------------------------------
#endif
