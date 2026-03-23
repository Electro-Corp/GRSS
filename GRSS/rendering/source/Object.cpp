/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Object.cpp  
 * [DESCRIPTION] This file contains the main implementation for renderable objects
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <include/Object.h>

namespace Rendering{

	Object::Object(Physics::Mass* mass) : mass(mass){

	}

	SphereObject::SphereObject(Physics::Mass* mass) : Object(mass) {

	}

	void SphereObject::render() {
		if (!mass) return;

		glPushMatrix();
		glTranslated(mass->position.x, mass->position.y, mass->position.z);

		GLUquadric* quad = gluNewQuadric();
		gluSphere(quad, mass->radius > 0 ? mass->radius : 1.0, 32, 32);
		gluDeleteQuadric(quad);

		glPopMatrix();
	}

} // RENDERING
