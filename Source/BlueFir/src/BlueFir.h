#ifndef BLUE_FIR_H
#define BLUE_FIR_H

#include <vector>

namespace bluefir
{
	namespace modules
	{
		class Module;
		class ModuleEvents;
		class ModuleRenderer;
		class ModuleTime;
		class ModuleScene;
		class ModuleEditor;
		class ModuleTexture;
		class ModuleResources;
	}

	class BlueFir
	{
	public:
		BlueFir();
		virtual ~BlueFir();

		bool Start();
		bool Update();
		bool End();

	public:
		modules::ModuleEvents* input = nullptr;
		modules::ModuleRenderer* renderer = nullptr;
		modules::ModuleTime* time = nullptr;
		modules::ModuleScene* scene = nullptr;
		modules::ModuleEditor* editor = nullptr;
		modules::ModuleTexture* texture = nullptr;
		modules::ModuleResources* resources = nullptr;

	private:
		std::vector<modules::Module*> modules_;
	};
}
extern bluefir::BlueFir* App;

#endif // !BLUE_FIR_H

