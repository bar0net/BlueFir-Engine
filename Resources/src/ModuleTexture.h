#ifndef BF_MODULES_TEXTURE
#define BR_MODULES_TEXTURE

#include "Module.h"
#include <unordered_map>
#include <string>

namespace bluefir::graphics
{
	class TextureBuffer;
}

namespace bluefir::editor
{
	class PanelTexture;
}

namespace bluefir::modules
{
	class ModuleTexture : public Module
	{
	public:
		static ModuleTexture& getInstance() { static ModuleTexture instance_; return instance_; }

		// Flow
		virtual bool Init() override;
		virtual bool CleanUp() override;

		// Texture Management
		int LoadTexture(const char* filename);
		const graphics::TextureBuffer*  GetTextureBuffer(int id);
		bool RemoveTexture(int id);

	private:
		std::unordered_map<int, const graphics::TextureBuffer* > textures_;
		std::unordered_map<std::string, int> texture_names_;


		friend bluefir::editor::PanelTexture;
	};

}
#endif // !BF_MODULES_TEXTURE

