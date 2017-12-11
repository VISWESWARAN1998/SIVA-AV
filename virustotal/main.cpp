/*
SWAMI KARUPPASWAMI THUNNAI
Author       : Visweswaran Nagasivam
Date         : 11.12.2017
Copyright(C) : 2017
License      : GPL v2.0
Description  : This will be a standalone .exe which will utilize the virustotal 2.0 api
for getting the scan results for hashes, urls, etc.
*/

#include<iostream>
#include<fstream>
#include"virustotal.h"

int main(int argc, char** argv)
{
	if (argc == 6)
	{
		std::string scan_id = argv[1];
		std::string api_key = argv[2];
		std::string name = argv[3];
		std::string resource = argv[4];
		std::string file_name = argv[5];
		std::string location = "scans/scan" + scan_id + "/virustotal/" + file_name;

		VirusTotal virustotal(api_key);
		std::string result = "";
		if (name == "hash")
		{
			result = virustotal.get_result_for_hash(resource);
		}
		else if (name == "url")
		{
			result = virustotal.get_result_for_url(resource);
		}
		// Write the contents into the file
		std::ofstream file;
		file.open(location);
		if (file.is_open())
		{
			file << result;
			file.close();
		}
	}
	else 
	{
		std::cout << "\tVIRUSTOAL SCAN ENGINE v0.1\n";
		std::cout << "USAGE: virustotal.exe scan_id api_key hash|url md5|sha|url location";
	}
}