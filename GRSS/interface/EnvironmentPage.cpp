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
#include "EnvironmentPage.h"
#include <common/Universe.h>

EnvironmentPage::EnvironmentPage(wxNotebook* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN){
    // Create buttons
    addMass_button = new wxButton(this, ID_ADD_MASS, wxT("Add Mass"), wxPoint(10, 20), wxSize(100, 80));


    // Connect buttons
    Connect(ID_ADD_MASS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EnvironmentPage::envPage_addMass));
}


//
// Button funcs
//

// Add a mass to the physics and rendering engine
void EnvironmentPage::envPage_addMass(wxCommandEvent& event){
    universe->addPlanet(Vector3(0, 0, 0), 1.0, 1.0);
}
