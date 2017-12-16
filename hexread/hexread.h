/*
SWAMI KARUPPASWAMI THUNNAI
==========================

Description:
=============
Hexadecimal reader, this code will be helpful in reading the,
offset, hex and the ascii equilaent of the hex for the given
file.

Copyright(C) to Visweswaran Nagasivam, 2017

Author      : Visweswaran Nagasivam
Email		: visweswaran.nagasivam98@gmail.com
Copyright   : 2017
License     : GPL 2.0

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<map>


// This structure will contain the hexadecimal value along with it's ascii
struct HexAndAscii
{
	std::string hex;
	char ascii;
};

class HexRead
{
private:
	// This will contain the name of the file to be processed
	std::wstring fileName;
	// This will get the hexadecimal value to the character
	std::string getHexFromChar(unsigned char ascii);
	// This will be our hex table with offset in decimal, and the structure
	std::map<unsigned long int, HexAndAscii> hexTable;
public:
	// Constructor is used to initialize the file name
	HexRead(std::wstring fileName);
	// This will read the whole file to the memory!
	void read();
	// This will read only within the given range!
	void read(unsigned long initByte, unsigned long int finalByte);
	// This will check if the offset is present
	bool is_offset_present(unsigned int offset);
	// This will give you the whole hex table
	std::map<unsigned long int, HexAndAscii> get();
	// This will give you the struct at a particular offset
	HexAndAscii get(unsigned int offset);
};
