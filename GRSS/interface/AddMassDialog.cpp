/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] AddMassDialog.cpp
 * [DESCRIPTION] Implementation of the AddMassDialog
 *
 * (c) 2026 Electro-Corp, Androo, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/AddMassDialog.h>

AddMassDialog::AddMassDialog(wxWindow* parent) 
    : wxDialog(parent, wxID_ANY, "Add New Mass", wxDefaultPosition, wxDefaultSize) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);

    addPropertyField(gridSizer, "Position X:", &xInput, "0.0");
    addPropertyField(gridSizer, "Position Y:", &yInput, "0.0");
    addPropertyField(gridSizer, "Position Z:", &zInput, "-0.6");
    addPropertyField(gridSizer, "Mass (kg):", &massInput, "1.0");
    addPropertyField(gridSizer, "Radius (m):", &radiusInput, "0.2");

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 15);

    // Standard OK/Cancel buttons
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    SetSizerAndFit(mainSizer);
}

void AddMassDialog::addPropertyField(wxSizer* sizer, const wxString& label, wxTextCtrl** ctrl, const wxString& defaultValue) {
    sizer->Add(new wxStaticText(this, wxID_ANY, label), 0, wxALIGN_CENTER_VERTICAL);
    *ctrl = new wxTextCtrl(this, wxID_ANY, defaultValue);
    sizer->Add(*ctrl, 1, wxEXPAND);
}

Vector3 AddMassDialog::getPosition() {
    double x, y, z;
    xInput->GetValue().ToDouble(&x);
    yInput->GetValue().ToDouble(&y);
    zInput->GetValue().ToDouble(&z);
    return Vector3(x, y, z);
}

double AddMassDialog::getMass() {
    double val;
    massInput->GetValue().ToDouble(&val);
    return val;
}

double AddMassDialog::getRadius() {
    double val;
    radiusInput->GetValue().ToDouble(&val);
    return val;
}
