/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Connections.cpp
 * [DESCRIPTION] Implementation of interface connection/trigger system
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#include <common/Connections.h>

// Create global connector
Connector* connector = new Connector();
// Selected object pointer
Rendering::Object* selectedObject = 0;
int selectedIndex = -1;

Connector::Connector() {
	
}

void Connector::trigger(int id) {
	for (Connection* connection : connections) {
		if (connection->connectionID == id) {
			connection->function();
			// Traverse the list
			Connection* next = connection->next;
			while(next){
				next->function();
				next = next->next; 
			}
			// Done
			return;
		}
	}
}