/*
	Crc.h
	Defines the crc function.
*/

#include <fstream>
#include "Crc.h"

int crc32(std::ifstream& input){
	unsigned long crc32_table[256];
	unsigned long ulPolynomial = 0x04c11db7;
	int crc32 = 0;
	unsigned char buffer = 0;
	size_t inputSize = 0;

	input.seekg(0, std::ios_base::end);
	inputSize = input.tellg();
	input.seekg(0, std::ios_base::beg);

	for (int i = 0; i <= 0xFF; i++){
		unsigned long value = 0;
		int temp = i;
		for (int j = 1; j < (8 + 1); j++){
			if (temp & 1){
				value |= 1 << (8 - j);
			}
			temp >>= 1;
		}
		crc32_table[i] = value << 24;
		for (int j = 0; j < 8; j++){
			if (crc32_table[i] & (1 << 31)){
				crc32_table[i] = (crc32_table[i] << 1) ^ ulPolynomial;
			} else {
				crc32_table[i] = (crc32_table[i] << 1) ^ 0;
			}
			
		}
		value = 0;
		for (int j = 1; j < (32 + 1); j++){
			if (crc32_table[i] & 1){
				value |= 1 << (32 - j);
			}
			crc32_table[i] >>= 1;
		}
		crc32_table[i] = value;
	}

	unsigned long crc = 0xffffffff;
	for (int i = 0; i < inputSize; i++){
		input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ buffer];
	}
	return crc ^ 0xffffffff;
}