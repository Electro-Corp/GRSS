/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] EnvironmentPage.h
 * [DESCRIPTION] wxPanel defintion for the Environment page of the tools UI
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/notebook.h>

#include <interface/Backend.h>
#include <physics/include/Mass.h>
#include <rendering/include/Object.h>

class EnvironmentPage : public wxPanel{
    public:
        EnvironmentPage(wxNotebook* parent);

    private:
        // Buttons
        wxButton* addMass_button;

        // Button IDs
        enum {
            ID_ADD_MASS = 0
        };

        // Button funcs
        void envPage_addMass(wxCommandEvent& event);
};