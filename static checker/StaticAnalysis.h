/*
SWAMI KARUPPASWAMI THUNNAI
----------------------------
This class is the base class which specifies the general format for
checking various scripts for maliciousness of specifc extensions which will get executed 
automatically without any dependencies like .bat, .vbs, etc.
*/

#pragma once
#include<iostream>
#include<string>

class StaticAnalysis
{
protected:
	std::wstring fileName;
	bool isbase64Encoded = false;
	bool isFileSystemAffected = false;
	bool isRegisteryAffected = false;
	bool isNetworkAffected = false;
	bool isPowershellAccessed = false;
	bool isFileDownloadedFromNetwork = false;
public:
	virtual bool checkIfBase64Encoded(int lineNo, std::string code) = 0;
	virtual bool checkIfFileSystemAffected(int lineNo, std::string code) = 0;
	virtual bool checkIfRegisteryAffected(int lineNo, std::string code) = 0;
	virtual bool checkIfNetworkAffected(int lineNo, std::string code) = 0;
	virtual bool checkIfPowershellAccessed(int lineNo, std::string code) = 0;
	virtual bool checkIfFileDownloadedFromNetwork(int lineNo, std::string code) = 0;

	// Non virtual method
	// This method will check if a regular expression is matched or not
	bool isRegexMatched(std::string code, std::string pattern);
};
