#pragma once
#include <string>

static class LogHandler
{
public:
	static void LogError(const std::string & const error);
	static void LogMessage(const std::string& const message);
};

