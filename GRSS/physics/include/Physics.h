/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Physics.h  
 * [DESCRIPTION] This file contains the main definitions for the physics engine of GRSS
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include <vector>
#include <memory>

#include <physics/include/Mass.h>

namespace Physics{
	class PhysicsEngine {
	public:
		PhysicsEngine();

		void addMass(std::unique_ptr<Mass> mass);

		void step(double dt);

		const std::vector<std::unique_ptr<Mass>>& getMasses() const {
			return masses;
		}
	private:
		std::vector<std::unique_ptr<Mass>> masses;
	};
} // PHYSICS