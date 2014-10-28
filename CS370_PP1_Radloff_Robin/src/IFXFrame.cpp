/***************************************************************
 * Name:      IFX_FrameworkMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Wylder Keane (wylder.keane@gmail.com)
 * Created:   2011-06-23
 * Copyright: Wylder Keane ()
 * License:
 **************************************************************/

#include "IFXFrame.h"
#include <wx/msgdlg.h>
#include <iostream>

//(*InternalHeaders(IFXFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//Image Handling System
#include "ImRecipe.h"
#include "IFXPropertyPanel.h"

//ImStages
#include "InvertStage.h"
//#include "CombinationStage.h"
//#include "LogTransform.h"
//#include "GammaTransform.h"
//#include "HistogramEqualizer.h"
//#include "SpatialFilter.h"
//#include "FFTStage.h"
//#include "SaltPepper.h"
//#include "MedianFilter.h"
//#include "GaussianNoise.h"
//#include "LocalNoiseReduction.h"
//#include "AdaptiveMedianFilter.h"
//#include "BilateralFilter.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(IFXFrame)
const long IFXFrame::ID_FXSelection = wxNewId();
const long IFXFrame::ID_EditFX = wxNewId();
const long IFXFrame::ID_AddFX = wxNewId();
const long IFXFrame::ID_FXCheckList = wxNewId();
const long IFXFrame::ID_MoveFXUp = wxNewId();
const long IFXFrame::ID_MoveFXDown = wxNewId();
const long IFXFrame::ID_RemoveFX = wxNewId();
const long IFXFrame::ID_ClearFX = wxNewId();
const long IFXFrame::ID_FXControlPanel = wxNewId();
const long IFXFrame::ID_FXPropertiesPanel = wxNewId();
const long IFXFrame::ID_RecipeSelection = wxNewId();
const long IFXFrame::ID_SourceImagePanel = wxNewId();
const long IFXFrame::ID_FinalImageSelection = wxNewId();
const long IFXFrame::ID_FinalImagePanel = wxNewId();
const long IFXFrame::ID_SourceImage2Selection = wxNewId();
const long IFXFrame::ID_SourceImagePanel2 = wxNewId();
const long IFXFrame::ID_FinalImage2Selection = wxNewId();
const long IFXFrame::ID_FinalImagePanel2 = wxNewId();
const long IFXFrame::ID_OpenItem = wxNewId();
const long IFXFrame::ID_SaveAsItem = wxNewId();
const long IFXFrame::idMenuQuit = wxNewId();
const long IFXFrame::idMenuAbout = wxNewId();
const long IFXFrame::ID_ScaleNN = wxNewId();
const long IFXFrame::ID_ScaleBilinear = wxNewId();
const long IFXFrame::ID_CommandPrompt = wxNewId();
const long IFXFrame::ID_CommandPanel = wxNewId();
//*)

BEGIN_EVENT_TABLE(IFXFrame,wxFrame)
    //(*EventTable(IFXFrame)
    //*)
END_EVENT_TABLE()

IFXFrame::IFXFrame(wxWindow* parent,wxWindowID id)
{
  ScalingType = 0;

  //Build the GUI
  InitGui(parent,id);

  //Initialize
  mCurrentRecipe = NULL;
  mCurrentProperties = NULL;

  //Register all stages with the system
  RegisterStage(InvertStage);
  //RegisterStage(CombinationStage);
  //RegisterStage(LogTransform);
  //RegisterStage(GammaTransform);
  //RegisterStage(HistogramEqualizer);
  //RegisterStage(GaussianBlur);
  //RegisterStage(UnsharpMask);
  //RegisterStage(SobelOperator);
  //RegisterStage(FFTStage);
  //RegisterStage(IFFTStage);
  //RegisterStage(SaltPepper);
  //RegisterStage(MedianFilter);
  //RegisterStage(GaussianNoise);
  //RegisterStage(LocalNoiseReduction);
  //RegisterStage(AdaptiveMedianFilter);
  //RegisterStage(BilateralFilter);
}

