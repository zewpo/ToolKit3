/***************************************************************
 * Name:      ToolKit3App.cpp
 * Purpose:   Code for Application Class
 * Author:    Christopher Plewright (chris@createng.com)
 * Created:   2016-10-08
 * Copyright: Christopher Plewright (www.createng.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ToolKit3App.h"

//(*AppHeaders
#include "ToolKit3Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ToolKit3App);

bool ToolKit3App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ToolKit3Frame* Frame = new ToolKit3Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    return wxsOK;

}
