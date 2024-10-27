#pragma once

/*****************************************************************//**
 * \file   pch.h
 * \brief  Pre-compile header, accelerating compiling speed,
 * including some header files that would not change frequently
 * 
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

//!!!!!Include this in all cpp file!!!!!

//--------------------C++ Standard Library--------------------
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

//--------------------C++ Standard Templates--------------------
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>


#include "Engine/Core/Log/Log.h"

#include <Windows.h>