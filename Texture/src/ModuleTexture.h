#ifndef BF_MODULES_TEXTURE
#define BR_MODULES_TEXTURE

#include "Module.h"
#include <unordered_map>

namespace bluefir::graphics
{
	class TextureBuffer;
}

namespace bluefir::modules
{
	class ModuleTexture : public Module
	{
	public:
		static ModuleTexture& getInstance() { static ModuleTexture instance_; return instance_; }

		// Flow
		virtual bool CleanUp() override;

		// Texture Management
		int LoadTexture(const char* filename);
		const graphics::TextureBuffer*  GetTextureBuffer(int id);
		bool RemoveTexture(int id);

	private:
		std::unordered_map<int, const graphics::TextureBuffer* > textures_;

		//friend 
	};

}
#endif // !BF_MODULES_TEXTURE

