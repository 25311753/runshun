//---------------------------------------------------------------------------

#ifndef TypePrt2UnitH
#define TypePrt2UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TTypePrt2Form : public TForm
{
__published:	// IDE-managed Components
   TQuickRep *QuickRep1;
   TQRBand *DetailBand1;
   TQRDBText *QRDBText1;
   TQRDBText *QRDBText2;
   TQRBand *TitleBand1;
   TQRLabel *LabTitle;
   TQRLabel *LabCode;
   TQRLabel *LabName;
   TQRShape *QRShape1;
   TQRBand *PageFooterBand1;
   TQRShape *QRShape2;
   TQRLabel *QRLabel1;
   TQRSysData *QRSysData1;
   TQRLabel *QRLabel2;
private:	// User declarations
public:		// User declarations
   __fastcall TTypePrt2Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypePrt2Form *TypePrt2Form;
//---------------------------------------------------------------------------
#endif
