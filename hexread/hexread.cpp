/*
SWAMI KARUPPASWAMI THUNNAI
==========================
Author      : Visweswaran Nagasivam
Email		: visweswaran.nagasivam98@gmail.com
Copyright(C): 2017
License     : GPL 2.0
*/
#include "hexread.h"
#include "hexread_exceptions.h"

HexRead::HexRead(std::wstring fileName)
{
	this->fileName = fileName;
}

std::string HexRead::getHexFromChar(unsigned char ascii)
{
	std::stringstream stream;
	stream << std::hex << int(ascii);
	std::string hexadecimal_value; // This will hold the hexa-decimal values
	stream >> hexadecimal_value;
	if (hexadecimal_value.size() == 1)hexadecimal_value = "0" + hexadecimal_value;
	return hexadecimal_value;
}

void HexRead::read()
{
	unsigned long int current_byte = 0;
	std::ifstream file(fileName, std::ios::binary);
	if (file.is_open())
	{
		while (!file.eof())
		{
			unsigned char ascii;
			file >> ascii;
			std::string hex = getHexFromChar(ascii);
			HexAndAscii currenHexAndAscii;
			currenHexAndAscii.ascii = ascii;
			currenHexAndAscii.hex = hex;
			hexTable[current_byte] = currenHexAndAscii;
			current_byte++;
		}
		file.close();
	}
	else throw hexread::FileNotFoundException();
}

void HexRead::read(unsigned long initByte, unsigned long int finalByte)
{
	if (initByte > finalByte) throw hexread::RangeOutOfBoundsException();
	unsigned long int totalBytes;
	std::ifstream file(fileName, std::ios::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		totalBytes = file.tellg();
		//std::cout << totalBytes;
		// If the initial value is greater than the boundary
		// then throw an exception informing the user.
		if (initByte > totalBytes)
		{
			file.close();
			throw hexread::RangeOutOfBoundsException();
		}
		// If the final range is greated than greater than the total range
		// resize gracefully
		if (finalByte > totalBytes) finalByte = totalBytes;
		// Now point to the begining of the file
		file.seekg(0, std::ios::beg);
		std::string contents;
		contents.resize(finalByte - initByte);
		file.read(&contents[0], finalByte - initByte);
		for (unsigned char ascii : contents)
		{
			std::string hex = getHexFromChar(ascii);
			HexAndAscii currenHexAndAscii;
			currenHexAndAscii.ascii = ascii;
			currenHexAndAscii.hex = hex;
			hexTable[initByte] = currenHexAndAscii;
			initByte++;
		}
		file.close();
	}
	else throw hexread::FileNotFoundException();
}

bool HexRead::is_offset_present(unsigned int offset)
{
	if (hexTable.find(offset) != hexTable.end()) return true;
	return false;
}

std::map<unsigned long int, HexAndAscii> HexRead::get()
{
	return hexTable;
}

HexAndAscii HexRead::get(unsigned int offset)
{
	return hexTable[offset];
}
