#ifndef BF_BASE_CHRONO_H
#define BF_BASE_CHRONO_H


namespace bluefir::base
{
	class Chrono
	{
	public:
		Chrono();
		virtual ~Chrono() {}

		void Start();
		unsigned int Pause() const;
		unsigned int Stop();

		unsigned int start_time_ = 0U;
		unsigned int end_time_ = 0U;
	};


	static unsigned long long int frequency;
	class uChrono
	{
	public:
		uChrono();
		virtual ~uChrono() {}

		void Start();
		float Pause() const;
		float Stop();

		unsigned long long int start_time_ = 0U;
		unsigned long long int end_time_ = 0U;
	};
}

#endif // !BF_BASE_CHRONO_H

