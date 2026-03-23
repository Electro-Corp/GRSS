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
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <include/Object.h>

namespace Rendering{
    // Main class for the Rendering engine
    class RenderingEngine{
        public:
            RenderingEngine();

            // Setup viewport
            void setupViewport(int tlX, int tlY, int brX, int brY);

            // Add an object to the scene
            void addObject(std::unique_ptr<Object>);

            // Render the current enviorment
            void tick();
        private:
            std::vector<std::unique_ptr<Object>> objects;
    };
}