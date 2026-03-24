/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] AddMassDialog.h
 * [DESCRIPTION] Dialog for setting properties when adding a new mass
 *
 * (c) 2026 Electro-Corp, Androo, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <wx/wx.h>

#include <common/Vector.h>

class AddMassDialog : public wxDialog {
public:
    AddMassDialog(wxWindow* parent);

    // Getters for the properties
    Vector3 getPosition();
    double getMass();
    double getRadius();

private:
    wxTextCtrl* xInput;
    wxTextCtrl* yInput;
    wxTextCtrl* zInput;
    wxTextCtrl* massInput;
    wxTextCtrl* radiusInput;

    void addPropertyField(wxSizer* sizer, const wxString& label, wxTextCtrl** ctrl, const wxString& defaultValue);
};
