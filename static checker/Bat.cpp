#include "bat.h"

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
