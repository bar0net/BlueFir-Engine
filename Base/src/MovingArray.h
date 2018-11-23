#ifndef BF_BASE_MOVINGARRAY_H
#define BF_BASE_MOVINGARRAY_H

#include <cstring>

namespace bluefir::base
{
	template <class T>
	class MovingArray
	{
	public:
		MovingArray(unsigned int size, T default_value) : size(size)
		{
			values = new T[size];
			std::memset(values, default_value, size * sizeof(T));
		}

		virtual ~MovingArray() { delete[] values; values = nullptr; }

		T& operator[](unsigned int x)
		{
			if (x < idx) return values[idx - x - 1];
			else return values[size + idx - x - 1];
		}

		void Push(T x)
		{
			values[idx] = x;
			if (++idx == size) idx = 0U;
		}

		float Get(void* data, int x) { return (float)(*(MovingArray*)data)[x]; }

	private:
		T* values = nullptr;
		unsigned int idx = 0U;
		unsigned int size = 0U;
	};
}

#endif // !BF_BASE_MOVINGARRAY_H

