#include "PanelConsole.h"

#include "../../Vendor/imgui-docking/imgui.h"

#define DISABLEDTEXT_COLOR ImVec4(0.7F, 0.7F, 0.7F, 1.0F)
#define DISABLED_COLOR ImVec4(0.5F, 0.5F, 0.5F, 1.0F)
#define DISABLED_HIGHLIGHT_COLOR ImVec4(0.6F, 0.6F, 0.6F, 1.0F)

#define NONE_COLOR ImVec4(0.0F, 1.0F, 0.0F, 1.0F)
#define DEBUG_COLOR ImVec4(0.0F, 1.0F, 1.0F, 1.0F)
#define INFO_COLOR ImVec4(1.0F, 1.0F, 1.0F, 1.0F)
#define WARNING_COLOR ImVec4(1.0F, 1.0F, 0.0F, 1.0F)
#define ERROR_COLOR ImVec4(1.0F, 0.0F, 0.0F, 1.0F)

void bluefir::editor::PanelConsole::Init()
{
#if(BF_DEBUG)
	LOGDEBUG("Console: Test debug level display.");
	LOGINFO("Console: Test info level display.");
	LOGWARNING("Console: Test warning level display.");
	LOGERROR("Console: Test error level display.");
#endif
}

void bluefir::editor::PanelConsole::Draw()
{
	if (!enabled_) return;
	int style_count = 0;

	ImGui::Begin("Console", &enabled_);
	
	// Set up buttons
	if (ImGui::Button("Clear"))		base::LogSystem::getInstance().Clear();
	ImGui::SameLine();

	style_count = SetButtonStyle(base::LogLevel::Debug);
	if (ImGui::Button("Debug"))		{ show_level_[(int)base::LogLevel::Debug] = !show_level_[(int)base::LogLevel::Debug]; prev_log_size_ = 0; }
	ImGui::SameLine();
	ImGui::PopStyleColor(style_count);

	style_count = SetButtonStyle(base::LogLevel::Info);
	if (ImGui::Button("Info"))		{ show_level_[(int)base::LogLevel::Info] =	!show_level_[(int)base::LogLevel::Info]; prev_log_size_ = 0; }
	ImGui::SameLine();
	ImGui::PopStyleColor(style_count);

	style_count = SetButtonStyle(base::LogLevel::Warning);
	if (ImGui::Button("Warning"))	{ show_level_[(int)base::LogLevel::Warning] =	!show_level_[(int)base::LogLevel::Warning]; prev_log_size_ = 0; }
	ImGui::SameLine();
	ImGui::PopStyleColor(style_count);

	style_count = SetButtonStyle(base::LogLevel::Error);
	if (ImGui::Button("Error"))		{ show_level_[(int)base::LogLevel::Error] =	!show_level_[(int)base::LogLevel::Error]; prev_log_size_ = 0; }
	ImGui::PopStyleColor(style_count);

	// Show Text
	if (ImGui::BeginChild("Scrolling"))
	{

		for (auto it = base::LogSystem::getInstance().history.begin(); it != base::LogSystem::getInstance().history.end(); ++it)
		{
			switch (it->type)
			{
			case base::LogLevel::Debug:
				if (show_level_[(int)base::LogLevel::Debug]) ImGui::TextColored(DEBUG_COLOR, it->message.c_str());
				break;
			case base::LogLevel::Info:
				if (show_level_[(int)base::LogLevel::Info]) ImGui::TextColored(INFO_COLOR, it->message.c_str());
				break;
			case base::LogLevel::Warning:
				if (show_level_[(int)base::LogLevel::Warning]) ImGui::TextColored(WARNING_COLOR, it->message.c_str());
				break;
			case base::LogLevel::Error:
				if (show_level_[(int)base::LogLevel::Error]) ImGui::TextColored(ERROR_COLOR, it->message.c_str());
				break;
			default:
				if (show_level_[(int)base::LogLevel::Info]) ImGui::TextColored(NONE_COLOR, it->message.c_str());
				break;
			}
		}

		// Set scrolling
		if (prev_log_size_ != (unsigned int)base::LogSystem::getInstance().history.size())
		{
			prev_log_size_ = (unsigned int)base::LogSystem::getInstance().history.size();
			ImGui::SetScrollHere();
		}
	}

	ImGui::EndChild();

	ImGui::End();
}

int bluefir::editor::PanelConsole::SetButtonStyle(base::LogLevel type)
{
	if (show_level_[(int)type])
	{
		switch (type)
		{
		case bluefir::base::LogLevel::Debug:
			ImGui::PushStyleColor(ImGuiCol_Text, DEBUG_COLOR);
			break;
		case bluefir::base::LogLevel::Info:
			ImGui::PushStyleColor(ImGuiCol_Text, INFO_COLOR);
			break;
		case bluefir::base::LogLevel::Warning:
			ImGui::PushStyleColor(ImGuiCol_Text, WARNING_COLOR);
			break;
		case bluefir::base::LogLevel::Error:
			ImGui::PushStyleColor(ImGuiCol_Text, ERROR_COLOR);
			break;
		default:
			ImGui::PushStyleColor(ImGuiCol_Text, NONE_COLOR);
			break;
		}
		return 1;
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Text, DISABLEDTEXT_COLOR);
		ImGui::PushStyleColor(ImGuiCol_Button, DISABLED_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, DISABLED_HIGHLIGHT_COLOR); 
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, DISABLED_HIGHLIGHT_COLOR);
		return 4;
	}

	return 0;
}
