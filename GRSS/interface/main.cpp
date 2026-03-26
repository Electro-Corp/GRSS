/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] main.cpp  
 * [DESCRIPTION] This file contains the main entry point for the User Interface of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/splash.h>

#include <interface/FrameMain.h>
#include <common/Universe.h>
#include <common/aixlog.hpp>

// Main GRSS wxWidgets App
class GRSSApp : public wxApp {
    public:
        virtual bool OnInit() {
            GRSSMainFrame* mainFrame = new GRSSMainFrame("General Relativity Simulation Software (GRSS)");
            // Create splash screen
            wxImage::AddHandler(new wxJPEGHandler);
            wxBitmap splash = wxBitmap();
            splash.LoadFile("assets/Splash.jpg", wxBITMAP_TYPE_JPEG);
            new wxSplashScreen(splash,
                wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
                6000, mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                wxSIMPLE_BORDER | wxSTAY_ON_TOP);

            // Splash
            wxYield();

            // Show application
            mainFrame->Show();
            mainFrame->Maximize(true);
            return true;
        }
};


int main(int argc, char* argv[]) {
    // Create UI
    wxApp::SetInstance(new GRSSApp);
    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();
    
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();

    return 0;
}