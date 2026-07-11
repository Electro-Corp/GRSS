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
        openCLPlatformName = platformName;
        // Get number of GPU devices
        cl_uint numGPU;
        clGetDeviceIDs(openCLPlatform, CL_DEVICE_TYPE_GPU, 0, nullptr, &numGPU);
        LOG(INFO) << "Found " << numGPU << " GPUs on platform " << platformName << ".\n";

        // Collect all GPUs 
        for (int i = 0; i < numGPU; i++) initializeOpenCLDevice(i + 1);

        // Create compute context
        openCLComputeContext = clCreateContext(0, 1, &(this->computeDevices[0].devID), NULL, NULL, &CL_err);
        if (CL_err != CL_SUCCESS) {
            LOG(ERROR) << "Error creating OpenCL compute context: " << CL_err << "... quiting.\n";
            exit(-1);
        }

        // Create command queue
        openCLCommandQueue = clCreateCommandQueue(openCLComputeContext, (this->computeDevices[0].devID), 0, &CL_err);
        if (CL_err != CL_SUCCESS) {
            LOG(ERROR) << "Error creating OpenCL command queue: " << CL_err << "... quiting.\n";
            exit(-1);
        }

        // Load kernel source
        std::string programSource = Util::readFile("kernels/test.cl");
        const char* programSourceC[] = { programSource.c_str() };
        const size_t programSourceLen = { programSource.length() };
        testCLProgram = clCreateProgramWithSource(openCLComputeContext, 1, programSourceC, &programSourceLen, &CL_err);
        if (CL_err != CL_SUCCESS) {
            LOG(ERROR) << "Error reading OpenCL kernel file: " << CL_err << "... quiting.\n";
            exit(-1);
        }
        
        // Build the program
        CL_err = clBuildProgram(testCLProgram, 0, NULL, NULL, NULL, NULL);
        if (CL_err != CL_SUCCESS) {
            size_t len;
            char err_buf[2048];
            clGetProgramBuildInfo(testCLProgram, (this->computeDevices[0].devID), CL_PROGRAM_BUILD_LOG, sizeof(err_buf), err_buf, &len);
            LOG(ERROR) << "Error building OpenCL program: " << err_buf << "... quiting.\n";
            exit(-1);
        }

        // Create compute kernel
        k_basic_mass_calculate = clCreateKernel(testCLProgram, "basic_mass_calculate", &CL_err);
        if (CL_err != CL_SUCCESS) {
            LOG(ERROR) << "Error loading kernel from OpenCL program: " << CL_err << "... quiting.\n";
            exit(-1);
        }
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
        cl_int CL_err = CL_SUCCESS;
        // Load mass stuff into mem (in the future, move this into mass itself and have the buffers created once)
        cl_mem cl_step, cl_vel, cl_outPos;
        //
        size_t global = 3;
        for (auto& mass : masses) {
            // Get mass stuff
            float dt_float[1] = { (float)dt };
            float velocity[3] = { (float)mass->linearVelocity.x, (float)mass->linearVelocity.y, (float)mass->linearVelocity.z };
            float out_d[3] = { 0.0f, 0.0f, 0.0f };

            cl_step = clCreateBuffer(openCLComputeContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float), &dt_float, &CL_err);
            cl_vel = clCreateBuffer(openCLComputeContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 3, &velocity, &CL_err);
            cl_outPos = clCreateBuffer(openCLComputeContext, CL_MEM_READ_WRITE, sizeof(float) * 3, NULL, &CL_err);

            CL_err = clSetKernelArg(k_basic_mass_calculate, 0, sizeof(cl_mem), &cl_step);
            CL_err |= clSetKernelArg(k_basic_mass_calculate, 1, sizeof(cl_mem), &cl_vel);
            CL_err |= clSetKernelArg(k_basic_mass_calculate, 2, sizeof(cl_mem), &cl_outPos);

            // Queue kernel 
            CL_err = clEnqueueNDRangeKernel(openCLCommandQueue, k_basic_mass_calculate, 1, NULL, &global, NULL, 0, NULL, NULL);
            if (CL_err != CL_SUCCESS) {
                LOG(ERROR) << "Error enqueuing kernel: " << CL_err << "... quiting.\n";
                exit(-1);
            }

            // Read it back
            CL_err = clEnqueueReadBuffer(openCLCommandQueue, cl_outPos, CL_TRUE, 0, sizeof(float) * 3, &out_d, 0, NULL, NULL);
            if (CL_err != CL_SUCCESS) {
                LOG(ERROR) << "Error reading out buffer: " << CL_err << "... quiting.\n";
                exit(-1);
            }

            mass->position.x += out_d[0];
            mass->position.y += out_d[1];
            mass->position.z += out_d[2];

            clReleaseMemObject(cl_step);
            clReleaseMemObject(cl_vel);
            clReleaseMemObject(cl_outPos);
            /*mass->position.x += mass->linearVelocity.x * dt;
            mass->position.y += mass->linearVelocity.y * dt;
            mass->position.z += mass->linearVelocity.z * dt;*/
        }
    }

} // PHYSICS