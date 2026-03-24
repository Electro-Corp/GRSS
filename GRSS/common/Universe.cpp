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

Universe* universe = new Universe();

Universe::Universe() {
	// Create engines
	this->physicsEngine = new Physics::PhysicsEngine();
	this->renderingEngine = new Rendering::RenderingEngine();
}

void Universe::setupUniverseViewport(int tlX, int tlY, int brX, int brY) {
	this->renderingEngine->setupViewport(tlX, tlY, brX, brY);
}

void Universe::addPlanet(Vector3 pos, double mass, double radius) {
	// 1. Create physics mass
	std::shared_ptr<Physics::Mass> newMass = std::make_shared<Physics::Mass>(pos);
	newMass->mass = mass;
	newMass->radius = radius;
	newMass->linearVelocity = Vector3(0.0, 0.5, 0.0);

	// 2. Create rendering sphere
	std::shared_ptr<Rendering::SphereObject> sphereView = std::make_shared<Rendering::SphereObject>(newMass.get());

	// 3. Give ownwership
	physicsEngine->addMass(std::move(newMass));
	renderingEngine->addObject(std::move(sphereView));

	// 4. Let everyone know
	connector->trigger(TRIGGER_MASSES_MODIFIED);
}

void Universe::updateRenderer() {
	renderingEngine->tick();
}

void Universe::tick(double dt) {
	physicsEngine->step(dt);
}
