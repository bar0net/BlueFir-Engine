#include "ModuleEditor.h"

#include "../Vendor/imgui-docking/imgui.h"
#include "../Vendor/imgui-docking/imgui_impl_sdl.h"
#include "../Vendor/imgui-docking/imgui_impl_opengl3.h"

#include "Graphics.h"
#include "EditorPanel.h"
#include "ModuleRenderer.h"
#include "GameObject.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

#include "Panels/PanelTime.h"
#include "Panels/PanelRenderer.h"
#include "Panels/PanelScene.h"
#include "Panels/PanelInspector.h"
#include "Panels/PanelConsole.h"
#include "Panels/PanelTexture.h"
#include "Panels/PanelEditorView.h"

#define GLSL_VERSION "#version 130"

bluefir::modules::ModuleEditor::~ModuleEditor() {}

bool bluefir::modules::ModuleEditor::Init()
{
	LOGINFO("Initializing Editor.");

	// Set ImGui Config
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	// Init Imgui
	ImGui_ImplSDL2_InitForOpenGL(ModuleRenderer::getInstance().GetWindowData()->window, ModuleRenderer::getInstance().GetWindowData()->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	ImGui::StyleColorsDark();

	// Define editor camera
	go_editor_camera_ = new core::GameObject();
	go_editor_camera_->name = "Editor Cam";
	editor_camera_ = go_editor_camera_->AddComponent<core::Camera>();
	editor_camera_->ToEditorConfiguration();
	go_editor_camera_->transform->SetPosition(0, 1.0F, 10.0F);
	go_editor_camera_->transform->SetRotation(0, 0.0F, 0);

	// register all editor panels
	panels_.push_back(new editor::PanelTime());
	panels_.push_back(new editor::PanelRenderer());
	panels_.push_back(new editor::PanelScene());
	panels_.push_back(new editor::PanelInspector());
	panels_.push_back(new editor::PanelConsole());
	panels_.push_back(new editor::PanelTexture());
	panels_.push_back(new editor::PanelEditorView());

	// Init all panels
	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		(*it)->Init();

	return true;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::PreUpdate()
{
	go_editor_camera_->PreUpdate();

	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::Update()
{
	go_editor_camera_->Update();

	//ModuleRenderer::getInstance().Render();
	//modules::ModuleRenderer::getInstance().RenderCamera(editor_camera_);
	//editor_camera_->UnBind();

	modules::ModuleRenderer::getInstance().RenderCamera(editor_camera_);
	editor_camera_->UnBind();

	// Create new imgui editor frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(ModuleRenderer::getInstance().GetWindowData()->window);
	ImGui::NewFrame();

	// Draw UI
	if (!MainMenu()) return UpdateState::Update_End;
	CreateDockingSpace();

	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		(*it)->Draw();


	return UpdateState::Update_Continue;
}

bluefir::modules::UpdateState bluefir::modules::ModuleEditor::PostUpdate()
{
	go_editor_camera_->PostUpdate();
	//modules::ModuleRenderer::getInstance().RenderCamera(editor_camera_);

	// Render Imgui editor
	graphics::Graphics::ClearViewport();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	return UpdateState::Update_Continue;
}

bool bluefir::modules::ModuleEditor::CleanUp()
{
	LOGINFO("Closing Editor.");
	// CleanUp all registered panels
	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		(*it)->CleanUp();

	// Delete all registered panels
	for (auto it = panels_.begin(); it != panels_.end(); ++it)
		delete (*it);

	delete go_editor_camera_; go_editor_camera_ = nullptr;

	// Shut down Imgui
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

	// Create an entry for all registered panels under 'Windows' menu
	if (ImGui::BeginMenu("Windows"))
	{
		for (auto it = panels_.begin(); it != panels_.end(); ++it)
			ImGui::MenuItem((*it)->name_.c_str(), NULL, &(*it)->enabled_);
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	return true;
}

void bluefir::modules::ModuleEditor::CreateDockingSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.0F);
	bool p_open = true;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0F);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruDockspace;
	ImGui::DockSpace(dockspace_id, ImVec2(0.0F, 0.0F), dockspace_flags);
	ImGui::End();
}
