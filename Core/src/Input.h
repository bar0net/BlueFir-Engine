#ifndef BF_CORE_INPUT_H
#define BF_CORE_INPUT_H

#define KEY_COUNT 300
#define MOUSE_KEY_COUNT 3

#include <string>

#define bluefir_input bluefir::core::Input::getInstance()

namespace bluefir::core
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

	class Input
	{
	public:
		virtual ~Input() { delete[] keyboard_; delete[] mouse_; }
		static Input& getInstance() { static Input instance_; return instance_; }

		// Setters
		void SetMouseButtonState(MouseButton b, bool is_down) { mouse_[(int)b] = (is_down ? KeyState::DOWN : KeyState::UP); }
		void UpdateMouseState() 
		{ 
			mouse_wheel_ = 0;
			for (int i = 0; i < MOUSE_KEY_COUNT; ++i)
			{
				if (mouse_[i] == KeyState::DOWN) mouse_[i] = KeyState::REPEAT;
				else if (mouse_[i] == KeyState::UP) mouse_[i] = KeyState::IDLE;
			}
		}
		// TODO: Does it have any sense applying mouse sensitivity to delta x?
		void SetMousePosition(int x, int y) { mouse_deltax_ = mouse_sensitivity * (float)(x - mouse_x_);mouse_deltay_ =  mouse_sensitivity * (float)(y - mouse_y_); mouse_x_ = x; mouse_y_ = y; }
		void SetMouseWheel(int value) { mouse_wheel_ = value; }
		void SetKeyState(int key, bool is_down)
		{
			if (is_down) keyboard_[key] = (keyboard_[key] == KeyState::DOWN ? KeyState::REPEAT : KeyState::DOWN);
			else keyboard_[key] = (keyboard_[key] == KeyState::DOWN || keyboard_[key] == KeyState::REPEAT) ? KeyState::UP : KeyState::IDLE;
		}

		// Getters
		bool GetKeyDown(KeyCode k) const { return keyboard_[(int)k] == KeyState::DOWN; }
		bool GetKey(KeyCode k) const { return keyboard_[(int)k] == KeyState::REPEAT; }
		bool GetKeyUp(KeyCode k) const { return keyboard_[(int)k] == KeyState::UP; }

		bool GetMouseButtonDown(MouseButton b) const { return mouse_[(int)b] == KeyState::DOWN; }
		bool GetMouseButton(MouseButton b) const { return mouse_[(int)b] == KeyState::REPEAT; }
		bool GetMouseButtonUp(MouseButton b) const { return mouse_[(int)b] == KeyState::UP; }

		void GetMouseDisplacement(float& x, float& y) { x = mouse_deltax_; y = mouse_deltay_; }
		void GetMousePosition(int& x, int& y) const { x = mouse_x_; y = mouse_y_; }
		float GetMouseWheel() const { return wheel_sensitivity * (float)mouse_wheel_; }

	private:
		Input() { 
			keyboard_ = new KeyState[KEY_COUNT]; 
			mouse_ = new KeyState[MOUSE_KEY_COUNT]; 	
			memset(keyboard_, 0, KEY_COUNT * sizeof(KeyState));
			memset(mouse_, 0, MOUSE_KEY_COUNT * sizeof(KeyCode));
		}

	public:
		float mouse_sensitivity = 0.05F;
		float wheel_sensitivity = 5.0F;

	private:
		KeyState* keyboard_ = nullptr;
		KeyState* mouse_ = nullptr;
		int mouse_x_ = 0;
		int mouse_y_ = 0;
		int mouse_wheel_ = 0;
		float mouse_deltax_ = 0.0F;
		float mouse_deltay_ = 0.0F;
	};
}

#endif // !BF_CORE_INPUT_H