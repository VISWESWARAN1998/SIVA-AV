/*
SWAMI KARUPPASWAMI THUNNAI
Author       : Visweswaran Nagasivam
Date         : 11.12.2017
Copyright(C) : 2017
License      : GPL v2.0
*/
#pragma once

#include"url.h"
#include<string>

/*
This class is used to query virustotal for all related informations
*/
class VirusTotal : protected URL
{
private:
	std::string api_key;
public:
	VirusTotal(std::string api_key);
	std::string get_result_for_hash(std::string hash);
	std::string get_result_for_url(std::string url);
};
