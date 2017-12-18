/*
SWAMI KARUPPASWAMI THUNNAI
---------------------------

Author: Visweswaran Nagasivam
*/

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

class Bat
{
private:
	bool isAttributesChanged = false;
	bool isContentDeleted = false;
	bool isDecodingOtherFile = false;
	bool isEncodingOtherFile = false;
	bool isDirectoriesCreated = false;
	bool isFileDownloaded = false;
	bool isNetWorkUsed = false;
	bool isOtherFileExcuted = false;
	bool isPowershellUsed = false;
	bool isRegisteryUsed = false;

	// This map will contain the description for a particular line which
	// does something unusual
	std::multimap<unsigned int, std::string> description;
	// This map will contain resoures like urls involved, ip address involved etc.,
	std::map<std::string, std::string> resources;
public:
	/*
	Sometimes, an attacker will add multiple lines of command in a sinlgle line of code
	like this: 
			echo "I wish to do good for you!" & call malware.bat 
	this method helps you to split it into individual commands like this,

	echo "I wish to do good for you!"
	call malware.bat
	*/
	std::vector<std::string> getCommands(std::string line);
};
