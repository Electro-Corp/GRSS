/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Properties.cpp
 * [DESCRIPTION] Implementation for the properties panel
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/PropertiesPanel.h>

PropertiesPanel::PropertiesPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
    m_parent = parent;

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    propertyGrid = new wxPropertyGrid(this, -1, wxDefaultPosition, wxDefaultSize, wxPG_SPLITTER_AUTO_CENTER);
    populatePropertyGrid();
    mainSizer->Add(propertyGrid, 1, wxALL | wxEXPAND);

    // Add triggers
    connector->addConnection<PropertiesPanel>(*this, &PropertiesPanel::updatePropertyGrid, TRIGGER_MASS_SELECTION_CHANGED);
    connector->addConnection<PropertiesPanel>(*this, &PropertiesPanel::updatePropertyGrid, TRIGGER_SELECTED_MASS_MODIFIED);

    SetSizerAndFit(mainSizer);
}

void PropertiesPanel::populatePropertyGrid() {
    // Physics controls
    propertyGrid->Append(new wxPropertyCategory("Position"));
    propPositionX = new wxFloatProperty("Pos_X", wxPG_LABEL, 0);
    propPositionY = new wxFloatProperty("Pos_Y", wxPG_LABEL, 0);
    propPositionZ = new wxFloatProperty("Pos_Z", wxPG_LABEL, 0);
    propertyGrid->Append(propPositionX);
    propertyGrid->Append(propPositionY);
    propertyGrid->Append(propPositionZ);
    // Linear Velocity
    propertyGrid->Append(new wxPropertyCategory("Linear Velocity"));
    propVelocityX = new wxFloatProperty("LinV_X", wxPG_LABEL, 0);
    propVelocityY = new wxFloatProperty("LinV_Y", wxPG_LABEL, 0);
    propVelocityZ = new wxFloatProperty("LinV_Z", wxPG_LABEL, 0);
    propertyGrid->Append(propVelocityX);
    propertyGrid->Append(propVelocityY);
    propertyGrid->Append(propVelocityZ);
    // Angular Velocity
    propertyGrid->Append(new wxPropertyCategory("Angular Velocity"));
    propAngularVelocityX = new wxFloatProperty("AngV_X", wxPG_LABEL, 0);
    propAngularVelocityY = new wxFloatProperty("AngV_Y", wxPG_LABEL, 0);
    propAngularVelocityZ = new wxFloatProperty("AngV_Z", wxPG_LABEL, 0);
    propertyGrid->Append(propAngularVelocityX);
    propertyGrid->Append(propAngularVelocityY);
    propertyGrid->Append(propAngularVelocityZ);
    // Physical properties
    propertyGrid->Append(new wxPropertyCategory("Physical Properties"));
    propMass = new wxFloatProperty("Mass", wxPG_LABEL, 0);
    propRadius = new wxFloatProperty("Radius", wxPG_LABEL, 0);
    propertyGrid->Append(propMass);
    propertyGrid->Append(propRadius);

    propertyGrid->CenterSplitter();

    // Bind physics controls
    Bind(wxEVT_PG_CHANGED, &PropertiesPanel::OnPropertyGridChanged, this);
}

void PropertiesPanel::OnPropertyGridChanged(wxPropertyGridEvent& event) {
    // Check if the object we're using even exists
    if (selectedObject) {
        wxPGProperty* prop = event.GetProperty();
        // Check against position
        if (prop == propPositionX) onPositionChanged(event.GetPropertyValue().GetDouble(), 0);
        if (prop == propPositionY) onPositionChanged(event.GetPropertyValue().GetDouble(), 1);
        if (prop == propPositionZ) onPositionChanged(event.GetPropertyValue().GetDouble(), 2);
        // Check against linear velocity
        if (prop == propVelocityX) onVelocityChanged(event.GetPropertyValue().GetDouble(), 0);
        if (prop == propVelocityY) onVelocityChanged(event.GetPropertyValue().GetDouble(), 1);
        if (prop == propVelocityZ) onVelocityChanged(event.GetPropertyValue().GetDouble(), 2);
        // Check against angular velocity
        if (prop == propAngularVelocityX) onAngularVelocityChanged(event.GetPropertyValue().GetDouble(), 0);
        if (prop == propAngularVelocityY) onAngularVelocityChanged(event.GetPropertyValue().GetDouble(), 1);
        if (prop == propAngularVelocityZ) onAngularVelocityChanged(event.GetPropertyValue().GetDouble(), 2);
        // Check against physical properties
        if (prop == propMass) onMassChanged(event.GetPropertyValue().GetDouble());
        if (prop == propRadius) onRadiusChanged(event.GetPropertyValue().GetDouble());
    }
}

void PropertiesPanel::updatePropertyGrid() {
    if (selectedObject) {
        // Update positions
        propPositionX->SetValue(selectedObject->mass->position.x);
        propPositionY->SetValue(selectedObject->mass->position.y);
        propPositionZ->SetValue(selectedObject->mass->position.z);
        // Update linear velocity
        propVelocityX->SetValue(selectedObject->mass->linearVelocity.x);
        propVelocityY->SetValue(selectedObject->mass->linearVelocity.y);
        propVelocityZ->SetValue(selectedObject->mass->linearVelocity.z);
        // Update angular velocity
        propAngularVelocityX->SetValue(selectedObject->mass->angularVelocity.x);
        propAngularVelocityY->SetValue(selectedObject->mass->angularVelocity.y);
        propAngularVelocityZ->SetValue(selectedObject->mass->angularVelocity.z);
        // Update physical properties
        propMass->SetValue(selectedObject->mass->mass);
        propRadius->SetValue(selectedObject->mass->radius);
    }
}

void PropertiesPanel::onPositionChanged(double val, int pos) {
    if (selectedObject) {
        switch (pos) {
        case 0:
            selectedObject->mass->position.x = val;
            break;
        case 1:
            selectedObject->mass->position.y = val;
            break;
        case 2:
            selectedObject->mass->position.z = val;
            break;
        }
    }
}

void PropertiesPanel::onVelocityChanged(double val, int pos){
    if (selectedObject) {
        switch (pos) {
        case 0:
            selectedObject->mass->linearVelocity.x = val;
            break;
        case 1:
            selectedObject->mass->linearVelocity.y = val;
            break;
        case 2:
            selectedObject->mass->linearVelocity.z = val;
            break;
        }
    }
}

void PropertiesPanel::onAngularVelocityChanged(double val, int pos){
    if (selectedObject) {
        switch (pos) {
        case 0:
            selectedObject->mass->angularVelocity.x = val;
            break;
        case 1:
            selectedObject->mass->angularVelocity.y = val;
            break;
        case 2:
            selectedObject->mass->angularVelocity.z = val;
            break;
        }
    }
}

void PropertiesPanel::onMassChanged(double mass) {
    if (selectedObject) {
        selectedObject->mass->mass = mass;
    }
}

void PropertiesPanel::onRadiusChanged(double radius) {
    if (selectedObject) {
        selectedObject->mass->radius = radius;
    }
}