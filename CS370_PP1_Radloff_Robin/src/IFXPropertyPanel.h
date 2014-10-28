/***************************************************************
 * Name:      IFXPropertyPanel.h
 * Purpose:   Defines Application Property Panel
 * Author:    Wylder Keane (wylder.keane@gmail.com)
 * Created:   2011-06-23
 * Copyright: Wylder Keane ()
 * License:
 **************************************************************/

#ifndef IFXPROPERTYPANEL_H
#define IFXPROPERTYPANEL_H

//Standards
#include <vector>

//wxWidgets
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/radiobox.h>
#include <wx/choice.h>
#include <wx/textctrl.h>

typedef unsigned uint;

class wxFlexGridSizer;

//An IFXProperty is a tweakable item that interfaces
//with some specific stage. They are generic and
class IFXProperty : public wxEvtHandler
{
protected:
  enum {
    cDefaultFlags =  wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,
    cDefaultBorder = 5
  };

public:
  IFXProperty() {}
  virtual ~IFXProperty() {}
};

//Property Types
//CheckBox
template <typename cType>
class IFXCheckBox : public IFXProperty
{
public:
  IFXCheckBox(wxWindow *parent, const wxString &label, cType *object, void (cType::*method)(bool))
  {
    mObject = object;
    mMethod = method;

    mCheckBox = new wxCheckBox(parent,wxNewId(),label);
    mCheckBox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&IFXCheckBox::EventHandler,0,this);
  }

  void EventHandler(wxCommandEvent &event)
  {
    (mObject->*mMethod)(event.IsChecked());
  }

//private:
  cType *mObject;
  void (cType::*mMethod)(bool);
  wxCheckBox *mCheckBox;
};


//RadioBox
template <typename cType>
class IFXRadioBox : public IFXProperty
{
public:
  IFXRadioBox(wxWindow *parent, const wxString &label, wxArrayString &choices, cType *object, void(cType::*method)(unsigned))
  {
    mObject = object;
    mMethod = method;

    mRadioBox = new wxRadioBox(parent,wxNewId(),label,wxDefaultPosition,wxDefaultSize,choices);
    mRadioBox->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&IFXRadioBox::EventHandler,0,this);
  }

  void EventHandler(wxCommandEvent &event)
  {
    (mObject->*mMethod)(mRadioBox->GetSelection());
  }

  void SetItemLabel(uint item, const wxString &label)
  {
    mRadioBox->SetLabel(label,item);
  }

//private:
  cType *mObject;
  void (cType::*mMethod)(unsigned);
  wxRadioBox *mRadioBox;
};

//ChoiceBox
template <typename cType>
class IFXChoiceBox : public IFXProperty
{
public:
  IFXChoiceBox(wxWindow *parent, cType *object, void(cType::*method)(unsigned,const char *), wxArrayString &choices )
  {
    mObject = object;
    mMethod = method;

    mChoice = new wxChoice(parent,wxNewId(),wxDefaultPosition,wxDefaultSize,choices);
    mChoice->Connect(wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&IFXChoiceBox::EventHandler,0,this);
  }

  void EventHandler(wxCommandEvent &event)
  {
    (mObject->*mMethod)(mChoice->GetSelection(),mChoice->GetStringSelection().c_str());
  }

  void UpdateChoices(std::vector<wxString> &choices)
  {
    //Clear old choices
    mChoice->Clear();

    //Add all new choices into menu
    std::vector<wxString>::iterator it = choices.begin();
    while (it != choices.end())
      mChoice->Append(*it++);
  }

//private:
  cType *mObject;
  void (cType::*mMethod)(unsigned,const char *);
  wxChoice *mChoice;
};


//TextEdit
template <typename cType>
class IFXTextEdit : public IFXProperty
{
public:
  IFXTextEdit(wxWindow *parent, const wxString &label, cType *object, void (cType::*method)(const wxString &))
  {
    mObject = object;
    mMethod = method;

    mTextCtrl = new wxTextCtrl(parent,wxNewId(),_T("1.0"),wxDefaultPosition,wxDefaultSize, wxTE_PROCESS_ENTER);
    mTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&IFXTextEdit::EventHandler,0,this);
  }

  void EventHandler(wxCommandEvent &event)
  {
    (mObject->*mMethod)(mTextCtrl->GetValue());
  }

//private:
  cType *mObject;
  void (cType::*mMethod)(const wxString &);
  wxTextCtrl *mTextCtrl;
};

//SpinControl
//SliderBar

//The PropertyPanel holds all the property controls for a given stage
class IFXPropertyPanel : public wxDialog
{
  DECLARE_CLASS( IFXPropertyPanel )
  DECLARE_EVENT_TABLE()

public:
  IFXPropertyPanel();
  virtual ~IFXPropertyPanel();

  //Removes all current properties
  void ClearProperties();

  //Rebuilds the properties panel
  void Create(wxWindow *parent);
  
  //Finalizes the window
  void Finalize();

  //Add a checkbox to the property panel
  template <typename cType>
  IFXCheckBox<cType> * AddCheckBox(const wxString &label, cType *object, void (cType::*method)(bool))
  {
    IFXCheckBox<cType> *checkbox = new IFXCheckBox<cType>(this,label,object,method);
    mBoxSizer->Add(checkbox->mCheckBox,0,wxALL|wxALIGN_LEFT,5);
    mProperties.push_back(checkbox);
    return checkbox;
  }

  //Add a radio box to the property panel
  template <typename cType>
  IFXRadioBox<cType> * AddRadioBox(const wxString &label, wxArrayString &choices, cType *object, void(cType::*method)(unsigned))
  {
    IFXRadioBox<cType> *radio = new IFXRadioBox<cType>(this,label,choices,object,method);
    mBoxSizer->Add(radio->mRadioBox,0,wxALL|wxALIGN_LEFT,5);
    mProperties.push_back(radio);
    return radio;
  }

  //Add a choice box to the property panel
  template <typename cType>
  IFXChoiceBox<cType> * AddChoiceBox(cType *object, void(cType::*method)(unsigned,const char *), wxArrayString &choices)
  {
    IFXChoiceBox<cType> *choice = new IFXChoiceBox<cType>(this,object,method,choices);
    mBoxSizer->Add(choice->mChoice,0,wxALL|wxALIGN_LEFT,5);
    mProperties.push_back(choice);
    return choice;
  }

  //Add a text edit box to the panel
  template <typename cType>
  IFXTextEdit<cType> * AddTextEdit(const wxString &label, cType *object, void (cType::*method)(const wxString &))
  {
    wxBoxSizer *box = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *text = new wxStaticText(this,wxNewId(),label);
    box->Add(text,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    IFXTextEdit<cType> *textCtrl = new IFXTextEdit<cType>(this,label,object,method);
    box->Add(textCtrl->mTextCtrl,0,wxALL|wxALIGN_LEFT,5);
    mBoxSizer->Add(box,0,wxGROW|wxALL,5);
    mProperties.push_back(textCtrl);
    return textCtrl;
  }

private:
  std::vector<IFXProperty *> mProperties;
  wxBoxSizer *mTopSizer;
  wxBoxSizer *mBoxSizer;
  wxBoxSizer *mOkSizer;
};

#endif
