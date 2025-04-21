#include "../../OMLogger/Logger.hpp"

const unsigned int PERFORMANCE_TEST_ITERATIONS = 50000;
const std::string LOREM_IPSUM = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut.";


void PerformanceTest()
{
	auto start = std::chrono::high_resolution_clock::now();

	for (unsigned int i = 0; i < PERFORMANCE_TEST_ITERATIONS; i++)
	{
		OM_LOG_DEBUG("Iterations: " + std::to_string(i));
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	OM_LOG_INFO(std::to_string(PERFORMANCE_TEST_ITERATIONS) + " iterations in " + std::to_string(elapsed.count()) + " seconds");
}

void LogFile()
{
	// Begin of the project
	OM::Logger::Logger* logger = OM::Logger::Logger::GetInstance();
	logger->OpenLogFile("log.txt");

	OM_LOG_DEBUG("message written to console and log file");

	// End of the project
	logger->CloseLogFile();
}

void Log()
{
	OM_LOG_DEBUG(LOREM_IPSUM);
	OM_LOG_INFO(LOREM_IPSUM);
	OM_LOG_WARNING(LOREM_IPSUM);
	OM_LOG_ERROR(LOREM_IPSUM);
	OM_LOG_CRITICAL(LOREM_IPSUM);
}

void LogWithTag()
{
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagEngine);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagCore);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagRender);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagInput);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagPhysics);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagAudio);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagAnimation);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagUI);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagAI);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagResource);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagScripting);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagTools);
	OM_LOG_INFO_TAG(LOREM_IPSUM, OM::Logger::TagScene);
}

void DisplaySettings()
{
	OM::Logger::Logger* logger = OM::Logger::Logger::GetInstance();

	logger->SetDisplaySettings(OM::Logger::DisplayNone);
	OM_LOG_INFO("Display only message");

	logger->SetDisplaySettings(OM::Logger::DisplayDate);
	OM_LOG_INFO("Display only date + message");

	logger->SetDisplaySettings(OM::Logger::DisplayThread);
	OM_LOG_INFO("Display only thread + message");

	logger->SetDisplaySettings(OM::Logger::DisplayFileInfo);
	OM_LOG_INFO("Display only file info + message");

	logger->SetDisplaySettings(OM::Logger::DisplayVerbosity);
	OM_LOG_INFO("Display only verbosity + message");

	logger->SetDisplaySettings(OM::Logger::DisplayTag);
	OM_LOG_INFO_TAG("Display only tag + message", OM::Logger::TagCore);

	logger->SetDisplaySettings(OM::Logger::DisplayDate | OM::Logger::DisplayFileInfo);
	OM_LOG_INFO("Display Date + File info + message");

	logger->SetDisplaySettings(OM::Logger::DisplayAll);
	OM_LOG_INFO("Display all info (date, thread, file info, verbosity, tag) + message");
}

void Verbosity()
{
	OM::Logger::Logger* logger = OM::Logger::Logger::GetInstance();

	logger->SetVerbosity(OM::Logger::VerbosityNone);
	OM_LOG_DEBUG("No log");
	OM_LOG_INFO("No log");
	OM_LOG_WARNING("No log");
	OM_LOG_ERROR("No log");
	OM_LOG_CRITICAL("No log");

	logger->SetVerbosity(OM::Logger::VerbosityDebug);
	OM_LOG_DEBUG("Only debug verbosity");
	OM_LOG_INFO("Only debug verbosity");
	OM_LOG_WARNING("Only debug verbosity");
	OM_LOG_ERROR("Only debug verbosity");
	OM_LOG_CRITICAL("Only debug verbosity");

	logger->SetVerbosity(OM::Logger::VerbosityInfo);
	OM_LOG_DEBUG("Only info verbosity");
	OM_LOG_INFO("Only info verbosity");
	OM_LOG_WARNING("Only info verbosity");
	OM_LOG_ERROR("Only info verbosity");
	OM_LOG_CRITICAL("Only info verbosity");

	// Only warning verbosity
	logger->SetVerbosity(OM::Logger::VerbosityWarning);
	OM_LOG_DEBUG("Only warning verbosity");
	OM_LOG_INFO("Only warning verbosity");
	OM_LOG_WARNING("Only warning verbosity");
	OM_LOG_ERROR("Only warning verbosity");
	OM_LOG_CRITICAL("Only warning verbosity");

	logger->SetVerbosity(OM::Logger::VerbosityError);
	OM_LOG_DEBUG("Only error verbosity");
	OM_LOG_INFO("Only error verbosity");
	OM_LOG_WARNING("Only error verbosity");
	OM_LOG_ERROR("Only error verbosity");
	OM_LOG_CRITICAL("Only error verbosity");

	logger->SetVerbosity(OM::Logger::VerbosityCritical);
	OM_LOG_DEBUG("Only critical verbosity");
	OM_LOG_INFO("Only critical verbosity");
	OM_LOG_WARNING("Only critical verbosity");
	OM_LOG_ERROR("Only critical verbosity");
	OM_LOG_CRITICAL("Only critical verbosity");

	logger->SetVerbosity(OM::Logger::VerbosityCritical | OM::Logger::VerbosityError);
	OM_LOG_DEBUG("Only critical and error verbosity");
	OM_LOG_INFO("Only critical and error verbosity");
	OM_LOG_WARNING("Only critical and error verbosity");
	OM_LOG_ERROR("Only critical and error verbosity");
	OM_LOG_CRITICAL("Only critical and error verbosity");

	logger->SetVerbosity(OM::Logger::VerbosityAll);
	OM_LOG_DEBUG("All verbosity (debug, info, warning, error, critical)");
	OM_LOG_INFO("All verbosity (debug, info, warning, error, critical)");
	OM_LOG_WARNING("All verbosity (debug, info, warning, error, critical)");
	OM_LOG_ERROR("All verbosity (debug, info, warning, error, critical)");
	OM_LOG_CRITICAL("All verbosity (debug, info, warning, error, critical)");
}

void Assertion()
{
	// If #define _DEBUG , log (critical verbosity) + breakpoint
	// Else, log (critical verbosity) + abort
	
	OM_ASSERTION(1 + 1 == 2, "Message log"); // pass
	OM_ASSERTION(1 + 1 == 3, "Message log"); // not pass
}

int main()
{
	LogFile();

	Log();
	LogWithTag();

	DisplaySettings();
	Verbosity();

	// Assertion();

	// I made my own profil for the One More project (with the One More Engine)
	// Fill free to create your own profil
	OM::Logger::Logger::GetInstance()->SetOMProfile();
	OM_LOG_INFO("One More project profil");

	// Run 50 000 time debug log
	// PerformanceTest(); 
	
	// Need to be call at the end of the program
	OM::Logger::Logger::GetInstance()->Destroy();
	return 0;
}