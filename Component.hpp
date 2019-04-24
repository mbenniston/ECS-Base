#pragma once
#include <typeinfo>

namespace ECS
{
	//used to uniquely identify types of components
	using ComponentID = std::size_t;

	//macro to define ID getters for a given component type
	//TODO: should check for hash code collisions 
	#define COMP_ATTRIBS(type) static ComponentID getStaticID() { return typeid(type).hash_code(); } virtual ComponentID getID() override { return typeid(type).hash_code(); }

	//Entity class forward declare
	class Entity;

	//Used to represent a piece (or pieces) of data about an entity
	struct Component
	{
		Entity* master;
		virtual ComponentID getID() = 0;
	};
}
