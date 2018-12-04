#include "ModuleInput.h"

#include "SDL.h"

bluefir::modules::ModuleInput::ModuleInput()
{
	memset(&keyboard_, 0, KEY_COUNT * sizeof(KeyState));
	memset(&mouse_, 0, MOUSE_KEY_COUNT * sizeof(KeyCode));
}

bool bluefir::modules::ModuleInput::Init()
{
	LOGINFO("Initializing Input System.");
	SDL_Init(0);
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOGERROR("Input System could not be initialized: %s", SDL_GetError());
		return false;
	}
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleInput::PreUpdate()
{
	UpdateKeyboardState();
	UpdateMouseState();
	return ParseEvents();
}

bool bluefir::modules::ModuleInput::CleanUp()
{
	LOGINFO("Closing input system.");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}

void bluefir::modules::ModuleInput::UpdateKeyboardState()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	for (unsigned int i = 0U; i < KEY_COUNT; ++i)
	{		
		if (keys[i] == 1)
		{
			if  (keyboard_[i] == KeyState::IDLE) keyboard_[i] = KeyState::DOWN;
			else keyboard_[i] = KeyState::REPEAT;
		}
		else
		{
			if (keyboard_[i] == KeyState::REPEAT || keyboard_[i] == KeyState::DOWN)
				keyboard_[i] = KeyState::UP;
			else
				keyboard_[i] = KeyState::IDLE;
		}	
	}
}

void bluefir::modules::ModuleInput::UpdateMouseState()
{
	for (unsigned int i = 0U; i < MOUSE_KEY_COUNT; ++i)
	{
		if (mouse_[i] == KeyState::DOWN)	mouse_[i] = KeyState::REPEAT;
		else if (mouse_[i] == KeyState::UP)		mouse_[i] = KeyState::IDLE;
	}

	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	mouse_deltax_ = mouse_sensitivity * (float)(mouse_x_ - x);
	mouse_deltay_ = mouse_sensitivity * (float)(mouse_y_ - y);
	mouse_x_ = x;
	mouse_y_ = y;
}

bluefir::modules::UpdateState bluefir::modules::ModuleInput::ParseEvents()
{
	static SDL_Event event;
	switch (event.type)
	{
	case SDL_QUIT:
		return UpdateState::Update_End;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)			mouse_[(int)MouseButton::MOUSE_LEFT] = KeyState::DOWN;
		else if (event.button.button == SDL_BUTTON_RIGHT)	mouse_[(int)MouseButton::MOUSE_RIGHT] = KeyState::DOWN;
		else if (event.button.button == SDL_BUTTON_MIDDLE)	mouse_[(int)MouseButton::MOUSE_MIDDLE] = KeyState::DOWN;
		break;

	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)			mouse_[(int)MouseButton::MOUSE_LEFT] = KeyState::UP;
		else if (event.button.button == SDL_BUTTON_RIGHT)	mouse_[(int)MouseButton::MOUSE_RIGHT] = KeyState::UP;
		else if (event.button.button == SDL_BUTTON_MIDDLE)	mouse_[(int)MouseButton::MOUSE_MIDDLE] = KeyState::UP;
		break;

	case SDL_MOUSEWHEEL:
		mouse_wheel_ = event.wheel.y;

	case SDL_WINDOWEVENT:
		// TODO: Call Module Renderer ResizeEvent();
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) int a = 0;
		break;

	default:
		break;
	}

	return UpdateState::Update_Continue;
}
