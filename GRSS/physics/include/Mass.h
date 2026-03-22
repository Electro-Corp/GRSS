/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Mass.h  
 * [DESCRIPTION] Class definition of a mass
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include <common/Vector.h>

namespace Physics{
    class Mass{
        public:
            Vector3 position, rotation;
            Vector3 linearVelocity, rotationalVelocity;

            double mass, radius;
    };
}