IFXFrame::~IFXFrame()
{
  //(*Destroy(IFXFrame)
  //*)

  //delete mPipeline;
}

void IFXFrame::InitGui(wxWindow* parent, wxWindowID id)
{
  //(*Initialize(IFXFrame)
  wxFlexGridSizer* FlexGridSizer1;
  wxFlexGridSizer* FlexGridSizer2;
  wxFlexGridSizer* FlexGridSizer3;
  wxFlexGridSizer* FlexGridSizer4;
  wxFlexGridSizer* FlexGridMain;
  wxGridSizer* GridSizer1;
  wxGridSizer* GridSizer2;
  wxGridSizer* GridSizer3;
  wxGridSizer* GridSizer4;
  wxGridSizer* GridSizer5;
  wxFlexGridSizer* FlexGridSizer6;
  wxMenuBar* MainMenu;
  wxMenu* FileMenu;
  wxMenuItem* OpenItem;
  wxMenuItem* SaveAsItem;
  wxMenuItem* QuitItem;
  wxMenu* HelpMenu;
  wxMenuItem* AboutItem;
  wxButton* FXScaleNN;
  wxButton* FXScaleBilinear;

  mImagePanelSize.Set(512,512);

  Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxNO_BORDER, _T("wxID_ANY"));
  SetMinSize(wxSize(756,396));
  FlexGridMain = new wxFlexGridSizer(2, 1, 0, 0);
  FlexGridMain->AddGrowableCol(0);
  FlexGridMain->AddGrowableRow(0);
  FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
  FlexGridSizer1->AddGrowableCol(1);
  FlexGridSizer1->AddGrowableRow(0);

  GridSizer2 = new wxGridSizer(1, 1, 0, 0);
  FXControlPanel = new wxPanel(this, ID_FXControlPanel, wxDefaultPosition, wxSize(310,271*2), wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_FXControlPanel"));
  FlexGridSizer2 = new wxFlexGridSizer(3, 2, 0, 0);
  FXSelection = new wxChoice(FXControlPanel, ID_FXSelection, wxDefaultPosition, wxSize(150,21), 0, 0, 0, wxDefaultValidator, _T("ID_FXSelection"));
  FlexGridSizer2->Add(FXSelection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  AddFX = new wxButton(FXControlPanel, ID_AddFX, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_AddFX"));
  FlexGridSizer2->Add(AddFX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  FXCheckList = new wxCheckListBox(FXControlPanel, ID_FXCheckList, wxDefaultPosition, wxSize(178,236), 0, 0, 0, wxDefaultValidator, _T("ID_FXCheckList"));
  FlexGridSizer2->Add(FXCheckList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

  GridSizer1 = new wxGridSizer(3, 1, 0, 0);
  GridSizer3 = new wxGridSizer(4, 1, 0, 0);
  EditFXButton = new wxButton(FXControlPanel,ID_EditFX, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EditFX"));
  GridSizer3->Add(EditFXButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  MoveFXUpButton = new wxButton(FXControlPanel, ID_MoveFXUp, _("Up"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MoveFXUp"));
  GridSizer3->Add(MoveFXUpButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  MoveFXDownButton = new wxButton(FXControlPanel, ID_MoveFXDown, _("Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MoveFXDown"));
  GridSizer3->Add(MoveFXDownButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  RemoveFX = new wxButton(FXControlPanel, ID_RemoveFX, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RemoveFX"));
  GridSizer3->Add(RemoveFX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  ClearFX = new wxButton(FXControlPanel, ID_ClearFX, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ClearFX"));
  GridSizer3->Add(ClearFX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  GridSizer1->Add(GridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer2->Add(GridSizer1, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

  GridSizer5 = new wxGridSizer(3, 1, 0, 0);
  FXScaleNN = new wxButton(FXControlPanel, ID_ScaleNN, _("Nearest Neighbor Scaling"), wxDefaultPosition, wxSize(150, 21), 0, wxDefaultValidator, _T("ID_ScaleNN"));
  GridSizer5->Add(FXScaleNN, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FXScaleBilinear = new wxButton(FXControlPanel, ID_ScaleBilinear, _("Bilinear Scaling"), wxDefaultPosition, wxSize(150, 21), 0, wxDefaultValidator, _T("ID_ScaleBilinear"));
  GridSizer5->Add(FXScaleBilinear, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer2->Add(GridSizer5, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

  FXControlPanel->SetSizer(FlexGridSizer2);
  FlexGridSizer2->SetSizeHints(FXControlPanel);
  GridSizer2->Add(FXControlPanel, 1, wxALIGN_LEFT|wxEXPAND|wxALIGN_CENTER_VERTICAL, 1);

  //FXPropertiesPanel = new wxPanel(this, ID_FXPropertiesPanel, wxDefaultPosition, wxDLG_UNIT(this,wxSize(66,63)), wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_FXPropertiesPanel"));
  //FXPropertiesSizer = new wxGridSizer(3, 1, 0, 0);
  //FXPropertiesPanel->SetSizer(FXPropertiesSizer);
  //FXPropertiesSizer->SetSizeHints(FXPropertiesPanel);
  //GridSizer2->Add(FXPropertiesPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);

  FlexGridSizer1->Add(GridSizer2, 1,  wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  GridSizer4 = new wxGridSizer(2, 2, 0, 0);
  FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
  FlexGridSizer3->AddGrowableCol(0);
  FlexGridSizer3->AddGrowableRow(1);
  RecipeSelection = new wxChoice(this, ID_RecipeSelection, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RecipeSelection"));
  FlexGridSizer3->Add(RecipeSelection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);

  SourceImagePanel = new wxPanel(this, ID_SourceImagePanel, wxDefaultPosition, mImagePanelSize, wxRAISED_BORDER | wxTAB_TRAVERSAL, _T("ID_SourceImagePanel"));
  FlexGridSizer3->Add(SourceImagePanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  GridSizer4->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);

  FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
  FlexGridSizer4->AddGrowableCol(0);
  FlexGridSizer4->AddGrowableRow(1);
  FinalImageSelection = new wxChoice(this, ID_FinalImageSelection, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_FinalImageSelection"));
  FlexGridSizer4->Add(FinalImageSelection, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

  FinalImagePanel = new wxPanel(this, ID_FinalImagePanel, wxDefaultPosition, mImagePanelSize, wxRAISED_BORDER | wxTAB_TRAVERSAL, _T("ID_FinalImagePanel"));
  FlexGridSizer4->Add(FinalImagePanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  GridSizer4->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);

  //FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
  //SourceImage2Selection = new wxChoice(this, ID_SourceImage2Selection, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_SourceImage2Selection"));
  //FlexGridSizer6->Add(SourceImage2Selection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  //SourceImagePanel2 = new wxPanel(this, ID_SourceImagePanel2, wxDefaultPosition,ImagePanelSize, wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_SourceImagePanel2"));
  //FlexGridSizer6->Add(SourceImagePanel2, 1, wxGROW|wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  //GridSizer4->Add(FlexGridSizer6, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  //FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
  //FinalImage2Selection = new wxChoice(this, ID_FinalImage2Selection, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_FinalImage2Selection"));
  //FlexGridSizer5->Add(FinalImage2Selection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  //FinalImagePanel2 = new wxPanel(this, ID_FinalImagePanel2, wxDefaultPosition,ImagePanelSize, wxRAISED_BORDER|wxTAB_TRAVERSAL, _T("ID_FinalImagePanel2"));
  //FlexGridSizer5->Add(FinalImagePanel2, 1, wxEXPAND| wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
  //GridSizer4->Add(FlexGridSizer5, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);

  FlexGridSizer1->Add(GridSizer4, 1, wxGROW|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

  FlexGridSizer6 = new wxFlexGridSizer(1, 1, 0, 0);
  CommandPanel = new wxPanel(this, ID_CommandPanel, wxDefaultPosition, wxSize(1000, 100), wxRAISED_BORDER, _T("ID_CommandPanel"));
  FlexGridSizer6->Add(CommandPanel, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);
  CommandInput = new wxTextCtrl(CommandPanel, ID_CommandPrompt, _("Enter a command"), wxDefaultPosition, wxSize(1000, 100), wxTE_PROCESS_ENTER | wxTE_MULTILINE, wxDefaultValidator, _T("ID_CommandsPrompt"));

  FlexGridMain->Add(FlexGridSizer1, 1, wxGROW | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridMain->Add(FlexGridSizer6, 1, wxGROW | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

  SetSizer(FlexGridMain);

  MainMenu = new wxMenuBar();
  FileMenu = new wxMenu();
  OpenItem = new wxMenuItem(FileMenu, ID_OpenItem, _("Open"), wxEmptyString, wxITEM_NORMAL);
  FileMenu->Append(OpenItem);
  SaveAsItem = new wxMenuItem(FileMenu, ID_SaveAsItem, _("Save As..."), wxEmptyString, wxITEM_NORMAL);
  FileMenu->Append(SaveAsItem);
  FileMenu->AppendSeparator();
  QuitItem = new wxMenuItem(FileMenu, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
  FileMenu->Append(QuitItem);
  MainMenu->Append(FileMenu, _("&File"));
  HelpMenu = new wxMenu();
  AboutItem = new wxMenuItem(HelpMenu, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
  HelpMenu->Append(AboutItem);
  MainMenu->Append(HelpMenu, _("Help"));
  SetMenuBar(MainMenu);
  FlexGridMain->Fit(this);

  //Connect all Gui controls to their respective handlers
  Connect(ID_EditFX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnEditFXClick);
  Connect(ID_AddFX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnAddFXClick);
  Connect(ID_FXCheckList,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&IFXFrame::OnFXCheckListToggled);
  Connect(ID_FXCheckList,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&IFXFrame::OnFXCheckListSelected);
  Connect(ID_MoveFXUp,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnMoveFXUpButtonClick);
  Connect(ID_MoveFXDown,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnMoveFXDownButtonClick);
  Connect(ID_RemoveFX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnRemoveFXClick);
  Connect(ID_ClearFX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&IFXFrame::OnClearFXClick);
  Connect(ID_RecipeSelection,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&IFXFrame::OnRecipeSelectionSelect);
  SourceImagePanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&IFXFrame::OnSourceImagePanelPaint,0,this);
  Connect(ID_FinalImageSelection,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&IFXFrame::OnFinalImageSelectionSelect);
  FinalImagePanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&IFXFrame::OnFinalImagePanelPaint,0,this);
  //Connect(ID_SourceImage2Selection,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&IFXFrame::OnSourceImage2SelectionSelect);
  //SourceImagePanel2->Connect(wxEVT_PAINT,(wxObjectEventFunction)&IFXFrame::OnSourceImagePanel2Paint,0,this);
  //Connect(ID_FinalImage2Selection,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&IFXFrame::OnFinalImage2SelectionSelect);
  //FinalImagePanel2->Connect(wxEVT_PAINT,(wxObjectEventFunction)&IFXFrame::OnFinalImagePanel2Paint,0,this);
  Connect(ID_OpenItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IFXFrame::OnOpenFile);
  Connect(ID_SaveAsItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IFXFrame::OnSaveFileAs);
  Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IFXFrame::OnQuit);
  Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IFXFrame::OnAbout);
  Connect(wxEVT_SIZE,(wxObjectEventFunction)&IFXFrame::OnSize);
  Connect(ID_ScaleNN, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&IFXFrame::OnNNScaling);
  Connect(ID_ScaleBilinear, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&IFXFrame::OnBLScaling);
  Connect(ID_CommandPrompt, wxEVT_COMMAND_TEXT_ENTER, (wxObjectEventFunction)&IFXFrame::OnCommandEntered);
  //*)

}

void IFXFrame::OnCommandEntered(wxCommandEvent& event)
{
  wxString command = CommandInput->GetLineText(CommandInput->GetNumberOfLines() - 1);
  int length = command.Length();
  if (length >= 3)
  {
    wxString beginning = command.SubString(0, 2);
    bool result = beginning.IsSameAs("cd ", false);
    if (result == true)
    {
      command = command.SubString(3, length - 1);
      cd = command;
    }
    else
    {
      if (length >= 5)
      {
        beginning = command.SubString(0, 4);
        command = command.SubString(5, length - 1);
        wxString cdTemp = cd;
        cdTemp.Append("\\");
        if (beginning.IsSameAs("load ", false))
        {
          // We can load the file
          Image2D *image = Image2D::readImage(cdTemp.Append(command, command.Length()), command);
          if (image)
          {
            ImRecipe *recipe = new ImRecipe(image->GetId());
            mCookbook.push_back(recipe);
            RecipeSelection->Append(command);
          }
          else
            wxMessageBox(_T("Unable to load the file. Check the file path & permissions."), _T("Image Application 1.0"));
        }
        else if (beginning.IsSameAs("save ", false))
        {
          // Save the file
          Image2D::writeImage(cdTemp.Append(command, command.Length()), *mCurrentRecipe->GetResults()[0]);
        }
      }
    }
  }
}

void IFXFrame::OnSize(wxSizeEvent& event)
{
  wxFrame::OnSize(event);
  mImagePanelSize.Set(FinalImagePanel->GetSize().GetWidth(), FinalImagePanel->GetSize().GetHeight());

  SourceImagePanel->Refresh();
  FinalImagePanel->Refresh();
}

void IFXFrame::OnNNScaling(wxCommandEvent& event)
{
  ScalingType = 0;
  FinalImagePanel->Refresh();
}

void IFXFrame::OnBLScaling(wxCommandEvent& event)
{
  ScalingType = 1;
  FinalImagePanel->Refresh();
}

void IFXFrame::InitPropertyPanel(unsigned index)
{
}

void IFXFrame::OnQuit(wxCommandEvent& event)
{
  Close();
}

void IFXFrame::OnAbout(wxCommandEvent& event)
{
  wxString msg = wxbuildinfo(long_f);
  wxMessageBox(msg, _("Welcome to..."));
}

void IFXFrame::OnMoveFXUpButtonClick(wxCommandEvent& event)
{
  uint item = FXCheckList->GetSelection();
  if (item != wxNOT_FOUND && item > 0)
  {
    bool checked = FXCheckList->IsChecked(item);
    wxString label = FXCheckList->GetStringSelection();
    FXCheckList->Delete(item);
    FXCheckList->Insert(label,item-1);
    FXCheckList->SetSelection(item-1);
    FXCheckList->Check(item - 1,checked);
        
    //Make changes in the ImagePipeline
    mCurrentRecipe->ModifyStage(item,-1);
    mCurrentRecipe->Execute();

    //Update the panel
    FinalImagePanel->Refresh();
  }
}

void IFXFrame::OnMoveFXDownButtonClick(wxCommandEvent& event)
{
  uint item = FXCheckList->GetSelection();
  if (item != wxNOT_FOUND && item < (FXCheckList->GetCount() - 1) )
  {
    bool checked = FXCheckList->IsChecked(item);
    wxString label = FXCheckList->GetStringSelection();
    FXCheckList->Delete(item);
    FXCheckList->Insert(label, item + 1);
    FXCheckList->SetSelection(item + 1);
    FXCheckList->Check(item + 1,checked);

    //Make changes in the ImagePipeline
    mCurrentRecipe->ModifyStage(item,1);
    mCurrentRecipe->Execute();
        
    //Update the panel
    FinalImagePanel->Refresh();
  }
}
void IFXFrame::OnEditFXClick(wxCommandEvent& event)
{
  //Nothing selected, do nothing
  if (!mCurrentRecipe)
    return;

  //Get the currently selected stage
  uint index = FXCheckList->GetSelection();
  
  if (!(index < mCurrentRecipe->GetStages().size()))
    return;

  ImStage *stage = mCurrentRecipe->GetStages()[FXCheckList->GetSelection()];

  //Get the property list from the stage
  if (stage->GetProperties()->ShowModal() == wxID_OK)
  {
    mCurrentRecipe->Execute();
    FinalImagePanel->Refresh();
  }
}

void IFXFrame::OnAddFXClick(wxCommandEvent& event)
{
  uint index = FXSelection->GetSelection();
  if (index != wxNOT_FOUND)
  {
    uint position = FXCheckList->GetSelection();
    ImStage * stage = mStageLibrary[index]->Clone();
    stage->BuildProperties(this);

    mCurrentRecipe->InsertStage(stage,position);

    if (position != wxNOT_FOUND)
      FXCheckList->Insert(stage->GetLabel(),position);
    else
      FXCheckList->Append(stage->GetLabel());

    //Update recipe
    mCurrentRecipe->Execute();
        
    //Add stage to a PropertyPanel
    
    //Update the panel
    FinalImagePanel->Refresh();
  }
  
}

void IFXFrame::OnRemoveFXClick(wxCommandEvent& event)
{
  uint item = FXCheckList->GetSelection();
  if (item != wxNOT_FOUND)
  {

    mCurrentRecipe->RemoveStage(item);
    FXCheckList->Delete(item);

    //Update recipe
    mCurrentRecipe->Execute();

    //Update the panel
    FinalImagePanel->Refresh();
  }
}

void IFXFrame::OnClearFXClick(wxCommandEvent& event)
{
  mCurrentRecipe->ClearStages();
  FXCheckList->Clear();

  //Default stage always remains
  mCurrentRecipe->Execute();
    
  //Update the panel
  FinalImagePanel->Refresh();
}

void IFXFrame::OnSourceImagePanelPaint(wxPaintEvent& event)
{
  wxPaintDC dc(SourceImagePanel);
  PrepareDC( dc );

  if (!mCurrentRecipe)
    return;

  ImageId id = mCurrentRecipe->GetId();
  Image2D *image = Image2D::findImage(id);

  if (image)
  {
    if (!image->IsValid())
      return;

    // Resizing image to fit window only if image is larger than window
    wxImage img(image->GetWidth(), image->GetHeight(), image->GetData(), true);

    int newWidth, newHeight;
    if (mImagePanelSize.GetWidth() < image->GetWidth() || mImagePanelSize.GetHeight() < image->GetHeight())
    {
      double ratioX = (double)mImagePanelSize.GetWidth() / (double)image->GetWidth();
      double ratioY = (double)mImagePanelSize.GetHeight() / (double)image->GetHeight();
      double ratio = ratioX < ratioY ? ratioX : ratioY;

      newHeight = image->GetHeight() * ratio;
      newWidth = image->GetWidth() * ratio;
      img.Rescale(newWidth, newHeight);
    }

    //img.Rescale(mImagePanelSize.GetWidth(), mImagePanelSize.GetHeight());
    //img.Rescale(newWidth, newHeight);
    //if (img.IsOk())
      dc.DrawBitmap(img, wxPoint(0,0));
  }
}

void IFXFrame::OnFinalImagePanelPaint(wxPaintEvent& event)
{
  wxPaintDC dc(FinalImagePanel);
  PrepareDC( dc );

  if (!mCurrentRecipe)
    return;

  //Update images
  mCurrentRecipe->Execute();

  uint index = FinalImageSelection->GetSelection();
  if (index == wxNOT_FOUND)
    return;

  Image2D *image = Image2D::findImage(mCurrentRecipe->GetResults()[index]);
  if (image)
  {
    if (!image->IsValid())
      return;

    image->ScaleTo(mImagePanelSize.GetWidth(), mImagePanelSize.GetHeight(), ScalingType);
    wxImage img(image->GetWidth(),image->GetHeight(),image->GetData(),true);
    
    //img.Rescale(mImagePanelSize.GetWidth(),mImagePanelSize.GetHeight());

    //if (img.IsOk())
      dc.DrawBitmap(img, wxPoint(0,0));
  }
}

void IFXFrame::OnSourceImagePanel2Paint(wxPaintEvent& event)
{
  //This must be here or App will crash
  wxPaintDC dc(SourceImagePanel2);
  PrepareDC(dc);
}

void IFXFrame::OnFinalImagePanel2Paint(wxPaintEvent& event)
{
  //This must be here or App will crash
  wxPaintDC dc(FinalImagePanel2);
  PrepareDC(dc);
}

void IFXFrame::OnOpenFile(wxCommandEvent& event)
{
	wxFileDialog  dlg( this, _T("Select a PPM file"), wxEmptyString, wxEmptyString, _T("*.*") );

	if( dlg.ShowModal() == wxID_OK )
	{
		wxString sFilename = dlg.GetPath();

    Image2D *image = Image2D::readImage(sFilename,dlg.GetFilename());
    if (image)
    {
      //Add source image and also generate a final image
      ImRecipe *recipe = new ImRecipe(image->GetId());

      mCookbook.push_back(recipe);
      RecipeSelection->Append(dlg.GetFilename());
    }
    else
      wxMessageBox( _T("Unable to load the file. Check the file path & permissions."), _T("Image Application 1.0") );
	}
}

void IFXFrame::OnSaveFileAs(wxCommandEvent& event)
{
  //TODO: Make this save as filetypes other than ppm
  wxFileDialog  dlg( this, _T("Save As..."), wxEmptyString, wxEmptyString, _T("*.ppm"), wxFD_SAVE );

  if( dlg.ShowModal() == wxID_OK )
  {
    wxString sFilename = dlg.GetPath();

    Image2D::writeImage(sFilename, *mCurrentRecipe->GetResults()[0]);

    //wxMessageBox( _T("Saving not implemented yet...") );

    //Save the FinalImage referenced to disc to disk
  }
}

void IFXFrame::OnFXCheckListToggled(wxCommandEvent& event)
{
  uint image = RecipeSelection->GetSelection();
  uint stage = event.GetInt();
  bool checked = FXCheckList->IsChecked(stage);
  mCurrentRecipe->EnableStage(stage,checked);

  mCurrentRecipe->Execute();
    
  //Update the panel
  FinalImagePanel->Refresh();
}

void IFXFrame::OnFXCheckListSelected(wxCommandEvent& event)
{
  InitPropertyPanel(event.GetSelection());
}

void IFXFrame::OnRecipeSelectionSelect(wxCommandEvent& event)
{
  //Set which image is to be rendered
  uint index = RecipeSelection->GetSelection();
  if (index == wxNOT_FOUND)
    return;

  //Set current recipe to the selection
  mCurrentRecipe = mCookbook[index];

  FXCheckList->Clear();
  const std::vector<ImStage *> &stages = mCurrentRecipe->GetStages();
  for (uint i = 0; i < stages.size(); ++i)
  {
    ImStage *im = stages[i];
    FXCheckList->Append(im->GetLabel());
    FXCheckList->Check(i,im->IsActive());
  }

  FinalImageSelection->Clear();
  const std::vector<ImageId> &results = mCurrentRecipe->GetResults();
  for (uint i = 0; i < results.size(); ++i)
  {
    Image2D *image = Image2D::findImage(results[i]);
    FinalImageSelection->Append(results[i].mName);
  }

  //Update recipe
  mCurrentRecipe->Execute();

  //Refresh the panel
  SourceImagePanel->Refresh();

  //Update results panel
  FinalImageSelection->Select(0);
  FinalImagePanel->Refresh();
}

void IFXFrame::OnFinalImageSelectionSelect(wxCommandEvent& event)
{
}

void IFXFrame::OnSourceImage2SelectionSelect(wxCommandEvent& event)
{
}

void IFXFrame::OnFinalImage2SelectionSelect(wxCommandEvent& event)
{
}
