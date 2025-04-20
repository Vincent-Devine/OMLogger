#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <mutex>
#include <thread>
#include <chrono>
#include <Windows.h>

namespace OM::Logger
{
	enum LogLevel : uint8_t
	{
		None		= 0,
		Debug		= 1 << 0,
		Info		= 1 << 1,
		Warning		= 1 << 2,
		Error		= 1 << 3,
		Critical	= 1 << 4,
		All			= Debug | Info | Warning | Error | Critical
	};

	enum LogOutputSettings : uint8_t
	{
		ShowNone		= 0,
		ShowDate		= 1 << 0,
		ShowThread		= 1 << 1,
		ShowFileInfo	= 1 << 2,
		ShowAll			= ShowDate | ShowThread | ShowFileInfo
	};

	class Logger
	{
		// Attributes
	private:
		static inline Logger* s_instance = nullptr;

		std::mutex m_mutex;
		std::ofstream m_logFile;
		uint8_t m_level = LogLevel::All;
		uint8_t m_outputSettings = LogOutputSettings::ShowAll;

		// Methods
	public:
		static Logger* GetInstance()
		{
			if (!s_instance)
				s_instance = new Logger();
			return s_instance;
		}

		void OpenLogFile(const std::filesystem::path& path)
		{
			std::scoped_lock lock(m_mutex);
			if (m_logFile.is_open())
				m_logFile.close();
			m_logFile.open(path, std::ios::out | std::ios::app);
		}

		void CloseLogFile()
		{
			if (m_logFile.is_open())
				m_logFile.close();
		}

		void Log(uint8_t level, const char* file, int line, const char* function, const std::string& message)
		{
			if (!(m_level & level))
				return;

			std::ostringstream out;

			if (m_outputSettings & LogOutputSettings::ShowDate)
			{
				auto now = std::chrono::system_clock::now();
				auto timeTNow = std::chrono::system_clock::to_time_t(now);
				std::tm localTime;
				localtime_s(&localTime, &timeTNow);
				out << '[' << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] ";
			}

			if(m_outputSettings & LogOutputSettings::ShowThread)
				out << "[Thread ID " << std::this_thread::get_id() << "] ";

			if (m_outputSettings & LogOutputSettings::ShowFileInfo)
			{
				const char* filename = std::strrchr(file, '\\');
				filename = filename ? filename + 1 : file;
				out << '[' << filename << ':' << function << '@' << line << "] ";
			}

			out << LogLevelToString(level) << " ";

			std::string logInfo = out.str(); // only colored part

			PrintConsole(logInfo, message, level);
			WriteFile(logInfo + message);
		}

		void SetOutputSettings(uint8_t outputSettings) { m_outputSettings = outputSettings; }
		void SetLevel(uint8_t level) { m_level = level; }

	private:
		Logger() = default;
		~Logger()
		{
			CloseLogFile();
			delete s_instance;
		}

		void PrintConsole(const std::string& logInfo, const std::string& message, const uint8_t level)
		{
			static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			std::scoped_lock lock(m_mutex);

			WORD color = 7; // default grey
			switch (level)
			{
			case LogLevel::Debug:	color = 13; break;	// purple
			case LogLevel::Info:	color = 11; break;	// cyan
			case LogLevel::Warning: color = 14; break;	// yellow
			case LogLevel::Error:	color = 12; break;	// red
			case LogLevel::Critical:color = 79; break;	// white on red background
			default: break;
			}

			SetConsoleTextAttribute(handle, color);
			std::cout << logInfo;
			SetConsoleTextAttribute(handle, 7);
			std::cout << message << std::endl;
		}

		void WriteFile(const std::string& message)
		{
			std::scoped_lock lock(m_mutex);
			if (m_logFile.is_open())
				m_logFile << message << '\n';
		}

		const char* LogLevelToString(uint8_t level)
		{
			switch (level)
			{
			case LogLevel::Debug: return "[DEBUG]   ";
			case LogLevel::Info: return "[INFO]    ";
			case LogLevel::Warning: return "[WARNING] ";
			case LogLevel::Error: return "[ERROR]   ";
			case LogLevel::Critical: return "[CRITICAL]";
			default: return "[UNKNOWN] ";
			}
		}
	};
}

// Print
#define OM_LOG_DEBUG(message) OM::Logger::Logger::GetInstance()->Log(OM::Logger::LogLevel::Debug,		__FILE__, __LINE__, __func__, message);
#define OM_LOG_INFO(message) OM::Logger::Logger::GetInstance()->Log(OM::Logger::LogLevel::Info,			__FILE__, __LINE__, __func__, message);
#define OM_LOG_WARNING(message) OM::Logger::Logger::GetInstance()->Log(OM::Logger::LogLevel::Warning,	__FILE__, __LINE__, __func__, message);
#define OM_LOG_ERROR(message) OM::Logger::Logger::GetInstance()->Log(OM::Logger::LogLevel::Error,		__FILE__, __LINE__, __func__, message);
#define OM_LOG_CRITICAL(message) OM::Logger::Logger::GetInstance()->Log(OM::Logger::LogLevel::Critical,	__FILE__, __LINE__, __func__, message);

// Setup
#define OM_LOG_OPEN_LOG_FILE(filePath) OM::Logger::Logger::GetInstance()->OpenLogFile(filePath);
#define OM_LOG_CLOSE_LOG_FILE() OM::Logger::Logger::GetInstance()->CloseLogFile();
#define OM_LOG_OUTPUT_LEVEL(level) OM::Logger::Logger::GetInstance()->SetLevel(level);
#define OM_LOG_OUTUP_SETTING(flags) OM::Logger::Logger::GetInstance()->SetOutputSettings(flags);

#define OM_LOG_SETTINGS_LEVEL_DEBUG		OM::Logger::LogLevel::Debug
#define OM_LOG_SETTINGS_LEVEL_INFO		OM::Logger::LogLevel::Info
#define OM_LOG_SETTINGS_LEVEL_WARNING	OM::Logger::LogLevel::Warning
#define OM_LOG_SETTINGS_LEVEL_ERROR		OM::Logger::LogLevel::Error
#define OM_LOG_SETTINGS_LEVEL_CRITICAL	OM::Logger::LogLevel::Critical
#define OM_LOG_SETTINGS_LEVEL_NONE		OM::Logger::LogLevel::None
#define OM_LOG_SETTINGS_LEVEL_ALL		OM::Logger::LogLevel::All

#define OM_LOG_SETTINGS_SHOW_DATE		OM::Logger::LogOutputSettings::ShowDate
#define OM_LOG_SETTINGS_SHOW_THREAD		OM::Logger::LogOutputSettings::ShowThread
#define OM_LOG_SETTINGS_SHOW_FILE_INFO	OM::Logger::LogOutputSettings::ShowFileInfo
#define OM_LOG_SETTINGS_SHOW_NONE		OM::Logger::LogOutputSettings::ShowNone
#define OM_LOG_SETTINGS_SHOW_ALL		OM::Logger::LogOutputSettings::ShowAll

// Assertion
#ifdef _DEBUG
#define OM_ASSERTION(expression, message) if(!(expression)) { OM_LOG_CRITICAL(message); __debugbreak(); }
#else
#define OM_ASSERTION(expression, message) if(!(expression)) { OM_LOG_CRITICAL(message); abort(); }
#endif