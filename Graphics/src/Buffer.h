#ifndef BF_GRAPHICS_BUFFER_H
#define BF_GRAPHICS_BUFFER_H

#include "Graphics.h"

namespace bluefir::graphics
{
	class GLBuffer
	{
	public:
		GLBuffer() {}
		virtual ~GLBuffer() = 0;

		virtual void Bind() const	= 0;
		virtual void UnBind() const = 0;

	protected:
		unsigned int idx = 0U;
	};
}

#endif // !BF_GRAPHICS_BUFFER_H

