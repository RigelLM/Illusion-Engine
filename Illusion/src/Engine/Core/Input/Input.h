/*
 * ========================== Input.h ==========================
 *                             -- ils --
 *                                          CREATE -- 2023.01.12
 *                                          MODIFY --
 * -------------------------------------------------------------
 * The abstrack Input class
 * Containing static methods that
 * can be called outside of the class
 *
 * Some KeyCodes and MouseButtonCodes
 * ----------------------------
 */

#pragma once

#include "Engine/Core/Core.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	class Input
	{

	public:

		// Static methods that could be used outside of this class
		// Call the virtual function that would be implemented in the inhirated class
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:

		// The implementation that would be called by the static method
		// Pure virtual function means it must be implemented by the inhirated class
		// Inhirated class has to implements these methods for its platform
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:

		static Input* s_Instance;

	};
	//--------------------namespace: Illusion ends--------------------
}

/*
 * =========================== KeyCodes ========================
 *                            -- ils --
 *                                          CREATE -- 2023.01.12
 *                                          MODIFY --
 * -------------------------------------------------------------
 * From glfw3.h
 */

 //----------------------- Key Codes -----------------------

 /* Printable keys */
#define ILLUSION_KEY_SPACE              32
#define ILLUSION_KEY_APOSTROPHE         39  /* ' */
#define ILLUSION_KEY_COMMA              44  /* , */
#define ILLUSION_KEY_MINUS              45  /* - */
#define ILLUSION_KEY_PERIOD             46  /* . */
#define ILLUSION_KEY_SLASH              47  /* / */
#define ILLUSION_KEY_0                  48
#define ILLUSION_KEY_1                  49
#define ILLUSION_KEY_2                  50
#define ILLUSION_KEY_3                  51
#define ILLUSION_KEY_4                  52
#define ILLUSION_KEY_5                  53
#define ILLUSION_KEY_6                  54
#define ILLUSION_KEY_7                  55
#define ILLUSION_KEY_8                  56
#define ILLUSION_KEY_9                  57
#define ILLUSION_KEY_SEMICOLON          59  /* ; */
#define ILLUSION_KEY_EQUAL              61  /* = */
#define ILLUSION_KEY_A                  65
#define ILLUSION_KEY_B                  66
#define ILLUSION_KEY_C                  67
#define ILLUSION_KEY_D                  68
#define ILLUSION_KEY_E                  69
#define ILLUSION_KEY_F                  70
#define ILLUSION_KEY_G                  71
#define ILLUSION_KEY_H                  72
#define ILLUSION_KEY_I                  73
#define ILLUSION_KEY_J                  74
#define ILLUSION_KEY_K                  75
#define ILLUSION_KEY_L                  76
#define ILLUSION_KEY_M                  77
#define ILLUSION_KEY_N                  78
#define ILLUSION_KEY_O                  79
#define ILLUSION_KEY_P                  80
#define ILLUSION_KEY_Q                  81
#define ILLUSION_KEY_R                  82
#define ILLUSION_KEY_S                  83
#define ILLUSION_KEY_T                  84
#define ILLUSION_KEY_U                  85
#define ILLUSION_KEY_V                  86
#define ILLUSION_KEY_W                  87
#define ILLUSION_KEY_X                  88
#define ILLUSION_KEY_Y                  89
#define ILLUSION_KEY_Z                  90
#define ILLUSION_KEY_LEFT_BRACKET       91  /* [ */
#define ILLUSION_KEY_BACKSLASH          92  /* \ */
#define ILLUSION_KEY_RIGHT_BRACKET      93  /* ] */
#define ILLUSION_KEY_GRAVE_ACCENT       96  /* ` */
#define ILLUSION_KEY_WORLD_1            161 /* non-US #1 */
#define ILLUSION_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define ILLUSION_KEY_ESCAPE             256
#define ILLUSION_KEY_ENTER              257
#define ILLUSION_KEY_TAB                258
#define ILLUSION_KEY_BACKSPACE          259
#define ILLUSION_KEY_INSERT             260
#define ILLUSION_KEY_DELETE             261
#define ILLUSION_KEY_RIGHT              262
#define ILLUSION_KEY_LEFT               263
#define ILLUSION_KEY_DOWN               264
#define ILLUSION_KEY_UP                 265
#define ILLUSION_KEY_PAGE_UP            266
#define ILLUSION_KEY_PAGE_DOWN          267
#define ILLUSION_KEY_HOME               268
#define ILLUSION_KEY_END                269
#define ILLUSION_KEY_CAPS_LOCK          280
#define ILLUSION_KEY_SCROLL_LOCK        281
#define ILLUSION_KEY_NUM_LOCK           282
#define ILLUSION_KEY_PRINT_SCREEN       283
#define ILLUSION_KEY_PAUSE              284
#define ILLUSION_KEY_F1                 290
#define ILLUSION_KEY_F2                 291
#define ILLUSION_KEY_F3                 292
#define ILLUSION_KEY_F4                 293
#define ILLUSION_KEY_F5                 294
#define ILLUSION_KEY_F6                 295
#define ILLUSION_KEY_F7                 296
#define ILLUSION_KEY_F8                 297
#define ILLUSION_KEY_F9                 298
#define ILLUSION_KEY_F10                299
#define ILLUSION_KEY_F11                300
#define ILLUSION_KEY_F12                301
#define ILLUSION_KEY_F13                302
#define ILLUSION_KEY_F14                303
#define ILLUSION_KEY_F15                304
#define ILLUSION_KEY_F16                305
#define ILLUSION_KEY_F17                306
#define ILLUSION_KEY_F18                307
#define ILLUSION_KEY_F19                308
#define ILLUSION_KEY_F20                309
#define ILLUSION_KEY_F21                310
#define ILLUSION_KEY_F22                311
#define ILLUSION_KEY_F23                312
#define ILLUSION_KEY_F24                313
#define ILLUSION_KEY_F25                314
#define ILLUSION_KEY_KP_0               320
#define ILLUSION_KEY_KP_1               321
#define ILLUSION_KEY_KP_2               322
#define ILLUSION_KEY_KP_3               323
#define ILLUSION_KEY_KP_4               324
#define ILLUSION_KEY_KP_5               325
#define ILLUSION_KEY_KP_6               326
#define ILLUSION_KEY_KP_7               327
#define ILLUSION_KEY_KP_8               328
#define ILLUSION_KEY_KP_9               329
#define ILLUSION_KEY_KP_DECIMAL         330
#define ILLUSION_KEY_KP_DIVIDE          331
#define ILLUSION_KEY_KP_MULTIPLY        332
#define ILLUSION_KEY_KP_SUBTRACT        333
#define ILLUSION_KEY_KP_ADD             334
#define ILLUSION_KEY_KP_ENTER           335
#define ILLUSION_KEY_KP_EQUAL           336
#define ILLUSION_KEY_LEFT_SHIFT         340
#define ILLUSION_KEY_LEFT_CONTROL       341
#define ILLUSION_KEY_LEFT_ALT           342
#define ILLUSION_KEY_LEFT_SUPER         343
#define ILLUSION_KEY_RIGHT_SHIFT        344
#define ILLUSION_KEY_RIGHT_CONTROL      345
#define ILLUSION_KEY_RIGHT_ALT          346
#define ILLUSION_KEY_RIGHT_SUPER        347
#define ILLUSION_KEY_MENU               348

