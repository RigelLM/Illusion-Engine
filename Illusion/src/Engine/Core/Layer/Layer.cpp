/*
 * ======================= Layer.cpp ===========================
 *						  -- ils --
 *                                         CREATE -- 2023.01.13
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The abstract Layer class
 * ----------------------------
 */
#include "pch.h"
#include "Layer.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	Layer::Layer(const std::string& debugname)
		: m_DebugName(debugname) {}

	Layer::~Layer() {}

//--------------------namespace: Illusion ends--------------------

}
