/***************************************************************
 * Name:      CompAffinMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Miguel Valbuena ()
 * Created:   2016-09-26
 * Copyright: Miguel Valbuena ()
 * License:
 **************************************************************/

#include "CompAffinMain.h"
#include "CompAffin.h"
#include <wx/msgdlg.h>
#include <thread>
#include <fstream>


//(*InternalHeaders(CompAffinFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

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

//(*IdInit(CompAffinFrame)
const long CompAffinFrame::ID_BUTTONCOMP = wxNewId();
const long CompAffinFrame::ID_BUTTONCLEAR = wxNewId();
const long CompAffinFrame::ID_PANEL1 = wxNewId();
const long CompAffinFrame::ID_TEXTCTRL1 = wxNewId();
const long CompAffinFrame::ID_TEXTCTRL2 = wxNewId();
const long CompAffinFrame::ID_BUTTONCLEAR1 = wxNewId();
const long CompAffinFrame::ID_PANEL2 = wxNewId();
const long CompAffinFrame::ID_BUTTONCLEAR2 = wxNewId();
const long CompAffinFrame::ID_PANEL3 = wxNewId();
const long CompAffinFrame::ID_TEXTCTRL3 = wxNewId();
const long CompAffinFrame::ID_TEXTCTRL4 = wxNewId();
const long CompAffinFrame::ID_TEXTCTRL5 = wxNewId();
const long CompAffinFrame::idMenuQuit = wxNewId();
const long CompAffinFrame::ID_MENU_INCREASE = wxNewId();
const long CompAffinFrame::ID_MENU_DECREASE = wxNewId();
const long CompAffinFrame::idMenuAbout = wxNewId();
const long CompAffinFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CompAffinFrame,wxFrame)
    //(*EventTable(CompAffinFrame)
    //*)
END_EVENT_TABLE()

