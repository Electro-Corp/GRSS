/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Rendering.h  
 * [DESCRIPTION] This file contains the main implementation for the rendering engine of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

#include <include/Object.h>

namespace Renderer{
    // Main class for the Rendering engine
    class RenderingEngine{
        public:
            RenderingEngine(int tlX, int tlY, int brX, int brY);

            // Add an object to the scene
            void addObject(Object* object);

            // Render the current enviorment
            void tick();
        private:
            std::vector<Object*> objects;
    };
}