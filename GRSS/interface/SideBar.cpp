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
    objectListBox->Bind(wxEVT_LISTBOX, &SideBar::OnListBoxSelection, this);
    sizer->Add(objectListBox, 1, wxEXPAND | wxALL);
    
    // Create properties panel
    propertiesPanel = new PropertiesPanel(this);
    sizer->Add(propertiesPanel, 1, wxEXPAND);

    this->SetSizer(sizer);

    // Setup triggers
    connector->addConnection<SideBar>(*this, &SideBar::updateList, TRIGGER_MASSES_MODIFIED);
}

void SideBar::updateList() {
    objectListBox->SetSelection(-1);
    objectListBox->Clear();
    // Get objects
    for(int i = 0; i < universe->getNumberOfObjects(); i++){
        objectListBox->Append(std::string{"Mass_"+std::to_string(i)}.c_str());
    }
}

void SideBar::OnListBoxSelection(wxCommandEvent& event) {
    selectedIndex = event.GetSelection();
    selectedObject = universe->getObjectAtIndex(selectedIndex).get();
    // Fire trigger
    connector->trigger(TRIGGER_MASS_SELECTION_CHANGED);
}