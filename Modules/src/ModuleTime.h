#ifndef BF_MODULE_TIME
#define BF_MODULE_TIME

#include "Module.h"
#include "Chrono.h"

namespace bluefir::modules
{
	class ModuleTime : public Module 
	{
	public:
		bool Init() override			 { chrono.Start(); return true; }
		UpdateState PreUpdate() override { real_last_ = chrono.Pause(); return UpdateState::Update_Continue; }
		bool CleanUp() override			 { chrono.Stop(); return true; }

		// Real
		float RealTime() const		{ return (float)chrono.Pause() / 1000.0F; }
		float RealDeltaTime() const { return (float)(chrono.Pause() - real_last_) / 1000.0F; }

		// UnScaled
		float UnscaledTime() const		{ return (float)unscaled_running_time_ / 1000.0F;  }
		float UnscaledDeltaTime() const { return active_ ? (float)(chrono.Pause() - real_last_) / 1000.0F : 0; }

		// Scaled
		float Time() const		{ return (float)running_time_ / 1000.0F; }
		float DeltaTime() const { return active_ ? (float)(chrono.Pause() - real_last_) * time_scale_ / 1000.0F : 0; };

		// ----

		void StartTimers() { active_ = true; }
		void PauseTimers() { active_ = false; }
		void StopTimers()  { active_ = false; running_time_ = 0U; unscaled_running_time_ = 0U; }

		void SetTimeScale(float scale)  { if (scale >= 0) time_scale_ = scale; }
		float GetTimeScale() const		{ return time_scale_; }

	private:
		base::Chrono chrono;

		bool active_ = false;
		float time_scale_ = 1.0F;

		unsigned int real_last_ = 0U;
		unsigned long int running_time_ = 0U;
		unsigned long int unscaled_running_time_ = 0U;

	};
}

#endif // !BF_MODULE_TIME
