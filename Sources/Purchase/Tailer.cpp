//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Tailer.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TTailerForm *TailerForm;
//---------------------------------------------------------------------------
void Tailer(int nAuth)
{
        CALL_FORM(TTailerForm);
}
__fastcall TTailerForm::TTailerForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
