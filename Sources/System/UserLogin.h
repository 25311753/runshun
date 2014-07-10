//---------------------------------------------------------------------------

#ifndef loginunitH
#define loginunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include "auAutoUpgrader.hpp"
#include "auHTTP.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TUserLoginForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TImage *Image1;
   TBitBtn *OKBtn;
   TBitBtn *CancelBtn;
   TBevel *Bevel1;
   TLabel *Label3;
   TEdit *Edit_Code;
   TLabel *Label4;
   TEdit *Edit_Password;
	TButton *btnDBSetup;
        TLabel *Label2;
        TBevel *Bevel2;
        TLabel *Label5;
        TCheckBox *cb_bkdb;
        TauAutoUpgrader *auAutoUpgrader1;
        TLabel *lb_versions;
        TProgressBar *ProgressBar1;
   void __fastcall OKBtnClick(TObject *Sender);
   void __fastcall CancelBtnClick(TObject *Sender);
   void __fastcall Edit_PasswordKeyPress(TObject *Sender, char &Key);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall Edit_CodeKeyPress(TObject *Sender, char &Key);
	void __fastcall btnDBSetupClick(TObject *Sender);
   void __fastcall connectMasterDB();
   void __fastcall connectBackupDB();
        void __fastcall cb_bkdbClick(TObject *Sender);
        void __fastcall auAutoUpgrader1Aborted(TObject *Sender);
        void __fastcall auAutoUpgrader1Progress(TObject *Sender,
          const AnsiString FileURL, int FileSize, int BytesRead,
          int ElapsedTime, int EstimatedTimeLeft, BYTE PercentsDone,
          BYTE TotalPercentsDone, float TransferRate);
        void __fastcall auAutoUpgrader1BeginUpgrade(TObject *Sender,
          const AnsiString UpgradeMsg, TacUpgradeMethod UpgradeMethod,
          TStringList *Files, bool &CanUpgrade);
private:	// User declarations
   int num;
public:		// User declarations
   __fastcall TUserLoginForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TUserLoginForm *UserLoginForm;
//---------------------------------------------------------------------------
#endif
