/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] FrameMain.h 
 * [DESCRIPTION] This file contains the main frame class used (in wxWidgets)
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/wxprec.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/timer.h>

#include "TopPanel.h"
#include "OpenGLPanel.h"

// For timing rendering
class RenderTimer : public wxTimer {
    OpenGLPanel* panel;
public:
    RenderTimer(OpenGLPanel* panel);
    void Notify();
    void start();
};

// Main frame of the application
class GRSSMainFrame : public wxFrame {
    public:
        GRSSMainFrame(const wxString& title);
    private:
        // Main panel
        wxPanel* mainPanel;
        // Top tool panel
        TopPanel* topPanel;
        // OpenGL area
        OpenGLPanel* openGLPanel;

        // Timer for frame drawing
        RenderTimer* timer;

        // Generate top menu bar
        void generateMenuBar();

        // Callbacks for menu bar
        void OnWelcome(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        ~GRSSMainFrame();

        enum {
            ID_Welcome = 1
        };
};
