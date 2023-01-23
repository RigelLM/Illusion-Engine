/*
 * ======================= LayerStack.cpp ===========================
 *						  -- ils --
 *                                         CREATE -- 2023.01.13
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The layerStack class
 * ----------------------------
 */
#include "pch.h"
#include "LayerStack.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Initialize the LayerStack
	LayerStack::LayerStack()
	{
	}

	// Delete all the layers and layerstack
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	// Put the layer into the layerstack
	// It is put into the "layer zone"
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	// Take the layer out from the layerstack
	// Update the "layer/overlay layer line"
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	// Put the overlay layer into the layerstacj
	// It is put into the "overlay layer zone"(above the pointer)
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	// Take the overlay layer out from the layerstack
	// It is above the pointer so it don't have to be updated
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
	//--------------------namespace: Illusion ends--------------------
}
