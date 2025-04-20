#include "../../OMLogger/Logger.hpp"

const unsigned int PERFORMANCE_TEST_ITERATIONS = 2;

double PerformanceTestv2()
{
	auto start = std::chrono::high_resolution_clock::now();

	for (unsigned int i = 0; i < PERFORMANCE_TEST_ITERATIONS; i++)
	{
		OM_LOG_DEBUG("Iterations: " + std::to_string(i));
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	return elapsed.count();
}

int main()
{
	OM_LOG_OPEN_LOG_FILE("logfile.txt");
	double timev2 = PerformanceTestv2();

	OM_LOG_DEBUG("debug");
	OM_LOG_INFO("info");
	OM_LOG_WARNING("warning");
	OM_LOG_ERROR("error");
	OM_LOG_CRITICAL("critical");

	OM_LOG_OUTUP_SETTING(OM_LOG_SETTINGS_SHOW_DATE);
	OM_LOG_INFO("only date");
	OM_LOG_OUTUP_SETTING(OM_LOG_SETTINGS_SHOW_DATE | OM_LOG_SETTINGS_SHOW_FILE_INFO);
	OM_LOG_INFO("date + file info");
	OM_LOG_OUTUP_SETTING(OM_LOG_SETTINGS_SHOW_DATE | OM_LOG_SETTINGS_SHOW_THREAD);
	OM_LOG_INFO("date + thread");

	OM_LOG_OUTUP_SETTING(OM_LOG_SETTINGS_SHOW_NONE);
	OM_LOG_INFO("none");

	OM_LOG_OUTUP_SETTING(OM_LOG_SETTINGS_SHOW_ALL);
	OM_LOG_INFO("all");

	OM_LOG_OUTPUT_LEVEL(OM_LOG_SETTINGS_LEVEL_WARNING | OM_LOG_SETTINGS_LEVEL_INFO);
	OM_LOG_INFO("info");
	OM_LOG_WARNING("warning");
	OM_LOG_ERROR("error");
	OM_LOG_CRITICAL("critical");
	OM_LOG_OUTPUT_LEVEL(OM_LOG_SETTINGS_LEVEL_NONE);
	OM_LOG_INFO("info");
	OM_LOG_WARNING("warning");
	OM_LOG_ERROR("error");
	OM_LOG_CRITICAL("critical");
	OM_LOG_OUTPUT_LEVEL(OM_LOG_SETTINGS_LEVEL_ALL);
	OM_LOG_INFO("info");
	OM_LOG_WARNING("warning");
	OM_LOG_ERROR("error");
	OM_LOG_CRITICAL("critical");

	OM_LOG_INFO("Execution time v2 for " + std::to_string(PERFORMANCE_TEST_ITERATIONS) + " iterations: " + std::to_string(timev2) + " seconds");

	OM_ASSERTION(1 + 1 == 2, "big brain");
	// OM_ASSERTION(1 + 2 == 2, "aled les maths");

	OM_LOG_CLOSE_LOG_FILE();
}