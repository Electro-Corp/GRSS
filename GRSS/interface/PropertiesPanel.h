/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Properties.h
 * [DESCRIPTION] Header for the properties panel, where users can modify parameters after mass creation
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>

#include <common/Connections.h>

class PropertiesPanel : public wxPanel {
public:
    PropertiesPanel(wxPanel* parent);

    
private:
    // Property grid
    wxPropertyGrid* propertyGrid;

    // Properties
    wxFloatProperty *propPositionX, *propPositionY, *propPositionZ;
    wxFloatProperty *propMass, *propRadius;

    void populatePropertyGrid();
    void updatePropertyGrid();

    // Handlers for property grid
    void OnPropertyGridChanged(wxPropertyGridEvent& event);
    // Specfics
    // X = 0, Y = 1, Z = 2
    void onPositionChanged(double val, int pos);
    void onMassChanged(double mass);
    void onRadiusChanged(double radius);
};