CompAffinFrame::CompAffinFrame(wxWindow* parent,wxWindowID id)
{
    //*Initialize(CompAffinFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("CompAffin"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    if (val::FileExists(iconpath)) {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(iconpath)));
    	SetIcon(FrameIcon);
    }
    else if (val::FileExists(alticonpath)) {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(alticonpath)));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    CompButton = new wxButton(Panel1, ID_BUTTONCOMP, _("Compute"), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCOMP"));
    CompButton->SetToolTip(_("Ctrl-L"));
    ClearButton = new wxButton(Panel1, ID_BUTTONCLEAR, _("Clear All"), wxPoint(96,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCLEAR"));
    ClearButton->SetToolTip(_("Ctrl-D"));
    BoxSizer2->Add(Panel1, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 1);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    I1_TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(194,89), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    I1_TextCtrl->SetToolTip(_("Eintrag Raum 1"));
    BoxSizer7->Add(I1_TextCtrl, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer7, 1, wxALL|wxEXPAND, 1);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    I2_TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    I2_TextCtrl->SetToolTip(_("Eintrag Raum 2"));
    BoxSizer8->Add(I2_TextCtrl, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer8, 1, wxALL|wxEXPAND, 1);
    BoxSizer1->Add(BoxSizer3, 0, wxALL|wxEXPAND, 1);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Clear1Button = new wxButton(Panel2, ID_BUTTONCLEAR1, _("Clear"), wxPoint(16,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCLEAR1"));
    Clear1Button->SetToolTip(_("Ctrl-1"));
    BoxSizer9->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer9, 1, wxALL|wxEXPAND, 1);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Clear2Button = new wxButton(Panel3, ID_BUTTONCLEAR2, _("Clear"), wxPoint(16,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCLEAR2"));
    Clear2Button->SetToolTip(_("Ctrl-2"));
    BoxSizer10->Add(Panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer10, 1, wxALL|wxEXPAND, 1);
    BoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND, 1);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    O1_TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    O1_TextCtrl->SetToolTip(_("Berechnungen zu Raum 1"));
    BoxSizer11->Add(O1_TextCtrl, 1, wxALL|wxEXPAND, 5);
    BoxSizer5->Add(BoxSizer11, 1, wxALL|wxEXPAND, 1);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    O2_TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    O2_TextCtrl->SetToolTip(_("Berechnungen zu Raum 2"));
    BoxSizer12->Add(O2_TextCtrl, 1, wxALL|wxEXPAND, 5);
    BoxSizer5->Add(BoxSizer12, 1, wxALL|wxEXPAND, 1);
    BoxSizer1->Add(BoxSizer5, 1, wxALL|wxEXPAND, 1);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    O_TextCtrl = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(500,150), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    O_TextCtrl->SetToolTip(_("Berechungen zur gegenseitiger Lage"));
    BoxSizer6->Add(O_TextCtrl, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer6, 1, wxALL|wxEXPAND, 1);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, ID_MENU_INCREASE, _("Increase Font Size\tCtrl-+"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu3, ID_MENU_DECREASE, _("Decrease Font Size\tCtrl--"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem4);
    MenuBar1->Append(Menu3, _("Settings"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTONCOMP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CompAffinFrame::OnCompButtonClick);
    Connect(ID_BUTTONCLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CompAffinFrame::OnClearButtonClick);
    Connect(ID_BUTTONCLEAR1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CompAffinFrame::OnClearButtonClick);
    Connect(ID_BUTTONCLEAR2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CompAffinFrame::OnClearButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CompAffinFrame::OnQuit);
    Connect(ID_MENU_INCREASE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CompAffinFrame::OnMenuIncrease);
    Connect(ID_MENU_DECREASE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CompAffinFrame::OnMenuIncrease);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CompAffinFrame::OnAbout);
    //*)

    val::Error::errormessage=&Error;
    computeready=1;

    wxAcceleratorEntry entries[5];
    entries[0].Set(wxACCEL_CTRL, (int) 'L',ID_BUTTONCOMP);
    entries[1].Set(wxACCEL_CTRL, (int) 'D',ID_BUTTONCLEAR);
    entries[2].Set(wxACCEL_CTRL, (int) '1',ID_BUTTONCLEAR1);
    entries[3].Set(wxACCEL_CTRL, (int) '2',ID_BUTTONCLEAR2);
    entries[4].Set(wxACCEL_CTRL,WXK_RETURN,ID_BUTTONCOMP);
    //entries[4].Set(wxACCEL_CTRL, (int) '+',ID_MENU_INCREASE);
    //entries[5].Set(wxACCEL_CTRL, (int) '-',ID_MENU_DECREASE);
    wxAcceleratorTable accel(5,entries);
    SetAcceleratorTable(accel);

    Bind(MY_EVENT,&CompAffinFrame::OnOutputEvent,this,IdOutput);
    Bind(MY_EVENT,&CompAffinFrame::OnButtonOKEvent,this,IdButtonOK);
    Bind(MY_EVENT,&CompAffinFrame::OnErrorEvent,this,IdError);
    GetSizeSettings();
    if (xsize!=-1) {
        SetClientSize(wxSize(xsize,ysize));
        Move(wxPoint(xpos,ypos));
        wxFont myfont(I1_TextCtrl->GetFont());
        myfont.SetPointSize(fontsize);
        I1_TextCtrl->SetFont(myfont);
        I2_TextCtrl->SetFont(myfont);
        O1_TextCtrl->SetFont(myfont);
        O2_TextCtrl->SetFont(myfont);
        O_TextCtrl->SetFont(myfont);
    }
    I1_TextCtrl->SetFocus();
}

CompAffinFrame::~CompAffinFrame()
{
    using namespace std;
    //std::ofstream file(val::GetExeDir()+filesep+"settings.txt",ios::out | ios::trunc);
    std::ofstream file(settingsfile,ios::out | ios::trunc);
    if (file) {
        wxSize MySize=GetClientSize();
        wxPoint MyPoint=GetPosition();
        file<<MyPoint.x<<endl;
        file<<MyPoint.y<<endl;
        file<<MySize.x<<endl;
        file<<MySize.y<<endl;
        file<<I1_TextCtrl->GetFont().GetPointSize();
        file.close();
    }
    //(*Destroy(CompAffinFrame)
    //*)
}

void CompAffinFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CompAffinFrame::GetSizeSettings()
{
    //std::ifstream file(val::GetExeDir()+filesep+"settings.txt",std::ios::in);
    std::ifstream file(settingsfile,std::ios::in);
    if (!file) {
        if (!val::DirExists(valdir)) {
            if (!val::CreateDir(valdir)) wxMessageBox("Cannot Create\n" + valdir);
        }
        if (!val::DirExists(settingsdir)) {
             if (!val::CreateDir(settingsdir)) wxMessageBox("Cannot Create\n" + settingsdir);
        }
        return;
    }
    file>>xpos>>ypos>>xsize>>ysize>>fontsize;
    file.close();
}


void CompAffinFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    //wxMessageBox(msg, _("Welcome to..."));
    wxMessageBox("programmed by Miguel Valbuena","Comparing two affine spaces");
}

void CompAffinFrame::OnClearButtonClick(wxCommandEvent& event)
{
    long id=event.GetId();
    if (id==ID_BUTTONCLEAR1) {
        I1_TextCtrl->Clear();
        O1_TextCtrl->Clear();
        //wxMessageBox("Clear All");
    }
    else if (id==ID_BUTTONCLEAR2) {
        //wxMessageBox("Clear 1");
        I2_TextCtrl->Clear();
        O2_TextCtrl->Clear();
    }
    else if (id==ID_BUTTONCLEAR) {
        I1_TextCtrl->Clear();
        O1_TextCtrl->Clear();
        I2_TextCtrl->Clear();
        O2_TextCtrl->Clear();
        O_TextCtrl->Clear();
        //wxMessageBox("Clear 2");
    }
}

void CompAffinFrame::OnCompButtonClick(wxCommandEvent& event)
{
    //wxMessageBox("Compute");
    if (!computeready) return;
    MyFrame=this;
    CompButton->Disable();
    Input_1=I1_TextCtrl->GetValue();
    Input_2=I2_TextCtrl->GetValue();
    O1_TextCtrl->Clear();
    O2_TextCtrl->Clear();
    O_TextCtrl->Clear();
    std::thread t(CompAffinMain,std::ref(Input_1),std::ref(Input_2));
    t.detach();
}

void CompAffinFrame::OnMenuIncrease(wxCommandEvent& event)
{
    long id=event.GetId();
    wxFont myfont(I1_TextCtrl->GetFont());
    int mysize=myfont.GetPointSize();

    if (id==ID_MENU_INCREASE) mysize+=1;
    else mysize-=1;

    if (mysize>20) mysize=20;
    if (mysize<9) mysize=9;
    myfont.SetPointSize(mysize);
    I1_TextCtrl->SetFont(myfont);
    I2_TextCtrl->SetFont(myfont);
    O_TextCtrl->SetFont(myfont);
    O1_TextCtrl->SetFont(myfont);
    O2_TextCtrl->SetFont(myfont);
    I1_TextCtrl->Refresh();
    I2_TextCtrl->Refresh();
    O_TextCtrl->Refresh();
    O1_TextCtrl->Refresh();
    O2_TextCtrl->Refresh();
}


void CompAffinFrame::OnOutputEvent(MyThreadEvent& event)
{
    int Output=event.GetOutput();

    if (Output==1) {
        //O1_TextCtrl->Clear();
        O1_TextCtrl->WriteText(event.GetMessage());
    }
    else if (Output==2) {
        //O2_TextCtrl->Clear();
        O2_TextCtrl->WriteText(event.GetMessage());
    }
    else {
        //O_TextCtrl->Clear();
        O_TextCtrl->WriteText(event.GetMessage());
    }
}


void CompAffinFrame::OnButtonOKEvent(MyThreadEvent& event)
{
    O1_TextCtrl->SetInsertionPoint(0);
    O2_TextCtrl->SetInsertionPoint(0);
    O_TextCtrl->SetInsertionPoint(0);
    CompButton->Enable();
    computeready=1;
}


void CompAffinFrame::OnErrorEvent(MyThreadEvent& event)
{
    wxMessageBox(event.GetMessage(),"Fatal Error!",wxICON_ERROR);
    errorcomputed=1;
}

