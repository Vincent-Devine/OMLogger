#include "../../OMLogger/Logger.hpp"

int main()
{
	OM::Logger::OpenFile("log.txt");
	LOG_INFO("info message");
	LOG_VALIDATION("validation message");
	LOG_DEBUG("debug message");
	LOG_WARNING("warning message");
	LOG_ERROR("error message");
	OM::Logger::CloseFile();
}