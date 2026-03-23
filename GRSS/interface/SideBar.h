/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] SideBar.h
 * [DESCRIPTION] Side panel next to gl view for list of objects and properties
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <wx/wx.h>
#include <wx/panel.h>

#include <common/Universe.h>

class SideBar : public wxPanel {
public:
    SideBar(wxPanel* parent);

    // Update the object list
    void updateList();
private:
    // Enum of IDs
    enum {
        ID_OBJECT_LIST_BOX = 0
    };
    // List box of objects
    wxListBox* objectListBox;
};