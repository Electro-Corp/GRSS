/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] OpenGLPanel.cpp
 * [DESCRIPTION] Implementation of wxWidgets-side OpenGL rendering. Main render is actually done in rendering library.
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/OpenGLPanel.h>
#include <common/Universe.h>

// Delcare event table
BEGIN_EVENT_TABLE(OpenGLPanel, wxGLCanvas)
    EVT_PAINT(OpenGLPanel::render)
    EVT_SIZE(OpenGLPanel::resized)

    EVT_MOTION(OpenGLPanel::mouseMoved)
    EVT_LEFT_DOWN(OpenGLPanel::mouseDown)
    EVT_LEFT_UP(OpenGLPanel::mouseReleased)
    EVT_RIGHT_DOWN(OpenGLPanel::rightClick)
    EVT_MOUSEWHEEL(OpenGLPanel::mouseWheelMoved)
    EVT_LEAVE_WINDOW(OpenGLPanel::mouseLeftWindow)

    EVT_KEY_DOWN(OpenGLPanel::keyPressed)
    EVT_KEY_UP(OpenGLPanel::keyReleased)
END_EVENT_TABLE()

OpenGLPanel::OpenGLPanel(wxWindow* parent, int* args) : wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE){
    context = new wxGLContext(this);

    universe->setupUniverseViewport(0, 0, getWidth(), getHeight());
}

// Getters
int OpenGLPanel::getWidth(){
    return GetSize().x;
}

int OpenGLPanel::getHeight(){
    return GetSize().y;
}

// Render
void OpenGLPanel::render(wxPaintEvent& event){
    // Are we showing?
    if(!IsShown()) return; // no

    wxGLCanvas::SetCurrent(*context);
    wxPaintDC(this);
    
    if(refreshSize){
        universe->setupUniverseViewport(0, 0, getWidth(), getHeight());
        refreshSize = false; // Set this whenever we need to
    }

    // Render commands
    universe->updateRenderer();

    SwapBuffers();
}

// Refresh our gl context
void OpenGLPanel::resized(wxSizeEvent& evt){
    refreshSize = true;
    // Refresh
    Refresh();
}

// Various input events

void OpenGLPanel::mouseMoved(wxMouseEvent& event){

}

void OpenGLPanel::mouseDown(wxMouseEvent& event){

}

void OpenGLPanel::mouseWheelMoved(wxMouseEvent& event){

}

void OpenGLPanel::mouseReleased(wxMouseEvent& event){

}

void OpenGLPanel::rightClick(wxMouseEvent& event){

}

void OpenGLPanel::mouseLeftWindow(wxMouseEvent& event){

}

void OpenGLPanel::keyPressed(wxKeyEvent& event){

}

void OpenGLPanel::keyReleased(wxKeyEvent& event){

}

// Delete
OpenGLPanel::~OpenGLPanel(){
    // Clean up
    delete context;
}