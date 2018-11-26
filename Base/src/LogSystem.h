#ifndef BLUEFIR_BASE_LOGSYS_H
#define BLUEFIR_BASE_LOGSYS_H

#include <list>
#include <string>

#define LOG(x, ...)			bluefir::base::LogSystem::getInstance().Log(bluefir::base::LogLevel::None, __FILE__, __LINE__, x, __VA_ARGS__)
#define LOGDEBUG(x, ...)	bluefir::base::LogSystem::getInstance().Log(bluefir::base::LogLevel::Debug, __FILE__, __LINE__, x, __VA_ARGS__)
#define LOGINFO(x, ...)		bluefir::base::LogSystem::getInstance().Log(bluefir::base::LogLevel::Info, __FILE__, __LINE__, x, __VA_ARGS__)
#define LOGWARNING(x, ...)	bluefir::base::LogSystem::getInstance().Log(bluefir::base::LogLevel::Warning, __FILE__, __LINE__, x, __VA_ARGS__)
#define LOGERROR(x, ...)	bluefir::base::LogSystem::getInstance().Log(bluefir::base::LogLevel::Error, __FILE__, __LINE__, x, __VA_ARGS__)

namespace bluefir::base
{
	enum class LogLevel
	{
		None = 0,
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4
	};

	struct LogData
	{
	public:
		LogData(LogLevel type, const std::string& message) : type(type), message(message) {}

		LogLevel type = LogLevel::None;
		std::string message;
	};

	class LogSystem
	{
	public:
		// Singleton Pattern
		static LogSystem& getInstance() { static LogSystem instance; return instance; }
		LogSystem(LogSystem const&) = delete;
		void operator=(LogSystem const&) = delete;

		void SetLevel(LogLevel level) { this->level_ = level; }
		void Log(LogLevel level, const char* file, int line, const char* message...);
		void Clear() { history.clear(); }

	private:
		LogSystem() {}
		~LogSystem() {}

	public:
		std::list<LogData> history;

	private:
		LogLevel level_ = LogLevel::Debug;
	};
}

#endif // !BLUEFIR_BASE_LOGSYS_H

