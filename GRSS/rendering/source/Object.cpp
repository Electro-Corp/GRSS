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
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <include/Object.h>

namespace Rendering{

	Object::Object(Physics::Mass* mass) : mass(mass){

	}

	SphereObject::SphereObject(Physics::Mass* mass) : Object(mass) {
		quad = gluNewQuadric();
	}

	void SphereObject::render() {
		if (!mass) return;

		glPushMatrix();
		glTranslated(mass->position.x, mass->position.y, mass->position.z);
		// Material
		GLfloat amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat spec[] = { 0.1f, 0.1f, 0.1f, 0.1f };
		GLfloat shine[] = { 0.5f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
		glMaterialf(GL_FRONT, GL_SHININESS, shine[0]);
		// Render sphere
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluSphere(quad, mass->radius > 0 ? mass->radius : 1.0, 32, 32);
		glPopMatrix();
	}

	SphereObject::~SphereObject() {
		gluDeleteQuadric(quad);
	}

} // RENDERING