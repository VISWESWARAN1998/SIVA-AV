/* 
SWAMI KARUPPASWAMI THUNNAI
===========================
Author     : Visweswaran Nagasivam
Email      : visweswaran.nagasivam98@gmail.com
Date	   : 16.12.2017

Description:
=============
This .cpp file is just a wrapper for exporting the classes as a dll
*/


#include<fstream>
#include "virustotal.h"
#include "virustotal_dll.h"

std::string get_results_for_hash(std::string api_key, std::string hash)
{
	VirusTotal virustotal(api_key);
	std::string result = virustotal.get_result_for_hash(hash);
	return result;
}

std::string get_results_for_url(std::string api_key, std::string url)
{
	VirusTotal virustotal(api_key);
	std::string result = virustotal.get_result_for_url(url);
	return url;
}


