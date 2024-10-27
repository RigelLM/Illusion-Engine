/*****************************************************************//**
 * \file   Random.cpp
 * \brief  Util class for generating random numbers
 *
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#include "pch.h"
#include "Random.h"


namespace Illusion
{
	namespace Utils
	{
		std::mt19937 Random::s_RandomEngine;
		std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

	}

}