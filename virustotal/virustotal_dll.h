/*
SWAMI KARUPPASWAMI THUNNAI
===========================
Author     : Visweswaran Nagasivam
Email      : visweswaran.nagasivam98@gmail.com
Date	   : 16.12.2017

Description:
=============
This .h file is just a wrapper for exporting the classes as a dll
*/
#pragma once
#include<string>

/*
Export the functions
*/
__declspec(dllexport) std::string get_results_for_hash(std::string api_key, std::string hash);
__declspec(dllexport) std::string get_results_for_url(std::string api_key, std::string url);


std::string get_results_for_hash(std::string api_key, std::string hash);
std::string get_results_for_url(std::string api_key, std::string url);