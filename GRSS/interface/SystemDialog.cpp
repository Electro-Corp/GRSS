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

    // Notebook to hold both OpenCL and Rendering options
    wxNotebook* optionsNotebook = new wxNotebook(this, wxID_ANY);

    // Create OpenCL devices dataview 
    openCLDevicesList = new wxDataViewListCtrl(optionsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES | wxDV_VERT_RULES);
    // Columns
    openCLDevicesList->AppendTextColumn("Vendor", wxDATAVIEW_CELL_INERT, 150);
    openCLDevicesList->AppendTextColumn("Device", wxDATAVIEW_CELL_INERT, 150);
    openCLDevicesList->AppendTextColumn("Memory (MB)", wxDATAVIEW_CELL_INERT, 150);
    // Device list
    std::vector<Physics::CL_ComputeDevice> openCLDevices = universe->getPhysicsEngineInstance()->getOpenCLDevices();
    // Actual list for wx
    wxVector<wxVariant> devList;
    for (Physics::CL_ComputeDevice& dev : openCLDevices) {
        devList.push_back(dev.vendor);
        devList.push_back(dev.name);
        devList.push_back(std::to_string(dev.memory / 1048576));
        devList.push_back(true);
    }
    openCLDevicesList->AppendItem(devList);

    optionsNotebook->AddPage(openCLDevicesList, L"OpenCL Devices");
    mainSizer->Add(optionsNotebook, 5, wxEXPAND | wxALL, 5);

    // Ok button
    wxSizer* buttonSizer = CreateButtonSizer(wxOK);
    mainSizer->Add(buttonSizer, 1, wxALIGN_CENTER | wxBOTTOM, 10);

    SetSizer(mainSizer);
}