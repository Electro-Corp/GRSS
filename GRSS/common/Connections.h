/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Connections.h
 * [DESCRIPTION] Allows UI components to talk with each other
 *
 * (c) 2026 Electro-Corp, All rights reserved.
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
 */
#pragma once

#include <vector>
#include <functional>

#include <rendering/include/Object.h>

// Currently selected object in the list view
extern Rendering::Object* selectedObject;
extern int selectedIndex;

typedef struct Connection{
	int connectionID;
	std::function<void()> function;
	// Optimization for triggers with multiple connections
	Connection* next = 0;
} Connection;

class Connector {
public:
	Connector();

	// Must be implmented in header because of C++ bs
	template <typename T>
	void addConnection(T& object, void(T::* function)(void), int id) {
		Connection* connection = new Connection;
		connection->connectionID = id;
		connection->function = std::bind(function, std::ref(object));
		// See if a connection already exists to this id
		// slower on init, but faster during runtime
		for(Connection* prevConnection : connections){
			// Is it our id?
			if(prevConnection->connectionID == id){
				Connection* ptr = prevConnection->next;
				// Traverse the chain until we find an empty one
				while(ptr) ptr = ptr->next; 
				ptr = connection;
				// Done
				return;
			}
		}
		this->connections.push_back(connection);
	}

	// Trigger a connection event
	void trigger(int id);
private:
	std::vector<Connection*> connections;
};

/*
 * Add a new id here when a new trigger is needed	
 */
enum Connection_IDs {
	TRIGGER_MASSES_MODIFIED = 0,
	TRIGGER_MASS_SELECTION_CHANGED = 1,
	TRIGGER_SELECTED_MASS_MODIFIED = 2, // Different from 0 as it doesnt refresh the mass list
};

// Global static Connector
extern Connector* connector;