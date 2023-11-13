#pragma once

#include "Entity.h"

namespace Illusion {

	class Script
	{
	public:
		virtual void OnCreate() = 0;

		virtual void OnDestroy() = 0;

		virtual void OnUpdate(Illusion::Timestep ts) = 0;

		virtual void OnEvent(Illusion::Event& e) = 0;

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}
