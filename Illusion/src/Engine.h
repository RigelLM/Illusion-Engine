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
#include "Engine/Core/Log/Log.h"
#include "Engine/Core/Layer/Layer.h"

#include "Engine/Core/Utils/Timestep.h"
#include "Engine/Core/Utils/Timer.h"

#include "Engine/Core/Input/Input.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Core/Resource/FileReader.h"
#include "Engine/Core/Resource/ResourceManager.h"

// Renderer 
#include "Engine/Render/Renderer/Renderer.h"
#include "Engine/Render/Renderer/Renderer2D.h"
#include "Engine/Render/Renderer/RenderCommand.h"

#include "Engine/Render/Utils/Shader.h"
#include "Engine/Render/Utils/Buffers.h"
#include "Engine/Render/Utils/VertexArray.h"

#include "Engine/Render/CameraSystem/Camera.h"
#include "Engine/Render/CameraSystem/CameraController.h"
#include "Engine/Render/Utils/Texture.h"

#include "Engine/Render/ParticleSystem/ParticleSystem.h"

#include "Engine/Render/Animation/SequenceAnimation.h"