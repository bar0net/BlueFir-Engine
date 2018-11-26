#ifndef BF_BASE_MOVINGARRAY_H
#define BF_BASE_MOVINGARRAY_H

#include <cstring>

namespace bluefir::base
{
	template <class T>
	class MovingArray
	{
		static_assert(std::is_arithmetic_v<T>);

	public:
		MovingArray(unsigned int size, T default_value) : size_(size)
		{
			values_ = new T[size];
			std::memset(values_, default_value, size * sizeof(T));
		}
		MovingArray(MovingArray const&) = delete;
		void operator=(MovingArray const&) = delete;

		virtual ~MovingArray() { delete[] values_; values_ = nullptr; }

		T& operator[](unsigned int x)
		{
			if (x < idx_) return values_[idx_ - x - 1];
			else return values_[size_ + idx_ - x - 1];
		}

		void Push(T x)
		{
			values_[idx_] = x;
			if (++idx_ == size_) idx_ = 0U;
		}

		float Get(void* data, int x) { return (float)(* static_cast<MovingArray*>(data) )[x]; }

	private:
		T* values_ = nullptr;
		unsigned int idx_ = 0U;
		unsigned int size_ = 0U;
	};
}

#endif // !BF_BASE_MOVINGARRAY_H

