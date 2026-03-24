/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] EnviromentPage.cpp
 * [DESCRIPTION] Implementation for the Environment page of the tools UI
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/EnvironmentPage.h>
#include <interface/AddMassDialog.h>
#include <common/Universe.h>

EnvironmentPage::EnvironmentPage(wxNotebook* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN){
    // Create sizer
    wxBoxSizer* envSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* tickOptions = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* lButtons = new wxBoxSizer(wxHORIZONTAL);
    // Create buttons
    addMass_button = new wxButton(this, ID_ADD_MASS, wxT("Add Mass"));
    deleteMass_button = new wxButton(this, ID_DELETE_MASS, wxT("Delete Mass"));
    convertMass_button = new wxButton(this, ID_CONVERT_MASS, wxT("Convert Mass"));
    tick_button = new wxButton(this, ID_TICK_PHYSICS, wxT("Tick"));
    // Slider for the tick rate
    tick_rate = new wxSlider(this, ID_TICK_RATE, 30, 1, 100, wxDefaultPosition, wxSize(100, -1), wxSL_AUTOTICKS | wxSL_MIN_MAX_LABELS | wxSL_VALUE_LABEL);

    // Add buttons 
    lButtons->Add(addMass_button, 0, wxEXPAND | wxALL, 0);
    lButtons->Add(deleteMass_button, 0, wxEXPAND | wxALL, 0);
    lButtons->Add(convertMass_button, 0, wxEXPAND | wxALL, 0);
    tickOptions->Add(tick_button, 0, wxEXPAND | wxALL, 0);
    tickOptions->Add(tick_rate, 0, wxEXPAND | wxALL, 0);

    envSizer->Add(lButtons, 0, wxEXPAND | wxALL, 10);
    envSizer->Add(tickOptions, 0, wxEXPAND | wxALL, 10);

    // Add sizer
    this->SetSizer(envSizer);

    // Connect buttons
    Connect(ID_ADD_MASS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EnvironmentPage::envPage_addMass));
    Connect(ID_DELETE_MASS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EnvironmentPage::envPage_deleteMass));
    Connect(ID_CONVERT_MASS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EnvironmentPage::envPage_convertMass));
    Connect(ID_TICK_PHYSICS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EnvironmentPage::envPage_physicsTick));
}


//
// Button funcs
//

// Add a mass to the physics and rendering engine
void EnvironmentPage::envPage_addMass(wxCommandEvent& event){
    AddMassDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        universe->addPlanet(dialog.getPosition(), dialog.getMass(), dialog.getRadius());
    }
}

void EnvironmentPage::envPage_deleteMass(wxCommandEvent& event){
    
}

void EnvironmentPage::envPage_convertMass(wxCommandEvent& event){

}

void EnvironmentPage::envPage_physicsTick(wxCommandEvent& event){
    universe->tick((double)tick_rate->GetValue() / 100.0);
}