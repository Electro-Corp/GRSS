/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Utility.h
 * [DESCRIPTION] This file contains utility functions for GRSS (file reading, etc)
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

#include "aixlog.hpp"

#include <fstream>
#include <sstream>

namespace Util {
	static std::string readFile(std::string path) {
		std::ifstream file(path);
		if (file.is_open()) {
			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string out = buffer.str();
			return out;
		}
		else {
			LOG(ERROR) << "Utility: Failed to find file " << path << "!\n";
			return "File Not Found";
		}
	}
} // UTIL