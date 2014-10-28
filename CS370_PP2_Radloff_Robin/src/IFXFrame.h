/***************************************************************
 * Name:      IFXFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Wylder Keane (wylder.keane@gmail.com)
 * Created:   2011-06-23
 * Copyright: Wylder Keane ()
 * License:
 **************************************************************/

#ifndef IFXFRAME_H
#define IFXFRAME_H

//(*Headers(IFXFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/checklst.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/textctrl.h>

#include <wx/image.h>
#include <vector>

//#include "src/ImRecipe.h"

class IFXPropertyPanel;
class ImRecipe;
class ImStage;

class IFXFrame: public wxFrame
{
    public:
        IFXFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~IFXFrame();

    private:
        //Initialize all Gui controls/views
        void InitGui(wxWindow* parent, wxWindowID id);
        //Sets the property window up for the currently selected effect
        void InitPropertyPanel(unsigned index);

        //(*Handlers(IFXFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckListBox1Toggled(wxCommandEvent& event);
        void OnFXCheckListSelected(wxCommandEvent& event);
        void OnMoveFXUpButtonClick(wxCommandEvent& event);
        void OnMoveFXDownButtonClick(wxCommandEvent& event);
        void OnNewFXToolClick(wxCommandEvent& event);
        void OnEditFXClick(wxCommandEvent& event);
        void OnAddFXClick(wxCommandEvent& event);
        void OnRemoveFXClick(wxCommandEvent& event);
        void OnClearFXClick(wxCommandEvent& event);
        void OnSourceImagePanelPaint(wxPaintEvent& event);
        void OnFinalImagePanelPaint(wxPaintEvent& event);
        void OnSourceImagePanel2Paint(wxPaintEvent& event);
        void OnFinalImagePanel2Paint(wxPaintEvent& event);
        void OnOpenFile(wxCommandEvent& event);
        void OnSaveFileAs(wxCommandEvent& event);
        void OnFXCheckListToggled(wxCommandEvent& event);
        void OnRecipeSelectionSelect(wxCommandEvent& event);
        void OnFinalImageSelectionSelect(wxCommandEvent& event);
        void OnSourceImage2SelectionSelect(wxCommandEvent& event);
        void OnFinalImage2SelectionSelect(wxCommandEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnNNScaling(wxCommandEvent& event);
        void OnBLScaling(wxCommandEvent& event);
        void OnCommandEntered(wxCommandEvent& event);
        //*)

        // Command prompt stuff
        wxString cd;

        //(*Identifiers(IFXFrame)
        static const long ID_FXSelection;
        static const long ID_EditFX;
        static const long ID_AddFX;
        static const long ID_FXCheckList;
        static const long ID_MoveFXUp;
        static const long ID_MoveFXDown;
        static const long ID_RemoveFX;
        static const long ID_ClearFX;
        static const long ID_FXControlPanel;
        static const long ID_FXPropertiesPanel;
        static const long ID_RecipeSelection;
        static const long ID_SourceImagePanel;
        static const long ID_FinalImageSelection;
        static const long ID_FinalImagePanel;
        static const long ID_SourceImage2Selection;
        static const long ID_SourceImagePanel2;
        static const long ID_FinalImage2Selection;
        static const long ID_FinalImagePanel2;
        static const long ID_CommandPanel;
        static const long ID_OpenItem;
        static const long ID_SaveAsItem;
        static const long idMenuQuit;
        static const long idMenuAbout;

        static const long ID_ScaleNN;
        static const long ID_ScaleBilinear;

        static const long ID_CommandPrompt;
        //*)

        int ScalingType;

        //(*Declarations(IFXFrame)
        wxCheckListBox* FXCheckList;
        wxChoice* FinalImageSelection;
        wxChoice* SourceImage2Selection;
        wxButton* MoveFXUpButton;
        wxButton* ClearFX;
        wxButton* RemoveFX;
        wxButton* AddFX;
        wxButton* EditFXButton;
        wxPanel* FXPropertiesPanel;
        wxChoice* RecipeSelection;
        wxPanel* FinalImagePanel;
        wxPanel* FinalImagePanel2;
        wxPanel* FXControlPanel;
        wxPanel* SourceImagePanel2;
        wxPanel* CommandPanel;
        wxChoice* FXSelection;
        wxChoice* FinalImage2Selection;
        wxPanel* SourceImagePanel;
        wxButton* MoveFXDownButton;
        wxTextCtrl* CommandInput;

        wxSize mImagePanelSize;
        //*)
        
        //Current recipe selected
        ImRecipe *mCurrentRecipe;
        IFXPropertyPanel *mCurrentProperties;

        //Recipes 
        std::vector<ImRecipe *> mCookbook;
        std::vector<ImStage *> mStageLibrary;

        DECLARE_EVENT_TABLE()
};

//Allow for easy registering of stages with the system
#define RegisterStage(StageType)            \
  {                                         \
    ImStage *stage = new StageType();       \
    FXSelection->Append(stage->GetLabel()); \
    mStageLibrary.push_back(stage);         \
  }

#endif // IFX_FRAMEWORKMAIN_H
