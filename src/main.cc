// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include <RML/rml.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace rml;

int main(int argc, char* argv[])
{
	std::string filedata;

	IndentType indent = IndentType::Unknown;

	if (argc == 2)
	{
		std::ifstream input(argv[1]);
		filedata = std::string{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
	}
	else if (argc == 3)
	{
		std::string indentStr(argv[1]);
		std::transform(indentStr.begin(), indentStr.end(), indentStr.begin(), ::tolower);

		if (indentStr == "space")
		{
			indent = IndentType::Space;
		}
		else if (indentStr == "tab")
		{
			indent = IndentType::Tab;
		}

		std::ifstream input(argv[2]);
		filedata = std::string{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
	}
	else
	{
        std::cout << " .----------------.  .----------------.  .----------------. " << std::endl;
        std::cout << "| .--------------. || .--------------. || .--------------. |" << std::endl;
        std::cout << "| |  _______     | || | ____    ____ | || |   _____      | |" << std::endl;
        std::cout << "| | |_   __ \\    | || ||_   \\  /   _|| || |  |_   _|     | |" << std::endl;
        std::cout << "| |   | |__) |   | || |  |   \\/   |  | || |    | |       | |" << std::endl;
        std::cout << "| |   |  __ /    | || |  | |\\  /| |  | || |    | |   _   | |" << std::endl;
        std::cout << "| |  _| |  \\ \\_  | || | _| |_\\/_| |_ | || |   _| |__/ |  | |" << std::endl;
        std::cout << "| | |____| |___| | || ||_____||_____|| || |  |________|  | |" << std::endl;
        std::cout << "| |              | || |              | || |              | |" << std::endl;
        std::cout << "| '--------------' || '--------------' || '--------------' |" << std::endl;
        std::cout << " '----------------'  '----------------'  '----------------' " << std::endl << std::endl;
		std::cout << "Author: Richard Laughlin" << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Purpose:\n    Compile .rml files into the appropriate .html.\n    By default does not insert extra whitespace." << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Usage: \n    rml [indent_specifier] filename" << std::endl << std::endl;
		std::cout << "    [indent_specifier] \t (Optional) Either \"tab\" or \"space\"" << std::endl;
		std::cout << "    [filename] \t\t The filename to read in and compile to HTML." << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;

		return 0;
	}

	if (filedata.size() > 0)
	{
		try
		{
			std::cout << RML::create(filedata).toHtml(indent);
		}
		catch (std::runtime_error re)
		{
			std::cerr << re.what();
		}
	}

	return 0;
}
