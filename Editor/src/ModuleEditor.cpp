#include "ModuleEditor.h"

#include "../Vendor/imgui-docking/imgui.h"
#include "../Vendor/imgui-docking/imgui_impl_sdl.h"
#include "../Vendor/imgui-docking/imgui_impl_opengl3.h"

#include "Graphics.h"
#include "EditorPanel.h"
#include "ModuleRenderer.h"

#include "Panels/PanelTime.h"
#include "Panels/PanelRenderer.h"
#include "Panels/PanelScene.h"

#define GLSL_VERSION "#version 130"

bluefir::modules::ModuleEditor::~ModuleEditor() {}

bool bluefir::modules::ModuleEditor::Init()
{
	LOGINFO("Initializing Editor.");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui_ImplSDL2_InitForOpenGL(ModuleRenderer::getInstance().GetWindowData()->window, ModuleRenderer::getInstance().GetWindowData()->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	ImGui::StyleColorsDark();

	panels_.push_back(new editor::PanelTime());
	panels_.push_back(new editor::PanelRenderer());
	panels_.push_back(new editor::PanelScene());

	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		(*it)->Init();

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::PreUpdate()
{

	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::Update()
{
	// ModuleRenderer::getInstance().Render();
	// Activate Editor Frame Buffer
	// Clear Viewport

	// Create new imgui editor fra,e
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(ModuleRenderer::getInstance().GetWindowData()->window);
	ImGui::NewFrame();

	// Draw UI
	if (!MainMenu()) return UpdateState::Update_End;
	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		(*it)->Draw();

	// Render imgui editor
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::PostUpdate()
{
	return UpdateState::Update_Continue;
}

bool bluefir::modules::ModuleEditor::CleanUp()
{
	LOGINFO("Closing Editor.");
	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		delete (*it);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void bluefir::modules::ModuleEditor::ProcessEvent(void * event) const
{
	assert(event);
	ImGui_ImplSDL2_ProcessEvent((SDL_Event*)event);
}

bool bluefir::modules::ModuleEditor::MainMenu()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit")) return false;
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Windows"))
	{
		for (auto it = panels_.begin(); it != panels_.end(); ++it)
		{
			ImGui::MenuItem((*it)->name_.c_str(), NULL, &(*it)->enabled_);
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	return true;
}
