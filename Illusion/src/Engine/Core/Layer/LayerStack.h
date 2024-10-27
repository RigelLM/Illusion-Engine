#pragma once

/*****************************************************************//**
 * \file   LayerStack.h
 * \brief  The layerstack class that stores all layers for an
 * application
 *
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Engine/Core/Core.h"
#include "Layer.h"

#include <vector>
 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();
		
		// Put layer into the layerstack
		void PushLayer(Layer* layer);
		// Put overlay layer into the layerstack
		void PushOverlay(Layer* overlay);
		// Take the layer out of the layerstack
		void PopLayer(Layer* layer);
		// Take the overlay layer out of the layerstack
		void PopOverlay(Layer* overlay);

		// The beginning positon of the stack
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		// The ending position of the stack
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		// The layerstack
		std::vector<Layer*> m_Layers;
		// The  position of the line between layer and overlay layer
		// All the layers beneath this are layers
		// All the layers above this are overlay layers
		unsigned m_LayerInsertIndex = 0;
	};

	//--------------------namespace: Illusion ends--------------------
}

