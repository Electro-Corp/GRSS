/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] SystemDialog.cpp
 * [DESCRIPTION] Implementation of the SystemDialog
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <interface/SystemDialog.h>


SystemDialog::SystemDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "GRSS Host System Information", wxDefaultPosition, wxDefaultSize) {
    // Create main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Ok button
    wxSizer* buttonSizer = CreateButtonSizer(wxOK);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);
}