/***************************************************************
 * Name:      CompAffinApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Miguel Valbuena ()
 * Created:   2016-09-26
 * License:   GPL v3.0
 **************************************************************/

#include "CompAffinApp.h"

//(*AppHeaders
#include "CompAffinMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CompAffinApp)

bool CompAffinApp::OnInit()
{
    //(*AppInitialize
    //wxLocale* locale = new wxLocale();
    //locale->Init(wxLANGUAGE_GERMAN, wxLOCALE_LOAD_DEFAULT);
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CompAffinFrame* Frame = new CompAffinFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
