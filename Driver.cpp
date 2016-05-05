#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include "FileIO.h"

int main(int argc, char *argv[]) {
	// get command line arguments to do operations here
	using namespace urssin001;
	int samples_per_sec = 0;
	int bit_count = 0;
	int num_of_channels = 0;
	std::string outFileName = "out";
	std::string soundFile1;
	std::string soundFile2;
	std::vector<std::pair<int, int>> v(2);
	v[0] = std::make_pair (5,1);
	std::cout << v[0].first <<std::endl;

	if( argc>= 8 ) {
		samples_per_sec = atoi(argv[2]);
		bit_count = atoi(argv[4]);
		num_of_channels = atoi(argv[6]);
		
		if(argc >= 9)
		{
			if(argv[7] == "-o") outFileName = argv[8];
		}
		soundFile1 = argv[argc -1];
		int8_t b;
		readInMonoAudioFile(soundFile1, b);
	

	}

	else {

		std::cerr << "Insufficient argument number entered." << std::endl;
		return 1;
	}

	return 0;
}
