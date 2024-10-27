/*****************************************************************//**
 * \file   Layer.cpp
 * \brief  The abstact Layer class
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

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
