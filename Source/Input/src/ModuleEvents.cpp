#include "ModuleEvents.h"

#include "SDL.h"

#include "ModuleRenderer.h"
#include "ModuleEditor.h"
#include "Input.h"

bluefir::modules::ModuleEvents::ModuleEvents() {}
bluefir::modules::ModuleEvents::~ModuleEvents() {}

bool bluefir::modules::ModuleEvents::Init()
{
	SDL_Init(0);
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOGERROR("Input System could not be initialized: %s", SDL_GetError());
		return false;
	}
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEvents::PreUpdate()
{
	UpdateKeyboardState();
	UpdateMouseState();
	UpdateState ret = ParseEvents();
	return ret;
}

bool bluefir::modules::ModuleEvents::CleanUp()
{
	LOGINFO("Closing input system.");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}

void bluefir::modules::ModuleEvents::UpdateKeyboardState()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	for (unsigned int i = 0U; i < KEY_COUNT; ++i) 
		bluefir_input.SetKeyState(i, keys[i] == 1);
}

void bluefir::modules::ModuleEvents::UpdateMouseState()
{
	bluefir_input.UpdateMouseState();

	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	bluefir_input.SetMousePosition(x, y);
}

bluefir::modules::UpdateState bluefir::modules::ModuleEvents::ParseEvents()
{
	static SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ModuleEditor::getInstance().ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			return UpdateState::Update_End;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)			bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_LEFT,true);
			else if (event.button.button == SDL_BUTTON_RIGHT)	bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_RIGHT, true);
			else if (event.button.button == SDL_BUTTON_MIDDLE)	bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_MIDDLE, true);
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)			bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_LEFT, false);
			else if (event.button.button == SDL_BUTTON_RIGHT)	bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_RIGHT, false);
			else if (event.button.button == SDL_BUTTON_MIDDLE)	bluefir_input.SetMouseButtonState(core::MouseButton::MOUSE_MIDDLE, false);
			break;

		case SDL_MOUSEWHEEL:
			core::Input::getInstance().SetMouseWheel(event.wheel.y);
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) modules::ModuleRenderer::getInstance().ResizeEvent((unsigned int)event.window.windowID);
			break;

		default:
			break;
		}
	}

	return UpdateState::Update_Continue;
}
