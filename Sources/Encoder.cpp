/*
	Encoder.cpp
	Defines the Encoder class and its methods.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "Encoder.h"
#include "piqpr8.h"
#include "Crc.h"

#define UNSIGNED_INT32_MAX 2*2147483647-1

Encoder::Encoder(){
	handler = CONSOLE;
}

Encoder::Encoder(Handler handler){
	this->handler = handler;
}

bool Encoder::encode(std::string inputFileName, std::string outputFileName){
	bool allHexesMatch = false, stillMatching = true;
	char hex[] = "0123456789ABCDEF";
	std::ifstream input;
	std::ofstream output;
	size_t inputSize = 0;
	int blockByteSize = 2 * sizeof(int);
	int hexCount = 2 * blockByteSize;
	unsigned int piDigitIndex = 0, previousPiDigitIndex = 0;
	PiFileHeader header;
	std::vector<unsigned char> block(blockByteSize, 0);
	char blockDigits[17] = { '\0' };//hexCount+1 = 17
	char piDigits[17] = { '\0' };//hexCount+1 = 17

	//TODO: add try block to catch IO exceptions
	input.open(inputFileName, std::ios_base::in | std::ios_base::binary | std::ios::ate);
	output.open(outputFileName, std::ios_base::out | std::ios_base::binary);
	if (!input.is_open() || !output.is_open())
		return false;

	inputSize = input.tellg();
	input.seekg(0, std::ios::beg);
	output.write(reinterpret_cast<char*>(&header), sizeof(PiFileHeader));
	header.bytesForLastIndex = inputSize % blockByteSize;

	while (input.tellg() < inputSize && !input.eof()){
		input.read(reinterpret_cast<char*>(&block[0]), blockByteSize);
		if (input.eof()){
			hexCount = 2*header.bytesForLastIndex;
		}
		for (int i = 0; i < hexCount; i += 2){
			blockDigits[i] = hex[block[i / 2] / 16];
			blockDigits[i + 1] = hex[block[i / 2] % 16];
		}
		while (!allHexesMatch){
			stillMatching = true;
			PiDigits(piDigitIndex, hexCount, piDigits);
			previousPiDigitIndex = piDigitIndex;
			for (int i = 0; i < hexCount; i++){
				//Any character mismatch means that piDigitIndex does not satisfy the block, matching no longer matters
				if (blockDigits[i] != piDigits[i]){
					stillMatching = false;
				}
				//Moves the piDigitIndex to the next subset of matching characters in piDigits
				if (blockDigits[0] == piDigits[i] && i != 0 && previousPiDigitIndex == piDigitIndex){
					for (int j = 0; j < hexCount - i; j++){
						if (blockDigits[j] != piDigits[i + j]){
							break;
						}
						if (blockDigits[j] == piDigits[i + j] && j == hexCount - i - 1){
							piDigitIndex = piDigitIndex + i;
						}
					}
				}
				if (i == hexCount - 1){
					//At the final index, a match will trigger the bool
					if (blockDigits[i] == piDigits[i] && stillMatching){
						allHexesMatch = true;
					} else {
						if (previousPiDigitIndex == piDigitIndex){
							piDigitIndex = piDigitIndex + hexCount;
						}
						break;
					}
				}
			}
			//piDigitIndex has passed its maximum value, no need to stay in the while-loop
			if (piDigitIndex - 1 == UNSIGNED_INT32_MAX){
				break;
			}
		}
		if (allHexesMatch){
			std::printf("Match for %s found at index %i\n", blockDigits, previousPiDigitIndex);
			output.write(reinterpret_cast<char*>(&previousPiDigitIndex), sizeof(previousPiDigitIndex));
			allHexesMatch = false;
			piDigitIndex = 0;
			continue;
		} else {
			if (handler == CONSOLE){
				std::printf("Error: Couldn't find match for string: \n%s\nwinthin %i digits\n", blockDigits, UNSIGNED_INT32_MAX);
			} else {
			//TODO: Add dialog box to notify user of non-match
			}
			return false;
		}
	}
	input.close();
	//update header information, before rewriting the header to the output file
	size_t endPosition = output.tellp();
	(header.id)[0] = 'P';
	(header.id)[1] = 'I';
	header.cycles += 1;
	header.indices = (endPosition - sizeof(PiFileHeader)) / header.indexByteSize;
	input.open(inputFileName, std::ios_base::in | std::ios_base::binary);
	header.hash = crc32(input);
	output.seekp(0, std::ios_base::beg);
	std::printf("Adding header (%ibytes)\n", sizeof(PiFileHeader));
	output.write(reinterpret_cast<char*>(&header), sizeof(PiFileHeader));
	output.close();
	input.close();
	return true;
}

bool Encoder::encode(std::string inputFileName){
	return encode(inputFileName, "output.pi");
}

bool Encoder::decode(std::string inputFileName, std::string outputFileName){
	std::ifstream input;
	std::ofstream output;
	size_t inputSize;
	int blockByteSize = 2 * sizeof(int);
	int hexCount = 2 * blockByteSize;
	unsigned int piDigitIndex = 0, previousPiDigitIndex = 0;
	PiFileHeader verificationHeader;
	char response = '\0';
	std::vector<unsigned char> block(blockByteSize, 0);
	char blockDigits[17] = { '\0' };//hexCount+1 = 17
	char piDigits[17] = { '\0' };//hexCount+1 = 17

	//TODO: Add try block to catch IO exceptions
	input.open(inputFileName, std::ios_base::in | std::ios_base::binary | std::ios::ate);
	output.open(outputFileName, std::ios_base::out | std::ios_base::binary);
	if (!input.is_open())
		return false;

	inputSize = input.tellg();
	input.seekg(0, std::ios::beg);

	input.read(reinterpret_cast<char*>(&verificationHeader), sizeof(verificationHeader));
	switch (verifyHeader(verificationHeader)){
	case VALID_HEADER:
		break;
	case INVALID_HEADER:
		return false;
		break;
	case CORRUPT_HEADER:
	default:
		if (handler == CONSOLE){
			printf("Possibly corrupt header. Continue?(y/n)");
			while (tolower(response) != 'y' || tolower(response) != 'n'){
				std::cin >> response;
			}
			if (tolower(response) == 'n'){
				return false;
			}
		} else {
			//TODO: Add confirmation box prompting for user confirmation to continue
		}
	}
	while (input.tellg() < inputSize){
		input.read(reinterpret_cast<char*>(&piDigitIndex), sizeof(piDigitIndex));
		int position = input.tellg();
		if (position == inputSize){
			hexCount = 2 * verificationHeader.bytesForLastIndex;
			blockByteSize = verificationHeader.bytesForLastIndex;
		}
		PiDigits(piDigitIndex, hexCount, piDigits);
		char str[3];
		for (int i = 0; i < hexCount; i += 2){
			sprintf_s(str, "%c%c", piDigits[i], piDigits[i + 1]);
			block[i / 2] = strtol(str, nullptr, 16);
		}
		printf("Retrieved %s found for index %i\nWriting %i bytes\n", piDigits, piDigitIndex, blockByteSize);
		output.write(reinterpret_cast<char*>(&block[0]), blockByteSize);
	}
	output.close();
	input.close();
	input.open(outputFileName, std::ios_base::in | std::ios_base::binary);
	if (verificationHeader.hash == crc32(input)){
		printf("Hash match! Success!");
	} else {
		if (handler == CONSOLE){
			printf("Hash mismatch! Something is wrong!");
		}
		else {
			//TODO: Add dialog box
		}
	}
	return true;
}

bool Encoder::decode(std::string inputFileName){
	return decode(inputFileName, "output");
}

HeaderStatus Encoder::verifyHeader(const PiFileHeader& verificationHeader){
	if ((verificationHeader.id)[0] != 'P' || (verificationHeader.id)[1] != 'I'){
		return INVALID_HEADER;
	}
	if (verificationHeader.cycles > 10 || verificationHeader.cycles == 0){
		return CORRUPT_HEADER;
	}
	return VALID_HEADER;
}