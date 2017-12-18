#include "StaticAnalysis.h"

bool StaticAnalysis::isRegexMatched(std::string code, std::string pattern)
{
	std::regex regexPattern(pattern, std::regex_constants::icase);
	if (std::regex_match(code, regexPattern)) {
		return true;
	}
	return false;
}
