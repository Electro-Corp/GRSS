/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] FrameMain.cpp 
 * [DESCRIPTION] Implementation for the main window of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/

#include <interface/FrameMain.h>

GRSSMainFrame::GRSSMainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    generateMenuBar();

    // Create main panel
    mainPanel = new wxPanel(this, wxID_ANY);
    // Create sizer
    wxBoxSizer* hSizer = new wxBoxSizer(wxVERTICAL);
    // Add tool panel
    topPanel = new TopPanel(mainPanel);
    hSizer->Add(topPanel, 0, wxEXPAND | wxALL, 0);

    // Bottom sizer
    wxBoxSizer* bottom = new wxBoxSizer(wxHORIZONTAL); 

    // Add OpenGL area
    int glArgs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    openGLPanel = new OpenGLPanel(mainPanel, glArgs);
    bottom->Add(openGLPanel, 4, wxEXPAND);

    // Side bar
    sideBar = new SideBar(mainPanel);
    bottom->Add(sideBar, 1, wxEXPAND);

    hSizer->Add(bottom, 1, wxEXPAND);

    // Create render time
    timer = new RenderTimer(openGLPanel, this);
    timer->start();

    // FPS
    lastTime = wxGetLocalTimeMillis().GetValue();
    frameCount = 0;

    CreateStatusBar(); 
    SetStatusText("GRSS loaded.");

    mainPanel->SetSizer(hSizer);

    this->Center();
}

// Generate top menu bar
void GRSSMainFrame::generateMenuBar(){
    // File
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_Welcome, "&Welcome...\tCtrl-H", "Message");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    // Help
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);

    // Menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &GRSSMainFrame::OnWelcome, this, ID_Welcome);
    Bind(wxEVT_MENU, &GRSSMainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &GRSSMainFrame::OnExit, this, wxID_EXIT);
}

void GRSSMainFrame::OnWelcome(wxCommandEvent& event){
    wxMessageBox("Welcome.", "Welcome", wxOK | wxICON_INFORMATION);
}

void GRSSMainFrame::OnExit(wxCommandEvent& event){
    Close(true);
}

void GRSSMainFrame::OnAbout(wxCommandEvent& event){
    wxAboutDialogInfo info;
    info.SetName(_("GRSS"));
    info.SetVersion(_("0.0.1 Alpha"));
    info.SetDescription(_("Simulate the universe, somewhat accurately."));
    info.SetCopyright("(C) 2026 Electro-Corp, Androo");
 
    wxAboutBox(info);
}

GRSSMainFrame::~GRSSMainFrame(){
    timer->Stop();
    delete topPanel;
    delete mainPanel;
}

RenderTimer::RenderTimer(OpenGLPanel* panel, GRSSMainFrame* frame) : wxTimer() {
    this->panel = panel;
    this->frame = frame;
}

void RenderTimer::Notify(){
    if(panel)
        panel->Refresh();

    if(frame){
        frame->frameCount++;
        long currentTime = wxGetLocalTimeMillis().GetValue();
        if(currentTime - frame->lastTime >= 1000){
            double fps = (double)frame->frameCount / ((double)(currentTime - frame->lastTime) / 1000.0);
            frame->SetStatusText(wxString::Format("FPS: %.2f", fps));
            frame->frameCount = 0;
            frame->lastTime = currentTime;
        }
    }
}

void RenderTimer::start(){
    wxTimer::Start(10);
}