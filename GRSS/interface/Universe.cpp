/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Universe.cpp
 * [DESCRIPTION] The Universe. . .
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <interface/Universe.h>

Universe::Universe() {
	// Create engines
	physicsEngine = new Physics::PhysicsEngine();
	renderingEngine = new Rendering::RenderingEngine();
}

void Universe::setupUniverseViewport(int tlX, int tlY, int brX, int brY) {
	renderingEngine->setupViewport(tlX, tlY, brX, brY);
}

void Universe::updateRenderer() {
	renderingEngine->tick();
}