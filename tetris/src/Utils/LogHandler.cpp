#include "LogHandler.hpp"

void LogHandler::LogError(const std::string& error)
{
	printf_s("Error: %s", error.c_str());
}

void LogHandler::LogMessage(const std::string& message)
{
	printf_s("Message: %s", message.c_str());
}