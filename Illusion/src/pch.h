/*
 * ========================== pch.h ==========================
 *                          -- ils --
 *                                        CREATE -- 2023.01.12
 *                                        MODIFY --
 * ----------------------------------------------------------
 *   Pre Compile Header
 *   Used for accelerate the speed of compiling
 *   Including some libraries that would not change frequently
 * ----------------------------
 */

#pragma once

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