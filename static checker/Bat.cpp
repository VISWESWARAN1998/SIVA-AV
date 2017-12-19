#include "bat.h"

Bat::Bat(std::wstring fileName)
{
	this->fileName = fileName;
}


std::vector<std::string> Bat::getCommands(std::string line)
{
	std::vector<std::string> commands;
	// This boolean variable helps us to check 
	// if we are looping inside a string literal
	bool isStringLiteralOpened = false;
	std::string currentCommand = "";
	for (char letter : line)
	{
		// remove the trailing white space
		if (currentCommand == "" && letter == ' ')continue;
		else
		{
			// echo "call malware.bat" will not call malware.bat it just prints it
			// we dont want false positives
			if (letter == '"')
			{
				if (isStringLiteralOpened) isStringLiteralOpened = false;
				else isStringLiteralOpened = true;
			}
			if (letter == '&' || letter == '|')
			{
				if (isStringLiteralOpened==false)
				{
					if(currentCommand.size()>0)commands.push_back(currentCommand);
					currentCommand = "";
				}
			}
			else
			{
				currentCommand += letter;
			}
		}
	}
	if (currentCommand.size()>0)commands.push_back(currentCommand);
	return commands;
}

void Bat::analyseCommand(unsigned int lineNo, std::string command)
{
	// Check for the attribute changes
	std::string result = "";
	// Regex Patterns
	std::string unsafeExtensions = "(?:\.bat|\.exe|\.cmd|\.pif|\.vb|\.vbs)";
	std::string systemFileLocations = "C:.(?:Windows|Program)";
	std::string attributesPattern = "^attrib";
	std::string deleteContentPattern = "^(?:del|erase)";
	std::string encodingAndDecoding = "^certutil -(?:encode|decode)";
	std::string newDirectoriesPattern = "^mkdir";
	std::string downloadFilePatterns[] = {
		"(New-Object Net\.WebClient)\.DownloadFile",
		"Invoke-WebRequest",
		"^bitsadmin.exe"
	};
	std::string networkPattern = "^(?:netstat|net|netsh)";
	std::string callPattern = "^call";
	std::string registeryPattern = "^reg (?:query|add|delete|copy|save|restore|load|unload|compare|export|import|flags)";
	std::string powershellPattern = "^powershell";
	std::string taskKillPattern = "^tskill";
	

	// Check for attribute changes
	if (isRegexMatched(command, attributesPattern))
	{
		isAttributesChanged = true;
		result = result + "Attributes are used. ";
		if (command.find("+h") || command.find("+H") != std::string::npos)
		{
			result += "Hiding a file ";
			isHidingContent = true;
			// Let us see whether it is hiding dangerous file extensions
			if (isRegexMatched(command, unsafeExtensions))
			{
				result += "which seems to be malicious";
			}
		}
	}
	// Now check for deletion of contents
	else if(isRegexMatched(command, deleteContentPattern))
	{
		isContentDeleted = true;
		result += "Will delete file(s) ";
		if (isRegexMatched(command, systemFileLocations))
		{
			isSystemLocationModified = true;
			result += "The file present in the system location. ";
		}
		if (command.find("*.*") != std::string::npos)
		{
			result += "Warning! Multiple contents will be deleted ";
		}
	}
	// check whether the bat decodes or encodes something
	else if (isRegexMatched(command, encodingAndDecoding))
	{
		isDecodingOrEncodingOtherFile = true;
		result += "Mailicous behaviour, encodes or decodes other files ";
		// Let us see whether it is hiding dangerous file extensions
		if (isRegexMatched(command, unsafeExtensions))
		{
			result += "Warning! the program will decode/encode an executable file";
		}
	}
	// Check if it creates new directories
	else if (isRegexMatched(command, newDirectoriesPattern))
	{
		result += "New directories will be created ";
		isDirectoriesCreated = true;
		if (isRegexMatched(command, systemFileLocations))
		{
			isSystemLocationModified = true;
			result += "in the system location.";
		}
	}
	// Check if donwloads something from the internet!
	else if (isRegexMatched(command, downloadFilePatterns[0]) || isRegexMatched(command, downloadFilePatterns[1]) || isRegexMatched(command, downloadFilePatterns[2]))
	{
		isFileDownloaded = true;
		result += "Warning! Files will get downloaded from the internet";
	}
	// Now check for network settings to get utilizd
	else if (isRegexMatched(command, networkPattern))
	{
		isNetWorkUsed = true;
		result += "It uses network features ";
		if (isRegexMatched(command, "firewall"))
		{
			isFirewallGetsAccessed = true;
			result += "Warning! It may use/modify your firewall";
		}
	}
	// See if it calls other bat files
	else if (isRegexMatched(command, callPattern))
	{
		isOtherFileExcuted = true;
		result += "Warning! It will execute another bat file";
	}
	// See if it is using the registery
	else if (isRegexMatched(command, registeryPattern))
	{
		isRegisteryUsed = true;
		result += "Registery is used";
	}
	// Check if it uses powershell
	else if (isRegexMatched(command, powershellPattern))
	{
		isPowershellUsed = true;
		result += "Warning! It will use the powershell";
	}
	// Check if it kills other process
	else if (isRegexMatched(command, taskKillPattern))
	{
		isTaskTerminated = true;
		result += "This will terminate several tasks";
	}
	
	// finally add the result
	if (result.size() > 0)
	{
		//std::cout << result << "\n";
		description.insert(std::pair<unsigned int, std::string>(lineNo, result));
	}
}

bool Bat::isRegexMatched(std::string code, std::string pattern)
{
	try {
		std::regex regexPattern(pattern, std::regex_constants::icase);
		if (regex_search(code, regexPattern))
		{
			return true;
		}
	}
	catch (std::exception &e)
	{
		std::cout << pattern << "\n";
		std::cout << e.what();
	}
	return false;
}

bool Bat::analyseFile()
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		unsigned int lineNo = 1;
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			std::vector<std::string> individualCommand = getCommands(line);
			// Iterator
			typedef std::vector<std::string>::iterator itr;
			itr i1 = individualCommand.begin();
			itr i2 = individualCommand.end();
			for (itr i = i1; i != i2; ++i)
			{
				//std::cout << *i << "\n";
				analyseCommand(lineNo, *i);
			}
			lineNo++;
		}
		file.close();
		return true;
	}
	else {
		return false;
	}
}
