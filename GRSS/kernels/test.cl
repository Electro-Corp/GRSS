/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] test.cl
 * [DESCRIPTION] OpenCL kernel test
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/

__kernel void basic_mass_calculate(__global float* inputDT, __global float* inputVelocity, __global float* outputPosition){
	int i = get_global_id(0);
	outputPosition[i] = inputDT[0] * inputVelocity[i];
}