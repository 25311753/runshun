//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BaseCode.h"
#include "UserLogin.h"
#include "DataModule.h"
#include "mainframe.h"
#include "DBSetup.h"
#include "TConst.h"
#include <process.h>
#include "TmpFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUserLoginForm *UserLoginForm;
//---------------------------------------------------------------------------
__fastcall TUserLoginForm::TUserLoginForm(TComponent* Owner)
   : TForm(Owner)
{
   num=0;
}
//---------------------------------------------------------------------------
static int nTryTimes = 0;
void __fastcall TUserLoginForm::OKBtnClick(TObject *Sender)
{
	AnsiString password;
	register i;
	char strPwd[80],strSQL[1024],szSQLV[1024];

	strcpy(strPwd,Edit_Password->Text.c_str());
	for (i=0;i<Edit_Password->Text.Length();i++) //�������
		strPwd[i]^=82;

	//��֤�ʺźͿ��
	if (!dm1->ConnectDB())
	{
		Application->MessageBox("��¼���ݿ�ʧ�ܣ�����ϵͳ����Ա��ϵ��","����",MB_OK+MB_ICONERROR) ;
		ModalResult = mrCancel;
		return;
	}
	sprintf(strSQL,"select * from operator where op_code='%s'",Edit_Code->Text.c_str());
	if(!RunSQL(dm1->Query1,strSQL,true))
	{
		Application->MessageBox("��¼���ݿ�ʧ�ܣ�����ϵͳ����Ա��ϵ��","����",MB_OK+MB_ICONERROR) ;
		ModalResult = mrCancel;
		return;
	}

	if(dm1->Query1->Eof)
	{
		ShowMessage("û�и��û�");
		if(Edit_Code->CanFocus())	Edit_Code->SetFocus();
//    ModalResult = mrCancel;
		return;
	}

	if(dm1->Query1->FieldByName("op_password")->AsString!=strPwd)
	{
		if(nTryTimes==3)
		{
                      Application->MessageBox("��֤ʧ�ܴ���̫��!","����",MB_OK+MB_ICONERROR);
                      ModalResult = mrCancel;
                      return;
		}
		nTryTimes++;
		ShowMessage("�������");
		if(Edit_Password->CanFocus())
			Edit_Password->SetFocus();
		return;
	}

//------------------------------------------------------------------------------
/*
//  ����׫
        sprintf(szSQLV, "select * from Version");
        RunSQL(dm1->Query2, szSQLV, true);
        if (!dm1->Query2->Eof)
        {
                if (dm1->Query2->FieldByName("v_new")->AsString!="v3.5.2")
                {//�汾�ŶԱ�
//                        ShowMessage("�����°汾�Ĳɹ�ϵͳ���汾��Ϊ: "+dm1->Query2->FieldByName("v_new")->AsString+"  �밴OK�������߸���");
                        ShowMessage(dm1->Query2->FieldByName("v_message")->AsString+dm1->Query2->FieldByName("v_new")->AsString+"  ,�밴OK�������߸���");

                        int f;
                        if((f=execl("GSUpdate.bat","GSUpdate.bat",NULL))==-1)
                        {
                                ShowMessage("ϵͳ�����ļ���ʧ��! �������Ա��ϵ.");
                        }
                        else
                        {
                                ShowMessage("ϵͳ�����������°汾,�°�汾��Ϊ��"+dm1->Query2->FieldByName("v_new")->AsString);
                        }
                        return;
                }
        }
*/
//------------------------------------------------------------------------------

	operatorcode=dm1->Query1->FieldByName("op_code")->AsString;           // ����Ա����
	operatorname=dm1->Query1->FieldByName("op_name")->AsString;           // ����Ա����
	operator_class=dm1->Query1->FieldByName("op_class")->AsString;        // ����Ա�ȼ�
	corpcode=dm1->Query1->FieldByName("op_cpcode")->AsString;             // ��˾��

	ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TUserLoginForm::CancelBtnClick(TObject *Sender)
{
	ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TUserLoginForm::Edit_CodeKeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key has been pressed
    {
        Key=0;
        Edit_Password->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TUserLoginForm::Edit_PasswordKeyPress(TObject *Sender,
      char &Key)
{
    if (Key==13) //enter key has been pressed
    {
        Key=0;
        OKBtnClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TUserLoginForm::FormShow(TObject *Sender)
{
    Edit_Code->SetFocus();
    Edit_Code->Clear();
    Edit_Password->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TUserLoginForm::btnDBSetupClick(TObject *Sender)
{
	TDBSetupForm *pSetup;
	try
  {
  	pSetup=new TDBSetupForm(this);
    pSetup->ShowModal();
    delete pSetup;
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------



