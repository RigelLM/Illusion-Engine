#pragma once

/*****************************************************************//**
 * \file   Layer.h
 * \brief  The abstract Layer class
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Engine/Core/Core.h"
#include "Engine/Event/Events.h"
#include "Engine/Core/Utils/Timestep.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Abstract Layer class
	class Layer
	{

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// Call when it is put into the stack
		virtual void OnAttach() {}
		// Call when it is take out from the stack
		virtual void OnDetach() {}
		// Call when it is asked to update
		virtual void OnUpdate(Timestep timestep) {}
		// Call when it receives events
		virtual void OnEvent(Event& event) {}
		
		virtual void OnImGuiRender() {}

		const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
	//--------------------namespace: Illusion ends--------------------

}

