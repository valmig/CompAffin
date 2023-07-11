/***************************************************************
 * Name:      CompAffinMain.h
 * Purpose:   Defines Application Frame
 * Author:    Miguel Valbuena ()
 * Created:   2016-09-26
 * Copyright: Miguel Valbuena ()
 * License:
 **************************************************************/

#ifndef COMPAFFINMAIN_H
#define COMPAFFINMAIN_H

//(*Headers(CompAffinFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)


class MyThreadEvent;


class CompAffinFrame: public wxFrame
{
    public:

        CompAffinFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CompAffinFrame();

    private:

        //(*Handlers(CompAffinFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClearButtonClick(wxCommandEvent& event);
        void OnCompButtonClick(wxCommandEvent& event);
        void OnMenuIncrease(wxCommandEvent& event);
        //*)

        //(*Identifiers(CompAffinFrame)
        static const long ID_BUTTONCOMP;
        static const long ID_BUTTONCLEAR;
        static const long ID_PANEL1;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTONCLEAR1;
        static const long ID_PANEL2;
        static const long ID_BUTTONCLEAR2;
        static const long ID_PANEL3;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_TEXTCTRL5;
        static const long idMenuQuit;
        static const long ID_MENU_INCREASE;
        static const long ID_MENU_DECREASE;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(CompAffinFrame)
        wxButton* Clear1Button;
        wxButton* Clear2Button;
        wxButton* ClearButton;
        wxButton* CompButton;
        wxMenu* Menu3;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxStatusBar* StatusBar1;
        wxTextCtrl* I1_TextCtrl;
        wxTextCtrl* I2_TextCtrl;
        wxTextCtrl* O1_TextCtrl;
        wxTextCtrl* O2_TextCtrl;
        wxTextCtrl* O_TextCtrl;
        //*)

        int computeready,xsize=-1,ysize=-1,xpos=-1,ypos=-1,fontsize=-1;
        void GetSizeSettings();
        void OnOutputEvent(MyThreadEvent& event);
        void OnButtonOKEvent(MyThreadEvent& event);
        void OnErrorEvent(MyThreadEvent& event);


        DECLARE_EVENT_TABLE()
};

#endif // COMPAFFINMAIN_H
