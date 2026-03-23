/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] TopPanel.cpp
 * [DESCRIPTION] Implementation for the top tools panel
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/TopPanel.h>

TopPanel::TopPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
    m_parent = parent;

    wxNotebook* topNotebook = new wxNotebook(this, wxID_ANY);

    envPage = new EnvironmentPage(topNotebook);
    topNotebook->AddPage(envPage, L"Environment");
    // Temp rendering page
    wxTextCtrl* textCtrl2 = new wxTextCtrl(topNotebook, wxID_ANY, L"Rendering");
    topNotebook->AddPage(textCtrl2, L"Rendering");


    this->SetMinSize(wxSize(-1, 150));

    //Set up the sizer for the panel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(topNotebook, 1, wxEXPAND);
    this->SetSizer(panelSizer);
}