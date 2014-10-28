/***************************************************************
 * Name:      IFX_FrameworkApp.h
 * Purpose:   Defines Application Class
 * Author:    Wylder Keane (wylder.keane@gmail.com)
 * Created:   2011-06-23
 * Copyright: Wylder Keane ()
 * License:
 **************************************************************/

#ifndef IFX_FRAMEWORKAPP_H
#define IFX_FRAMEWORKAPP_H

#include <wx/app.h>

class IFXApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // IFX_FRAMEWORKAPP_H
