/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] TopPanel.h 
 * [DESCRIPTION] Class for the upper tool panel 
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
#include <wx/textctrl.h>

#include "EnvironmentPage.h"

class TopPanel : public wxPanel{
    public:
        TopPanel(wxPanel* parent);

    private:
        EnvironmentPage* envPage;
        
};