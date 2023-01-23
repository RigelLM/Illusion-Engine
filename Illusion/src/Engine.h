/*
 * ========================== Engine.h ============================
 *                           -- ils --
 *                                              CREATE -- 2023.01.12
 *                                              MODIFY --
 * -----------------------------------------------------------------
 * The total including file for the application
 * header file that connects the Engine and the Game
 * ----------------------------
 */

#pragma once

// For use in applications
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/Layer/Layer.h"
#include "Engine/Core/Log/Log.h"

#include "Engine/Core/Utils/Timestep.h"

#include "Engine/Core/Input/Input.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Core/Resource/FileReader.h"
#include "Engine/Core/Resource/ResourceManager.h"

// Renderer 
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderCommand.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffers.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/CameraController.h"
#include "Engine/Renderer/Texture.h"