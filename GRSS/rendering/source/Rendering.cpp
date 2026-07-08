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
        // Global lighting (basic)
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        // Basic lighting for scene
        GLfloat lightPos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
        GLfloat lightDiff[] = { 0.4f, 0.4f, 0.4f, 1.0f };
        GLfloat lightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat lightSpec[] = { 0.2f, 0.2f, 0.2f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    }

    // Setup viewport
    void RenderingEngine::setupViewport(int tlX, int tlY, int brX, int brY) {
        // Setup viewport
        glViewport(0, 0, brX - tlX, brY - tlY);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float ratio = ((float)(brX - tlX) / (float)(brY - tlY));
        gluPerspective(45, ratio, 0.1, 200); // View angle, ratio, Clip near, Clip far
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Setup camera
        cameraPosition = Vector3(0.0, 0.0, 0.0);
        cameraUP = Vector3(0.0, 1.0, 0.0);
        cameraRIGHT = Vector3(1.0, 0.0, 0.0);
        cameraTarget = Vector3(0.0, 0.0, -0.6); // Default spawn point for objects
    }

    // Add an object to the scene
    void RenderingEngine::addObject(std::shared_ptr<Object> object) {
        this->objects.push_back(std::move(object));
    }

    void RenderingEngine::removeObject(int index){
        this->objects.erase(objects.begin() + index);
    }

    void RenderingEngine::tick(){
        glClearColor(0.03, 0.03, 0.04, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        // Update camera
        gluLookAt(
            cameraPosition.x, cameraPosition.y, cameraPosition.z,
            cameraTarget.x, cameraTarget.y, cameraTarget.z,
            cameraUP.x, cameraUP.y, cameraUP.z
        );
        // Render each object
        for(auto& object: this->objects){
            object->render();
        }
        // Flush
        glFlush();
    }

    // Pan the view
    void RenderingEngine::pan(double deltaX, double deltaY) {
        cameraRIGHT = Vector3::CrossProduct(cameraTarget, cameraUP);
        
        cameraPosition = cameraPosition + ((cameraRIGHT * (-deltaX / 1000)) + (cameraUP * (deltaY / 1000)));
        cameraTarget = cameraTarget + ((cameraRIGHT * (-deltaX / 1000)) + (cameraUP * (deltaY / 1000)));
    }

    // Rotate the view
    void RenderingEngine::rotate(double deltaX, double deltaY) {
        // This doesn't work at all
        double c = 1;//3.14 / 180;
        cameraUP.x += cos(deltaX * c) * sin(deltaY * c);
        cameraUP.y += sin(deltaX * c) * cos(deltaY * c);
        cameraUP.z += cos(deltaY * c);
    }

    // Zoom the view
    void RenderingEngine::zoom(double delta) {
        cameraPosition.x -= delta / 1000;
        cameraPosition.y += delta / 1000;
    }

} // RENDERING