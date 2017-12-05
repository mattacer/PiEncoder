/*
	main.cpp
	Handles the command line arguments, usage information of the program, and 
	interface usage (CLI or NET form).
*/

#include <iostream>
#include "piqpr8.h"
#include "MainForm.h"
#include "Encoder.h"

using namespace PiEncoder;
using namespace System;
using namespace System::Windows::Forms;

enum PiOperation {
	UNSPECIFIED = 0, ENCODE, DECODE
};

enum ArgumentError {
	HELP = 0, BOTH_D_E_FLAGS_SET, NO_SOURCE_SPECIFIED
};

static void usage(std::string executable, ArgumentError error){
	switch (error){
	case BOTH_D_E_FLAGS_SET:
		std::cerr << "Neither or both /e and /d flags were set. Only one may be set when not in GUI mode.\n" << std::endl;
		break;
	case NO_SOURCE_SPECIFIED:
		std::cerr << "A file source was not specified with the /i flag. An input file must be specified when not in GUI mode.\n" << std::endl;
		break;
	default:
		break;
	}
	std::cerr << "Usage: " << executable << " <option(s)> SOURCES\n"
				<< "This executable encodes a file by dividing it into 8 byte blocks, which are each matched against the digits of Pi.\n"
				<< "When a consecutive set of 16 hexidecimal digits of Pi matches the hexidecimal values of an 8 byte block,\n"
				<< "a 4 byte integer is used to store the locaton of that digit of pi in a new encoded output file.\n"
				<< "The decoding process takes the set of integers in the encoded file and calculates the 16 hexidecimal digits of pi at each corresponding location to reconstruct the original file.\n\n"
				<< "Options:\n"
				<< "\t/h, Displays this usage message\n"
				<< "\t/g, Enables GUI mode (Enabled by default when no arguments are specified)\n"
				<< "\t/e, Enables encoding of the input file\n"
				<< "\t/d, Enables decoding of the input file\n"
				<< "\t/i SOURCE, Specifies input file location (Must be specified when not in GUI mode)\n"
				<< "\t/o SOURCE, Specifies output file location\n"
				<< std::endl;
}

[STAThread]
int main(int argc, char* argv[]){
	bool useForm = false;
	std::string input = "", output = "";
	PiOperation operation = UNSPECIFIED;

	if (argc < 2){
		useForm = true;
	}
	for (int i = 1; i < argc; i++){
		std::string argument = argv[i];
		if (!argument.compare("/e")){
			if (operation == UNSPECIFIED){
				operation = ENCODE;
			} else {
				operation = UNSPECIFIED;
			}

		} else if (!argument.compare("/d")){
			if (operation == UNSPECIFIED){
				operation = DECODE;
			} else {
				operation = UNSPECIFIED;
			}
		} else if (!argument.compare("/g")){
			useForm = true;
		} else if (!argument.compare("/i")){
			if (i+1 < argc){
				input = argv[i+1];
			}
		} else if (!argument.compare("/o")){
			if (i+1 < argc){
				output = argv[i+1];
			}
		} else if (!argument.compare("/h")){
			usage(argv[0], HELP);
			return 0;
		}

	}
	if (input == "" && !useForm){
		usage(argv[0], NO_SOURCE_SPECIFIED);
		return 1;
	} else if (operation == UNSPECIFIED && !useForm){
		usage(argv[0], BOTH_D_E_FLAGS_SET);
		return 1;
	}
	if (useForm){
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		PiEncoder::MainForm form(input, output);
		Application::Run(%form);
	} else {
		Encoder encoder;
		if (operation == ENCODE){
			encoder.encode(input, output);

		} else if (operation == DECODE){
			encoder.decode(input, output);
		}
	}
	return 0;
}