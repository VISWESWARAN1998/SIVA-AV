/*
SWAMI KARUPPASWAMI THUNNAI
Author       : Visweswaran Nagasivam
Date         : 11.12.2017
Copyright(C) : 2017
License      : GPL v2.0
*/

#include<iostream>
#include<Windows.h>
#include "virustotal.h"

VirusTotal::VirusTotal(std::string api_key)
{
	this->api_key = api_key;
}

std::string VirusTotal::get_result_for_hash(std::string hash)
{
	std::string payload = "apikey=" + api_key + "&resource=" + hash;
	std::string  result = post_request("http://www.virustotal.com", "/vtapi/v2/file/report", payload);
	return result;
}

std::string VirusTotal::get_result_for_url(std::string url)
{
	std::string payload = "apikey=" + api_key + "&url=" + url;
	std::string result = post_request("http://www.virustotal.com", "/vtapi/v2/url/scan", payload);
	/* Will check if the scan is in queued, and query the server*/
	while (result.find("Scan request successfully queued") != std::string::npos)
	{
		Sleep(20000);
		result = post_request("http://www.virustotal.com", "/vtapi/v2/url/report", "apikey=" + api_key + "&resource=" + url);
	}
	return result;
}
