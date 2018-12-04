#ifndef BF_MODULES_INPUT
#define BF_MODULES_INPUT

#include "Module.h"

#define KEY_COUNT 300
#define MOUSE_KEY_COUNT 3

namespace bluefir::modules
{
	enum class KeyState
	{
		IDLE = 0,
		DOWN,
		REPEAT,
		UP
	};

	enum class KeyCode
	{
		A = 4, B = 5, C = 6, D = 7, E = 8, F = 9, G = 10,
		H = 11, I = 12, J = 13, K = 14, L = 15, M = 16, N = 17,
		O = 18, P = 19, Q = 20, R = 21, S = 22, T = 23, U = 24,
		V = 25, W = 26, X = 27, Y = 28, Z = 29,

		LSHIFT = 225,
		LALT = 226
	};

	enum class MouseButton
	{
		MOUSE_LEFT = 0,
		MOUSE_RIGHT = 1,
		MOUSE_MIDDLE = 2
	};

	class ModuleInput : public Module
	{
	public:
		ModuleInput();
		virtual ~ModuleInput();

		// Flow
		virtual bool Init() override;
		virtual UpdateState PreUpdate() override;
		virtual bool CleanUp() override;

		//Access
		bool GetKeyDown(KeyCode k) const	{ return keyboard_[(int)k] == KeyState::DOWN; }
		bool GetKey(KeyCode k) const		{ return keyboard_[(int)k] == KeyState::REPEAT; }
		bool GetKeyUp(KeyCode k) const		{ return keyboard_[(int)k] == KeyState::UP; }

		bool GetMouseButtonDown(MouseButton b) const	{ return mouse_[(int)b] == KeyState::DOWN; }
		bool GetMouseButton(MouseButton b) const		{ return mouse_[(int)b] == KeyState::REPEAT; }
		bool GetMouseButtonUp(MouseButton b) const		{ return mouse_[(int)b] == KeyState::UP; }

		void GetMouseDisplacement(float& x, float& y) { x = mouse_deltax_; y = mouse_deltay_; }
		void GetMousePosition(int& x, int& y) const { x = mouse_x_; y = mouse_y_; }
		float GetMouseWheel() const { return wheel_sensitivity * (float)mouse_wheel_; }

	private:
		void UpdateKeyboardState();
		void UpdateMouseState();
		UpdateState ParseEvents();

	public:
		float mouse_sensitivity = 0.2F;
		float wheel_sensitivity = 5.0F;

	private:
		KeyState* keyboard_;
		KeyState* mouse_;
		int mouse_x_ = 0;
		int mouse_y_ = 0;
		float mouse_deltax_ = 0.0F;
		float mouse_deltay_ = 0.0F;
		int mouse_wheel_ = 0;
	};
}

#endif // !BF_MODULES_INPUT
