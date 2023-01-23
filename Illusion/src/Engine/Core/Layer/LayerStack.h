/*
 * ======================= LayerStack.h ===========================
 *						  -- ils --
 *                                         CREATE -- 2023.01.13
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The layerStack class
 * ----------------------------
 */

#pragma once

#include "Engine/Core/Core.h"
#include "Layer.h"

#include <vector>
 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	class LayerStack
	{
	public:
		LayerStack();
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

