/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Rendering.cpp  
 * [DESCRIPTION] This file contains the implementaion for the rendering engine of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#include <include/Rendering.h>

namespace Rendering{

    RenderingEngine::RenderingEngine(){
        // Setup rendering
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_COLOR_MATERIAL);
    }

    // Setup viewport
    void RenderingEngine::setupViewport(int tlX, int tlY, int brX, int brY) {
        // Setup viewport
        glViewport(tlX, brY, brX - tlX, brY - tlY);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float ratio = ((float)(brX - tlX) / (float)(brY - tlY));
        gluPerspective(45, ratio, 0.1, 200); // View angle, ratio, Clip near, Clip far
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    // Add an object to the scene
    void RenderingEngine::addObject(std::unique_ptr<Object> object) {
        this->objects.push_back(std::move(object));
    }

    void RenderingEngine::tick(){
        glClearColor(0.0, 0.06, 0.25, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        // Render each object
        for(auto& object: this->objects){
            object->render();
        }
        // Flush
        glFlush();
    }

} // RENDERING