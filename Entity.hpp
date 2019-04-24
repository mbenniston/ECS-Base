#pragma once
#include <map>
#include <stdexcept>

#include "Component.hpp"

namespace ECS
{
	class Entity
	{
	protected:
		std::map<ComponentID, Component*> components; //actual components stored in systems

	public:
		//Returns whether a component with the given id is present in the entity
		inline bool hasComponent(ComponentID comp) const noexcept {
			return components.find(comp) != components.end();
		}

		//Adds a component to the entity using its component id
		template<typename Comp> void addComponent(Comp* c)
		{
			//check if a component with the same name already exists
			if(hasComponent(c->getID())){
				throw std::exception("Entity does not contain component");
			}

			components[Comp::getStaticID()] = (Component*)c;
			//set ownership
			c->master = this;
		}

		//Removes a component from the entity using its component id
		void removeComponent(ComponentID comp) 
		{
			//check the component exists
			if(!hasComponent(comp)){
				throw std::exception("Entity does not contain component");
			}

			//remove ownership
			components[comp]->master = nullptr;
			components.erase(comp);
		}

		//Component getter with presence checks, (constant return type version)
		const Component* getComponent(ComponentID comp) const
		{
			//check the component exists
			if(!hasComponent(comp)){
				throw std::exception("Entity does not contain component");
			}

			return components.at(comp);
		}

		//Component getter with presence checks
		Component* getComponent(ComponentID comp)
		{
			//check the component exists
			if(!hasComponent(comp)){
				throw std::exception("Entity does not contain component");
			}

			return components.at(comp);
		}

		//Component getter with presence checks, (no args template getter)
		template<typename Comp> Comp* getComponent()
		{
			//check the component exists
			if(!hasComponent(Comp::getStaticID())){
				throw std::exception("Entity does not contain component");
			}
			
			return (Comp*)components.at(Comp::getStaticID());
		}

		virtual ~Entity()
		{
			//Check that all systems has deregistered the entity
			if (!components.empty()) {
				throw std::exception("Cannot destruct entity that contains components, remember to deregister them from the systems");
			}
		}
	};
}