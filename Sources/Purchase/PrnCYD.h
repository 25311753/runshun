//---------------------------------------------------------------------------

#ifndef PrnCYDH
#define PrnCYDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnCYDForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *PageHeaderBand1;
        TQRShape *QRShape10;
        TQRShape *QRShape15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel4;
        TQRLabel *qrl_date;
        TQRLabel *QRLabel3;
        TQRShape *QRShape1;
        TQRLabel *QRLabel5;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRLabel *QRLabel6;
        TQRShape *QRShape6;
        TQRLabel *QRLabel7;
        TQRShape *QRShape7;
        TQRShape *QRShape8;
        TQRShape *QRShape9;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape14;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRShape *QRShape18;
        TQRShape *QRShape19;
        TQRShape *QRShape20;
        TQRShape *QRShape21;
        TQRShape *QRShape22;
        TQRShape *QRShape23;
        TQRShape *QRShape24;
        TQRShape *QRShape25;
        TQRShape *QRShape26;
        TQRShape *QRShape27;
        TQRShape *QRShape28;
        TQRShape *QRShape29;
        TQRShape *QRShape30;
        TQRShape *QRShape31;
        TQRShape *QRShape32;
        TQRShape *QRShape33;
        TQRShape *QRShape34;
        TQRShape *QRShape35;
        TQRShape *QRShape36;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
        TQRLabel *QRLabel19;
        TQRLabel *QRLabel20;
        TQRLabel *QRLabel21;
        TQRLabel *QRLabel22;
        TQRLabel *QRLabel23;
        TQRLabel *QRLabel24;
        TQRLabel *qrlCarNo;
        TQRLabel *qrlLoadAddress;
        TQRLabel *qrlOpDate;
        TQRLabel *qrlLading;
        TQRLabel *qrlContainerType;
        TQRLabel *qrlBeiZhu;
        TQRLabel *QRLabel25;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnCYDForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnCYDForm *PrnCYDForm;
//---------------------------------------------------------------------------
#endif
