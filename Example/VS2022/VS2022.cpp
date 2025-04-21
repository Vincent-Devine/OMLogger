#include "../../OMLogger/Logger.hpp"

const unsigned int PERFORMANCE_TEST_ITERATIONS = 50000;

void PerformanceTest()
{
	auto start = std::chrono::high_resolution_clock::now();

	for (unsigned int i = 0; i < PERFORMANCE_TEST_ITERATIONS; i++)
	{
		OM_LOG_DEBUG("Iterations: " + std::to_string(i));
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	OM_LOG_INFO(std::to_string(PERFORMANCE_TEST_ITERATIONS) + " iteractions in " + std::to_string(elapsed.count()) + " secondes");
}

int main()
{
	OM::Logger::Logger* logger = OM::Logger::Logger::GetInstance();
	logger->OpenLogFile("log.txt");

	std::string loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut.";

	logger->SetVerbosity(OM::Logger::VerbosityInfo);
	logger->SetDisplaySettings(OM::Logger::DisplayNone);
	PerformanceTest();
	
	logger->SetOMProfil();

	OM_LOG_DEBUG(loremIpsum);
	OM_LOG_INFO(loremIpsum);
	OM_LOG_WARNING(loremIpsum);
	OM_LOG_ERROR(loremIpsum);
	OM_LOG_CRITICAL(loremIpsum);

	OM_LOG_INFO_TAG(loremIpsum, OM::Logger::TagCore);
	OM_LOG_DEBUG_TAG(loremIpsum, OM::Logger::TagEngine);
	OM_LOG_WARNING_TAG(loremIpsum, OM::Logger::TagRender);
	OM_LOG_ERROR_TAG(loremIpsum, OM::Logger::TagAnimation);
	OM_LOG_CRITICAL_TAG(loremIpsum, OM::Logger::TagAI);
	OM_LOG_INFO_TAG(loremIpsum, OM::Logger::TagScripting);

	OM_LOG_DEBUG(loremIpsum);
	OM_LOG_INFO(loremIpsum);
	OM_LOG_WARNING(loremIpsum);
	OM_LOG_ERROR(loremIpsum);
	OM_LOG_CRITICAL(loremIpsum);

	logger->CloseLogFile();
	logger->Destroy();

	return 0;
}