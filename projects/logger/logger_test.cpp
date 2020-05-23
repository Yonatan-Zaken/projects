#include <iostream>
#include "logger_preprocessor.hpp"

int main()
{
	LOG_DEBUG("testing debug");
	LOG_INFO("testing info");
	LOG_WARNING("testing warning");
	LOG_ERROR("testing error");

	return 0;
}
