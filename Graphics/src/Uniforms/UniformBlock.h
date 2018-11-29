#ifndef BF_GRAPHICS_UNIFORMBLOCK
#define BF_GRAPHICS_UNIFORMBLOCK

#include "../Uniform.h"
#include "../Buffer/UniformBuffer.h"

// TODO: SEND TYPE?

namespace bluefir::graphics
{
	template <class T>
	class UniformBlock : public UniformedTyped<T>
	{
		static_assert(std::is_fundamental_v<T>);

	public:
		UniformBlock(int location, int offset, int size, unsigned int count, const UniformBuffer* ubo, UniformType type)
			: UniformedTyped(location, size, count, type, UniformPrimitive::NONE), offset_(offset), ubo_(ubo) { block_ = true; }

		virtual void Set(const void* data) const override { LOGERROR("Unsupported uniform type."); }

		int offset_ = 0;
		const UniformBuffer* ubo_ = nullptr;
	};

	template <>
	class UniformBlock<int> : public UniformedTyped<int>
	{
	public:
		UniformBlock<int>::UniformBlock(int location, int offset, int size, unsigned int count, const UniformBuffer* ubo, UniformType type)
			: UniformedTyped(location, size, count, type, UniformPrimitive::INT), offset_(offset), ubo_(ubo) { block_ = true; }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			ubo_->SetUniform(offset_, size_, data);
		}

		int offset_ = 0;
		const UniformBuffer* ubo_ = nullptr;
	};

	template <>
	class UniformBlock<float> : public UniformedTyped<float>
	{
	public:
		UniformBlock<float>::UniformBlock(int location, int offset, int size, unsigned int count, const UniformBuffer* ubo, UniformType type)
			: UniformedTyped(location, size, count, type, UniformPrimitive::INT), offset_(offset), ubo_(ubo) { block_ = true; }

		virtual void Set(const void* data) const override
		{
			ASSERT(data);
			ubo_->SetUniform(offset_, size_, data);
		}

		int offset_ = 0;
		const UniformBuffer* ubo_ = nullptr;
	};
}
#endif // !BF_GRAPHICS_UNIFORMBLOCK