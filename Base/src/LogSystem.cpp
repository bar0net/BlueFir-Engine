#include "LogSystem.h"

#include <stdarg.h>

#if (BF_DEBUG)
	#include <iostream>
	#define PRINT(x) std::cout << x << std::endl;
#else
	#define PRINT(x)
#endif

void bluefir::base::LogSystem::Log(LogLevel level, const char * file, int line, const char *message ...)
{
	if (level < this->level_) return;
	std::string s = "";

	switch (level)
	{
	case LogLevel::Debug:
		s = "[Debug] <";
		break;
	case LogLevel::Info:
		s = "[Info] <";
		break;
	case LogLevel::Warning:
		s = "[Warning] <";
		break;
	case LogLevel::Error:
		s = "[Error] <";
		break;

	default:
		s = "[None] <";
		break;
	}
	s.append(file); s.append(":"); s += std::to_string(line); s.append("> ");
	s.append(message);

	va_list args;
	va_start(args, message);

	std::size_t i = 0U;
	while (true)
	{
		i = s.find('%', i + 1U);
		if (i == std::string::npos || s.size() < i + 1) break;

		switch (s[i + 1])
		{
		case 's':
			s = s.substr(0, i) + va_arg(args, char*) + s.substr(i + 2);
			break;

		case 'd':
			s = s.substr(0, i) + std::to_string(va_arg(args, int)) + s.substr(i + 2);
			break;

		case 'i':
			s = s.substr(0, i) + std::to_string(va_arg(args, int)) + s.substr(i + 2);
			break;

		case 'f':
			s = s.substr(0, i) + std::to_string(va_arg(args, double)) + s.substr(i + 2);
			break;

		default:
			break;
		}
	}
	va_end(args);

	PRINT(s);
	history.emplace_back(level, s);
	s.clear();
}
