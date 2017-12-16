/*
SWAMI KARUPPASWAMI THUNNAI
Author       : Visweswaran Nagasivam
Date         : 11.12.2017
Copyright(C) : 2017
License      : GPL v2.0
*/
#pragma once
#include<string>

class URL
{
protected:
	std::string get_request(std::string url);
	std::string post_request(std::string domain, std::string relative_path, std::string params);
};
