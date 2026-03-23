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
#include <common/Universe.h>
#include <rendering/include/Object.h>

Universe* universe = nullptr;

Universe::Universe() {
	// Create engines
	physicsEngine = new Physics::PhysicsEngine();
	renderingEngine = new Rendering::RenderingEngine();
}

void Universe::setupUniverseViewport(int tlX, int tlY, int brX, int brY) {
	renderingEngine->setupViewport(tlX, tlY, brX, brY);
}

void Universe::addPlanet(Vector3 pos, double mass, double radius) {
	// 1. Create physics mass
	auto newMass = std::make_unique<Physics::Mass>(pos);
	newMass->mass = mass;
	newMass->radius = radius;
	Physics::Mass* observer = newMass.get();

	physicsEngine->addMass(std::move(newMass));

	// 2. Create rendering sphere
	auto sphereView = std::make_unique<Rendering::SphereObject>(observer);
	renderingEngine->addObject(std::move(sphereView));
}

void Universe::updateRenderer() {
	renderingEngine->tick();
}

void Universe::tick(double dt) {
	physicsEngine->step(dt);
}
