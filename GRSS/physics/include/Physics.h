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

#include <CL/cl.h>

#include <physics/include/Mass.h>
#include <common/aixlog.hpp>

namespace Physics{
	typedef struct CL_ComputeDevice {
		// Info
		char name[128];
		char vendor[128];
		cl_ulong memory;
		cl_uint units;
		// OpenCL specfic
		cl_device_id devID;
		cl_context devContext;
		cl_uint devType;
	};

	class PhysicsEngine {
	public:
		PhysicsEngine();

		void addMass(std::shared_ptr<Mass> mass);
		void removeMass(int index);

		void step(double dt);

		std::vector<std::shared_ptr<Mass>> getMasses() {
			return masses;
		}

		std::vector<CL_ComputeDevice> getOpenCLDevices() {
			return computeDevices;
		}
	private:
		// Selected platform
		cl_platform_id openCLPlatform;
		// Compute device
		std::vector<CL_ComputeDevice> computeDevices;
		// List of currently simulated masses
		std::vector<std::shared_ptr<Mass>> masses;

		// Initilize OpenCL
		void initializeOpenCL();
		// Initlize device
		void initializeOpenCLDevice(int id);
	};
} // PHYSICS