/*
SWAMI KARUPPASWAMI THUNNAI
---------------------------

Author : Visweswaran Nagasivam
Email  : visweswaran.nagasivam98@gmail.com
*/

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<iterator>
#include<regex>

class Bat
{
private:
	std::wstring fileName;

	bool isAttributesChanged = false;
	bool isContentDeleted = false;
	bool isDecodingOrEncodingOtherFile = false;
	bool isDirectoriesCreated = false;
	bool isFileDownloaded = false;
	bool isFirewallGetsAccessed = false;
	bool isHidingContent = false;
	bool isSystemLocationModified = false;
	bool isNetWorkUsed = false;
	bool isOtherFileExcuted = false;
	bool isPowershellUsed = false;
	bool isRegisteryUsed = false;
	bool isTaskTerminated = false;
	//unsigned int isMalicious = 0;

	// This map will contain the description for a particular line which
	// does something unusual, same line can contain multiple commands so I've used multimap
	std::multimap<unsigned int, std::string> description;
	// This map will contain resoures like urls involved, ip address involved etc.,
	//std::map<std::string, std::string> resources;

public:
	/*constructor to initialize the file name*/
	Bat(std::wstring fileName);
	/*A method to analyse the file*/
	bool analyseFile();
	/*
	Sometimes, an attacker will add multiple lines of command in a sinlgle line of code
	like this: 
			echo "I wish to do good for you!" & call malware.bat 
	this method helps you to split it into individual commands like this,

	echo "I wish to do good for you!"
	call malware.bat
	*/
	std::vector<std::string> getCommands(std::string line);
	// The method will perform an analysis on that command
	void analyseCommand(unsigned int lineNo, std::string command);
	// This method will return true if regex and the code gets matches
	bool isRegexMatched(std::string code, std::string pattern);

	// Getters
	// Will return the description
	std::multimap<unsigned int, std::string> getDescription() { return description; }
	// Will return true if attributes is changed
	bool attribChange() { return isAttributesChanged; }
	// Will return true if content is deleted
	bool contentDeleted() { return isContentDeleted; }
	// Will return true if decoding or encoding occured
	bool encodingDecodingOccred() { return isDecodingOrEncodingOtherFile; }
	// Will return true if directories is created
	bool newDirectories() { return isDirectoriesCreated; }
	// Will return true if file is downloaded from the internet
	bool fileDownloads() { return isFileDownloaded; }
	// Will return true if firewall is being used
	bool firewallAccess() { return isFirewallGetsAccessed; }
	// Will return true if it hides content from user
	bool hidingContent() { return isHidingContent; }
	// Will return true if if system location modified
	bool systemLocationModification() { return isSystemLocationModified; }
	// Will return true if network is being used
	bool networkUsage() { return isNetWorkUsed; }
	// Will return true if other files get executed
	bool otherFileExecuted() { return isOtherFileExcuted; }
	// Will return true if powershell is used
	bool powershellUsage() { return isPowershellUsed; }
	// Will return true if registery used
	bool registeryUsage() { return isRegisteryUsed; }
	// Will return true if task gets terminated
	bool taskTermination() { return isTaskTerminated; }
};
