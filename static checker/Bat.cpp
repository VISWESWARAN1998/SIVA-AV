// SWAMI KARUPPASWAMI THUNNAI
#include "Bat.h"

Bat::Bat(std::wstring fileName)
{
	this->fileName = fileName;
}

/*
This method will read every lines of the file and perform analysis
*/
void Bat::analyse()
{
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		int lineNo = 1;
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			// Check if the line of code is base64 encoded
			if (checkIfBase64Encoded(lineNo, line))
			{
				isbase64Encoded = true;
				// Add a description so that an user can know what is happening
				lineDescription.insert(std::pair<int, std::string>(lineNo, 
					"This line is encoded with base64 which seems to be malicious."));
			}
			else
			{
				// One can add multiple commands in 
				// single line of code so we need to check for all conditions!
				if (checkIfRegisteryAffected(lineNo, line))
				{
					isRegisteryAffected = true;
					std::string description = "registery key if affected at this line : "+line;
				}

			}
		}
		file.close(); // Dont forget to close the file
	}
}

/*
This method is used to check if the line of the code is bas64 encoded or not,
base64 encoding is usually seen in malware
*/
bool Bat::checkIfBase64Encoded(int lineNo, std::string code)
{
	bool isBase64 = true;
	std::string validBase64Chars =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789"
		"+/";
	// base64 strings are always a multiple of 4
	if (code.size() % 4 == 0)
	{
		for (char character : code)
		{
			if (validBase64Chars.find(character) == std::string::npos) return false;
		}
	}
	else return false;
	return isBase64;
}

bool Bat::checkIfFileSystemAffected(int lineNo, std::string code)
{
	return false;
}

bool Bat::checkIfRegisteryAffected(int lineNo, std::string code)
{
	
}

bool Bat::checkIfNetworkAffected(int lineNo, std::string code)
{
	return false;
}

bool Bat::checkIfPowershellAccessed(int lineNo, std::string code)
{
	return false;
}

bool Bat::checkIfFileDownloadedFromNetwork(int lineNo, std::string code)
{
	return false;
}
