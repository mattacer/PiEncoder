/*
	Encoder.h
	Declares the Encoder class, PiFileHeader struct, and enumeration types used by the Encoder class. 
*/

#pragma once
#include <string>

struct PiFileHeader {
	signed char id[2];
	const float version = 0.1;
	const int indexByteSize = sizeof(int);
	unsigned short cycles = 0;
	unsigned int indices = 0;
	unsigned char bytesForLastIndex = 0;
	int hash = 0;
};

enum HeaderStatus{
	VALID_HEADER = 0, INVALID_HEADER, CORRUPT_HEADER
};

enum Handler{
	CONSOLE = 0, FORM
};

class Encoder{
public:
	Encoder();
	Encoder(Handler handler);
	bool encode(std::string inputFileName, std::string outputFileName);
	bool encode(std::string inputFileName);
	bool decode(std::string inputFileName, std::string outputFileName);
	bool decode(std::string inputFileName);
	HeaderStatus verifyHeader(const PiFileHeader& verificationHeader);
private:
	Handler handler;
};