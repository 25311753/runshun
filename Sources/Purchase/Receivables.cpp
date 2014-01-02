//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Receivables.h"  
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common_busi.hpp"
#include "common.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TReceivablesForm *ReceivablesForm;
void Receivables(int nAuth)
{
        CALL_FORM(TReceivablesForm);
}
//---------------------------------------------------------------------------
__fastcall TReceivablesForm::TReceivablesForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

