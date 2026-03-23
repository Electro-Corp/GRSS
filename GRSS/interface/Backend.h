/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Backend.h
 * [DESCRIPTION] Allows the interface to contact the renderer and physics engine
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <rendering/include/Rendering.h>
#include <physics/include/Physics.h>

static Rendering::RenderingEngine* renderingEngine;
static Physics::PhysicsEngine* physicsEngine;