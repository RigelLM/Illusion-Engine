/*****************************************************************//**
 * \file   Entity.h
 * \brief  Wrapper class for entity in entt lib
 *
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#include "pch.h"
#include "Entity.h"

namespace Illusion
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{
	}

}
