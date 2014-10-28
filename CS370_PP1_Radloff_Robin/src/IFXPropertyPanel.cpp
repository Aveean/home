#include "IFXPropertyPanel.h"
#include "wx/panel.h"
#include "wx/button.h"

IMPLEMENT_CLASS( IFXPropertyPanel, wxDialog )

BEGIN_EVENT_TABLE( IFXPropertyPanel, wxDialog )
END_EVENT_TABLE()

IFXPropertyPanel::IFXPropertyPanel()
{
}

IFXPropertyPanel::~IFXPropertyPanel()
{
  ClearProperties();
}

void IFXPropertyPanel::ClearProperties()
{
  for (uint i = 0; i < mProperties.size(); ++i)
    delete mProperties[i];
}

void IFXPropertyPanel::Create(wxWindow *parent)
{
  bool flag = wxDialog::Create(parent,wxNewId(),_T("TestCaption"));

  mTopSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(mTopSizer);

  mBoxSizer = new wxBoxSizer(wxVERTICAL);
  mTopSizer->Add(mBoxSizer,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);
}

void IFXPropertyPanel::Finalize()
{
  mOkSizer = new wxBoxSizer(wxHORIZONTAL);
  mBoxSizer->Add(mOkSizer,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);

  wxButton *ok = new wxButton(this, wxID_OK, _T("&Ok"));
  mOkSizer->Add(ok,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

  wxButton *cancel = new wxButton(this,wxID_CANCEL, _T("&Cancel"));
  mOkSizer->Add(cancel,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
}