//----------------------- Key Codes -----------------------




/*
 * ==================== MouseButtonCodes =======================
 *                         -- ils --
 *                                          CREATE -- 2023.01.12
 *                                          MODIFY --
 * -------------------------------------------------------------
 * From glfw3.h
 *
 */

 //------------------ Mouse Button Codes -------------------

 // Mouse Button Code
#define ILLUSION_MOUSE_BUTTON_1         0
#define ILLUSION_MOUSE_BUTTON_2         1
#define ILLUSION_MOUSE_BUTTON_3         2
#define ILLUSION_MOUSE_BUTTON_4         3
#define ILLUSION_MOUSE_BUTTON_5         4
#define ILLUSION_MOUSE_BUTTON_6         5
#define ILLUSION_MOUSE_BUTTON_7         6
#define ILLUSION_MOUSE_BUTTON_8         7
#define ILLUSION_MOUSE_BUTTON_LAST      ILLUSION_MOUSE_BUTTON_8
#define ILLUSION_MOUSE_BUTTON_LEFT      ILLUSION_MOUSE_BUTTON_1
#define ILLUSION_MOUSE_BUTTON_RIGHT     ILLUSION_MOUSE_BUTTON_2
#define ILLUSION_MOUSE_BUTTON_MIDDLE    ILLUSION_MOUSE_BUTTON_3


//------------------ Mouse Button Codes -------------------
