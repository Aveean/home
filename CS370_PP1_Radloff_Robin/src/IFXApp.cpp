/***************************************************************
 * Name:      IFX_FrameworkApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Wylder Keane (wylder.keane@gmail.com)
 * Created:   2011-06-23
 * Copyright: Wylder Keane ()
 * License:
 **************************************************************/

#include "IFXApp.h"

//(*AppHeaders
#include "IFXFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(IFXApp);

bool IFXApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	IFXFrame* Frame = new IFXFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
