/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] AddMassDialog.h
 * [DESCRIPTION] Dialog for setting properties when adding a new mass
 *
 * (c) 2026 Electro-Corp, All rights reserved.
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
