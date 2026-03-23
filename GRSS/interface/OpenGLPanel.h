/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] OpenGLPanel.h
 * [DESCRIPTION] wxWidgets panel for OpenGL rendering. Recives actual draw commands from the rendering library.
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/glcanvas.h>

class OpenGLPanel : public wxGLCanvas {
    public:
        OpenGLPanel(wxWindow* parent, int* args);

        // Resize event
        void resized(wxSizeEvent& evt);

        // Getters
        int getWidth();
        int getHeight();

        // Rendering
        void render(wxPaintEvent& evt);
        void prepare3DViewport(int tlX, int tlY, int brX, int brY);
	    void prepare2DViewport(int tlX, int tlY, int brX, int brY);

        // Various input events
        void mouseMoved(wxMouseEvent& event);
        void mouseDown(wxMouseEvent& event);
        void mouseWheelMoved(wxMouseEvent& event);
        void mouseReleased(wxMouseEvent& event);
        void rightClick(wxMouseEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void keyPressed(wxKeyEvent& event);
        void keyReleased(wxKeyEvent& event);
        
        DECLARE_EVENT_TABLE()

        // Deconstruct
        virtual ~OpenGLPanel();
    private:
        wxGLContext* context;
};