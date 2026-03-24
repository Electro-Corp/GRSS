/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Physics.cpp  
 * [DESCRIPTION] This file contains the main implmentations for the physics engine of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#include <include/Physics.h>

namespace Physics{

    PhysicsEngine::PhysicsEngine() {}

    void PhysicsEngine::addMass(std::shared_ptr<Mass> mass) {
        masses.push_back(std::move(mass));
    }

    void PhysicsEngine::step(double dt) {
        // Basic Euler integration, move to rk4 or better
        for (auto& mass : masses) {
            mass->position.x += mass->linearVelocity.x * dt;
            mass->position.y += mass->linearVelocity.y * dt;
            mass->position.z += mass->linearVelocity.z * dt;
        }
    }

} // PHYSICS