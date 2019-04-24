#pragma once
#include "Entity.hpp"

namespace ECS
{
	//Base class for single component system
	template<typename Comp> class System
	{
	protected:
		std::map<Entity*, Comp> registry; 

	public:

		//Adds an entity to the registry 
		virtual Comp* registerEntity(Entity* e) {
			Comp* comp = &registry[e]; 
			e->addComponent(comp);
			return comp;
		}

		//Removes the entity from the registry
		virtual void deregisterEntity(Entity* e) {
			//remove ref from entity
			e->removeComponent(Comp::getStaticID());
			
			//remove from registry
			registry.erase(e);
		}

		//Removes all components and detaches them from entity parents 
		virtual void removeAll()
		{
			//remove references to component
			for(auto& entry : registry){
				entry.first->removeComponent(Comp::getStaticID());
			}

			registry.clear();
		}

		//NOTE: System should be destructed before entities to ensure that
		//the Component::master pointers are not dangling 
		virtual ~System(){
			removeAll();
		}
	};

}