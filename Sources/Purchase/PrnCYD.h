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
        TQRBand *TitleBand1;
        TQRLabel *QRLabel25;
        TQRLabel *QRLabel26;
        TQRLabel *QRLabel27;
        TQRLabel *QRLabel28;
        TQRLabel *qrl_date2;
        TQRShape *QRShape2;
        TQRShape *QRShape37;
        TQRLabel *QRLabel30;
        TQRShape *QRShape38;
        TQRLabel *QRLabel31;
        TQRShape *QRShape39;
        TQRShape *QRShape40;
        TQRLabel *qrlCarNo2;
        TQRShape *QRShape41;
        TQRLabel *QRLabel33;
        TQRShape *QRShape42;
        TQRLabel *QRLabel34;
        TQRLabel *QRLabel35;
        TQRShape *QRShape43;
        TQRShape *QRShape44;
        TQRLabel *QRLabel36;
        TQRShape *QRShape45;
        TQRLabel *QRLabel37;
        TQRShape *QRShape46;
        TQRLabel *QRLabel38;
        TQRShape *QRShape47;
        TQRLabel *qrlContainerType2;
        TQRShape *QRShape48;
        TQRLabel *qrlLading2;
        TQRShape *QRShape49;
        TQRLabel *QRLabel41;
        TQRShape *QRShape50;
        TQRShape *QRShape51;
        TQRLabel *QRLabel42;
        TQRShape *QRShape52;
        TQRLabel *QRLabel43;
        TQRShape *QRShape53;
        TQRLabel *QRLabel44;
        TQRShape *QRShape54;
        TQRShape *QRShape55;
        TQRLabel *QRLabel45;
        TQRShape *QRShape56;
        TQRShape *QRShape57;
        TQRLabel *QRLabel46;
        TQRShape *QRShape58;
        TQRLabel *QRLabel47;
        TQRShape *QRShape59;
        TQRShape *QRShape60;
        TQRShape *QRShape61;
        TQRLabel *qrlOpDate2;
        TQRShape *QRShape62;
        TQRLabel *QRLabel49;
        TQRLabel *QRLabel50;
        TQRShape *QRShape63;
        TQRShape *QRShape64;
        TQRShape *QRShape65;
        TQRLabel *QRLabel51;
        TQRLabel *QRLabel52;
        TQRShape *QRShape66;
        TQRLabel *QRLabel53;
        TQRShape *QRShape67;
        TQRShape *QRShape68;
        TQRShape *QRShape69;
        TQRLabel *QRLabel54;
        TQRLabel *QRLabel55;
        TQRLabel *QRLabel56;
        TQRLabel *qrlBeiZhu2;
        TQRLabel *qrlLoadAddress2;
        TQRShape *QRShape70;
        TQRLabel *QRLabel29;
        TQRLabel *QRLabel32;
        TQRLabel *QRLabel39;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnCYDForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnCYDForm *PrnCYDForm;
//---------------------------------------------------------------------------
#endif
