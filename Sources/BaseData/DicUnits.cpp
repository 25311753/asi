//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "DicUnits.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicUnitsForm *DicUnitsForm;

// ==================================================================
//单位档输入接口，文件DicUnits.*
void DicUnits(int nAuth)
{
	if(nAuth==AUTH_NONE)
  {
  	ShowMessage("抱歉，您没有这个权限");
    return;
  }

  TDicUnitsForm *pForm;
	try
	{
  	pForm=new TDicUnitsForm(Application);
  }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
    return;
	}
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
// ==================================================================


__fastcall TDicUnitsForm::TDicUnitsForm(TComponent* Owner)
  : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------

void __fastcall TDicUnitsForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------


// --------------------------------------------------------------------------
void TDicUnitsForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtID->Text=pItem->Caption;
  edtName->Text=pItem->SubItems->Strings[0];
}


//---------------------------------------------------------------------------

void TDicUnitsForm::RefreshData()
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from DicUnits");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("du_code")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误!");
    return;
  }
}

void __fastcall TDicUnitsForm::btnAddNewClick(TObject *Sender)
{
  edtID->Text="";
  edtName->Text="";
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtID->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TDicUnitsForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtName->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TDicUnitsForm::btnCancel0Click(TObject *Sender)
{
  int nState;

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  msgState->Caption="工作状态：查询";
  Row2Editor();
  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW: btnAddNew->SetFocus();  break;
    case EN_EDIT:   btnEdit->SetFocus();    break;
    default:  break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDicUnitsForm::btnOK0Click(TObject *Sender)
{
  char strID[80],strName[80],*ptr,strTemp[80];
  int nState;

  edtID->Text=edtID->Text.Trim();
  edtName->Text=edtName->Text.Trim();

  if(edtID->Text.IsEmpty())
  {
  	ShowMessage("请输入编号");
    if(edtID->CanFocus())	edtID->SetFocus();
    return;
  }
  if(edtName->Text.IsEmpty())
  {
  	ShowMessage("请输入名称");
    if(edtName->CanFocus())	edtName->SetFocus();
    return;
  }

  strcpy(strID,edtID->Text.c_str());
  strcpy(strName,edtName->Text.c_str());

  char strSQL[1024];

  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into DicUnits values('%s','%s')",strID,strName);
      break;
    case EN_EDIT:
      sprintf(strSQL,"update DicUnits set du_name='%s' where du_code='%s'",strName,strID);
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }

  if(!dm1->OpenDatabase())  return;

  try
  {
    if(m_enWorkState==EN_ADDNEW)
    {
      char strAddSQL[256];
      sprintf(strAddSQL,"select * from DicUnits where du_code='%s'",strID);
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该编号的记录!");
        edtID->SetFocus();
        return;
      }
    }
    RunSQL(strSQL);
  }
  catch(...)
  {
    ShowMessage("数据库操作错误!");
    return;
  }

  TListItem *pItem;
  if(m_enWorkState==EN_ADDNEW)
  {
  	pItem=ListView1->Items->Add();
    pItem->Caption=edtID->Text;
    pItem->SubItems->Add(edtName->Text);
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtID->Text;
      pItem->SubItems->Strings[0]=edtName->Text;
    }
  }

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  msgState->Caption="工作状态：查询";
  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW: btnAddNew->SetFocus();  break;
    case EN_EDIT:   btnEdit->SetFocus();    break;
    default:  break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDicUnitsForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtID->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from DicUnits where du_code='%s'",edtID->Text.c_str());
  if(!dm1->OpenDatabase())  return;

  if(!RunSQL(strSQL))	return;

  TListItem *pItem;
  pItem=ListView1->Selected;
  if(pItem!=NULL)
  {
  	int nSel=ListView1->Items->IndexOf(pItem);
    ListView1->Items->Delete(nSel);
    ListView1->Selected=NULL;
  }
//  if(nSel>=ctlListBox->Items->Count)
//    nSel=ctlListBox->Items->Count-1;
//  ctlListBox->ItemIndex=nSel;
//  Row2Editor();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void TDicUnitsForm::ResetCtrl()
{
	bool bAuth = m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtID	,false);
    EnableEdit(edtName,false);
    btnOK0->Enabled=false;
    btnCancel0->Enabled=false;

    btnAddNew->Enabled=true && bAuth;
    btnRefresh->Enabled=true;
    btnExit->Enabled=true;
    btnPrint->Enabled=true;
    ListView1->Enabled=true;
//    ctlListBox->Enabled=true;
    if(ListView1->Selected!=NULL)
    {
      btnEdit->Enabled=true && bAuth;
      btnDelete->Enabled=true && bAuth;
    }
    else
    {
      btnEdit->Enabled=false;
      btnDelete->Enabled=false;
    }
  }
  else
  {
    btnAddNew->Enabled=false;
    btnRefresh->Enabled=false;
    btnExit->Enabled=false;
//    ctlListBox->Enabled=false;
    ListView1->Enabled=false;
    btnEdit->Enabled=false;
    btnDelete->Enabled=false;
    btnPrint->Enabled=false;

    EnableEdit(edtName,true);
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtID,true);
    else //修改时不能修改产品编号
	    EnableEdit(edtID,false);
  }
}

void __fastcall TDicUnitsForm::btnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TDicUnitsForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------


#include "PrnBaseData.h"
void __fastcall TDicUnitsForm::btnPrintClick(TObject *Sender)
{
  if(!dm1->OpenDatabase())  return;
  AnsiString szSQL="select du_code as prnID,du_name as prnName from DicUnits order by du_code";
  if(!OpenQuery(dm1->sqlPrint,szSQL.c_str()))
  	return;

  try
  {
	  TPrnBaseDataForm *pForm;
  	pForm=new TPrnBaseDataForm(this);

    pForm->txtTitle->Caption="单位字典表";
    pForm->txtText2->Caption="";
    pForm->txtText3->Caption="";

    pForm->PrnView->PreviewModal() ;
    delete pForm;
  }
  catch(...)
  {
    ShowMessage("打印机返回错误信息，请检查是否安装并设置了默认打印机");
    return;
  }
}
//---------------------------------------------------------------------------


void __fastcall TDicUnitsForm::FormShow(TObject *Sender)
{
	edtID->Text="";
  edtName->Text="";
  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------



void __fastcall TDicUnitsForm::ListView1Click(TObject *Sender)
{
  Row2Editor();
	ResetCtrl();
}
//---------------------------------------------------------------------------



