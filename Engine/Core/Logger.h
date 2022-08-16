#pragma once

#ifdef _DEBUG
	#define LOG(format, ...) jemgine::g_logger.Log(format, __VA_ARGS__)
#else
	#define LOG(format, ...) ((void)0)
#endif //_DEBUG
namespace jemgine
{

	class Logger
	{
	public:
		Logger() = default;
		~Logger() = default;

		void Log(const char* format, ...);
	private:

	};
	
	extern Logger g_logger;
}