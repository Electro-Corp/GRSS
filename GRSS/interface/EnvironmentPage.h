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

#include <common/Connections.h>
#include <common/Universe.h>

class EnvironmentPage : public wxPanel{
    public:
        EnvironmentPage(wxNotebook* parent);

    private:
        // Buttons
        wxButton* addMass_button;
        wxButton* deleteMass_button;
        wxButton* convertMass_button;
        // Tick options
        wxButton* tick_button;
        wxSlider* tick_rate;

        // Button IDs
        enum {
            ID_ADD_MASS = 0,
            ID_DELETE_MASS = 1,
            ID_CONVERT_MASS = 2,
            ID_TICK_PHYSICS = 3,
            ID_TICK_RATE = 4
        };

        // Button funcs
        void envPage_addMass(wxCommandEvent& event);
        void envPage_deleteMass(wxCommandEvent& event);
        void envPage_convertMass(wxCommandEvent& event);

        void envPage_physicsTick(wxCommandEvent& event);
};