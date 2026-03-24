/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] SideBar.cpp
 * [DESCRIPTION] Implementation for the side panel
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/SideBar.h>

SideBar::SideBar(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
    m_parent = parent;

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create list box
    objectListBox = new wxListBox(this, ID_OBJECT_LIST_BOX);
    sizer->Add(objectListBox, 1, wxEXPAND | wxALL);

    this->SetSizer(sizer);

    // Setup triggers
    connector->addConnection<SideBar>(*this, &SideBar::updateList, TRIGGER_MASSES_MODIFIED);
}

void SideBar::updateList() {
    objectListBox->Clear();
    // Get objects
    // TODO: getNumberOfObjects just returns an int, we need to be able to know more information 
    //       about the object... but i couldnt get a clean way with the unique_ptr. The only way
    //       i got it to work was with std::unique_ptr::get but that defeats the purpose of the unique_ptr
    for(int i = 0; i < universe->getNumberOfObjects(); i++){
        objectListBox->Append(wxT("Mass"));
    }
}