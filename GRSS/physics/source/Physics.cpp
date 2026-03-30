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

    PhysicsEngine::PhysicsEngine() {
        // Init logging
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
        LOG(INFO) << "GRSS Physics Engine started...\n";
        LOG(INFO) << "Initlizing OpenCL...\n";

        initializeOpenCL();
    }

    void PhysicsEngine::initializeOpenCL() {
        // Poll platforms
        cl_int CL_err = CL_SUCCESS;
        cl_uint nPlat = 0;

        CL_err = clGetPlatformIDs(0, NULL, &nPlat);
        if (CL_err == CL_SUCCESS) {
            LOG(INFO) << "Found " << nPlat << " OpenCL platforms.\n";
            if (nPlat == 0) {
                LOG(ERROR) << "No platforms! Quiting.\n";
                exit(-1);
            }
        }
        else {
            LOG(ERROR) << "Error polling for OpenCL platforms: " << CL_err << "... quiting.\n";
            exit(-1);
        }
          
        // Select first platform
        clGetPlatformIDs(1, &openCLPlatform, nullptr);
        // Retrive name
        char platformName[128];
        clGetPlatformInfo(openCLPlatform, CL_PLATFORM_NAME, sizeof(platformName), platformName, nullptr);

        // Get number of GPU devices
        cl_uint numGPU;
        clGetDeviceIDs(openCLPlatform, CL_DEVICE_TYPE_GPU, 0, nullptr, &numGPU);
        LOG(INFO) << "Found " << numGPU << " GPUs on platform " << platformName << ".\n";

        // Collect all GPUs 
        for (int i = 0; i < numGPU; i++) initializeOpenCLDevice(i + 1);
    }

    void PhysicsEngine::initializeOpenCLDevice(int id) {
        CL_ComputeDevice device;
        // Get device ID
        clGetDeviceIDs(openCLPlatform, CL_DEVICE_TYPE_GPU, id, &device.devID, nullptr);
        // Poll device info
        clGetDeviceInfo(device.devID, CL_DEVICE_NAME, sizeof(device.name), &device.name, nullptr);
        clGetDeviceInfo(device.devID, CL_DEVICE_VENDOR, sizeof(device.vendor), &device.vendor, nullptr);
        clGetDeviceInfo(device.devID, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(device.memory), &device.memory, nullptr);
        clGetDeviceInfo(device.devID, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(device.units), &device.units, nullptr);
        // Create context
        device.devContext = clCreateContextFromType(NULL, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);
        // Print device info
        LOG(INFO) << "Initialized device " << device.vendor << "'s " << device.name << " with " << device.memory / 1048576 << "MB of memory and " << device.units << " compute units.\n";
        // Add device
        this->computeDevices.push_back(device);
    }

    void PhysicsEngine::addMass(std::shared_ptr<Mass> mass) {
        masses.push_back(std::move(mass));
    }

    void PhysicsEngine::removeMass(int index){
        masses.erase(masses.begin() + index);
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