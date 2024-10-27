#pragma once

/*****************************************************************//**
 * \file   ImGuiLayer.h
 * \brief  ImGuiLayer class, stores all the render logic for
 * overlay layers
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Engine/Core/Layer/Layer.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		// Call when it is put into the layerstack
		virtual void OnAttach() override;
		// Call when it is taken out from the layerstack
		virtual void OnDetach() override;

		virtual void OnEvent(Event& event) override;

		virtual void OnImGuiRender() override;

		void Begin();

		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColor();

	private:
		bool m_BlockEvents = true;
	};
	//--------------------namespace: Illusion ends--------------------
}

