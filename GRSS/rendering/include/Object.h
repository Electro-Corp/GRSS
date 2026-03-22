/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Object.h  
 * [DESCRIPTION] This file contains the generic rendering object
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include <include/Mass.h>

namespace Rendering{
    class Object{
        public: 
            Physics::Mass* mass;

            Object(Physics::Mass* mass);

            virtual void render();
        private:
    };
} // RENDERING