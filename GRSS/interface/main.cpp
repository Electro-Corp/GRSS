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

#include "FrameMain.h"

// Main GRSS wxWidgets App
class GRSSApp : public wxApp {
    public:
        virtual bool OnInit() {
            GRSSMainFrame* mainFrame = new GRSSMainFrame("General Relativity Simulation Software (GRSS)");
            mainFrame->Show();
            mainFrame->Maximize(true);
            return true;
        }
};


int main(int argc, char* argv[]) {
    wxApp::SetInstance(new GRSSApp);
    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();
    
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();

    return 0;
}