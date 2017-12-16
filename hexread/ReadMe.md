# HexRead - Dependency free hex reading library
This library is used to read the hex and ascii values for the particular offset(using decimal for denoting the byte range) or also can be used to read the whole file.</br>
This hex reading library will throw two exceptions which is to be catched all the time,
1. FileNotFoundException - which is to be catched if the file is not found</br>
2. RangeOutOfBoundsException - which is to be catched if the range is unavailable</br>

The exceptions are defined in *hexread_exceptions.h* as follows
```C++
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
```
which is to be catched.</br>

Here is the code example:
```C++
#include"hexread.h"
#include"hexread_exceptions.h"

int main()
{
	// The file name to be opened
	HexRead read(L"E:/chromedriver.exe");
	try {
		read.read(0,9);
		// Get the value present at a particular offset
		if (read.is_offset_present(9))
		{
			HexAndAscii values = read.get(9);
			std::cout << "hex: " << values.hex << "\n";
			std::cout << "ascii: " << values.ascii << "\n";
		}
		else std::cout << "Offset Unavailable!";

		// Get everything
		std::map<unsigned long int, HexAndAscii> hexTable = read.get();
		// Now we will get the values
		for (auto hex : hexTable)
		{
			HexAndAscii values =  hex.second;
			unsigned long int offset = hex.first;
			std::cout << "offset: " << offset << "\n";
			std::cout << "Ascii Value: " << values.ascii << "\n";
			std::cout << "Hex Value: " << values.hex << "\n";
		}
	}
	catch (hexread::FileNotFoundException &e)
	{
		std::cout << e.what();
	}
	catch (hexread::RangeOutOfBoundsException &e) {
		std::cout << e.what();
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
}
```