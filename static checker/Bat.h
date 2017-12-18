/*
SWAMI KARUPPASWAMI THUNNAI
*/
#pragma once
#include "StaticAnalysis.h"
#include<fstream>
#include<map>



class Bat : public StaticAnalysis
{
private:
	std::map<int, std::string> lineDescription;
public:
	Bat(std::wstring fileName);
	void analyse();
	// Inherited via StaticAnalysis
	virtual bool checkIfBase64Encoded(int lineNo, std::string code) override;
	virtual bool checkIfFileSystemAffected(int lineNo, std::string code) override;
	virtual bool checkIfRegisteryAffected(int lineNo, std::string code) override;
	virtual bool checkIfNetworkAffected(int lineNo, std::string code) override;
	virtual bool checkIfPowershellAccessed(int lineNo, std::string code) override;
	virtual bool checkIfFileDownloadedFromNetwork(int lineNo, std::string code) override;
};

