/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] RenderingPage.cpp
 * [DESCRIPTION] Implementation for the Rendering page of the tools UI
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/RenderingPage.h>
#include <interface/AddMassDialog.h>
#include <common/Universe.h>

RenderingPage::RenderingPage(wxNotebook* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
    // Create sizer
    wxBoxSizer* renSizer = new wxBoxSizer(wxHORIZONTAL);

    // Add sizer
    this->SetSizer(renSizer);
}