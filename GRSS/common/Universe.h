/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Universe.h
 * [DESCRIPTION] The Universe coordinator
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <rendering/include/Rendering.h>
#include <physics/include/Physics.h>
#include <common/Vector.h>

class Universe {
public:
	Universe();

	void setupUniverseViewport(int tlX, int tlY, int brX, int brY);

	void addPlanet(Vector3 pos, double mass, double radius);

	void updateRenderer();

	void tick(double dt);

private:
	Rendering::RenderingEngine* renderingEngine;
	Physics::PhysicsEngine* physicsEngine;
};


extern Universe* universe;
