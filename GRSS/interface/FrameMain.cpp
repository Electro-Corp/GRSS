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

#include "FrameMain.h"

GRSSMainFrame::GRSSMainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    generateMenuBar();

    // Create main panel
    mainPanel = new wxPanel(this, wxID_ANY);
    // Create sizer
    wxBoxSizer* hSizer = new wxBoxSizer(wxVERTICAL);
    // Add tool panel
    topPanel = new TopPanel(mainPanel);
    hSizer->Add(topPanel, 0, wxEXPAND | wxALL, 0);

    // Add OpenGL area
    int glArgs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    openGLPanel = new OpenGLPanel(mainPanel, glArgs);
    hSizer->Add(openGLPanel, 1, wxEXPAND);

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
    wxMessageBox("Welcome to GRSS! Still a work-in-progress.", "Welcome", wxOK | wxICON_INFORMATION);
}

void GRSSMainFrame::OnExit(wxCommandEvent& event){
    Close(true);
}

void GRSSMainFrame::OnAbout(wxCommandEvent& event){
    wxMessageBox("GRSS, (c) 2026 Electro-Corp", "About GRSS", wxOK | wxICON_INFORMATION);
}

GRSSMainFrame::~GRSSMainFrame(){
    delete topPanel;
    delete mainPanel;
}