/*
 * ========================== Core.h ========================
 *                          -- ils --
 *                                        CREATE -- 2023.01.12
 *                                        MODIFY --
 * ----------------------------------------------------------
 * Helper Macros
 * ----------------------------
 */

#pragma once

#include <memory>

#ifdef ILLUSION_DEBUG
	#define ILLUSION_ENABLE_ASSERTS
#endif

#ifdef ILLUSION_ENABLE_ASSERTS
	#define ILLUSION_CLIENT_ASSERT(x, ...) { if(!(x)) { ENGINE_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ILLUSION_CORE_ASSERT(x, ...) { if (!(x)) { ENGINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ILLUSION_CLIENT_ASSERT(x, ...)
	#define ILLUSION_CORE_ASSERT(x, ...)
#endif

//move 1 to the left by x bit, used in creating a bitfield
#define BIT(x) (1 << x)

// Macro that generate a callable function which is like a pointer to the funtion fn
#define ENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Illusion
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}