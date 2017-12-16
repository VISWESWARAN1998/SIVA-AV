/*
SWAMI KARUPPASWAMI THUNNAI
==========================
Author      : Visweswaran Nagasivam
Email		: visweswaran.nagasivam98@gmail.com
Date		: 14.12.2017
Copyright   : 2017
License     : GPL 2.0
*/

#pragma once
#include<exception>

namespace hexread
{
	class FileNotFoundException : public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "File Cannot be found to read the hex values";
		}
	};

	class RangeOutOfBoundsException : public std::exception
	{
	public:
		virtual const char* what() const throw(){
			return "HexRead: Range cannot be processed!"; 
		}
	};
}
