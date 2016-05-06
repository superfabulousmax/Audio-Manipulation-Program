#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include "FileIO.h"
#include "Audio.h"

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

	if( argc>= 8 ) {
		samples_per_sec = atoi(argv[2]);
		bit_count = atoi(argv[4]);
		num_of_channels = atoi(argv[6]);
		soundFile1 = argv[argc -1];
		if(argc >= 9)
		{
			if(std::string(argv[7]) == "-o") outFileName = argv[8];
		}
		if(argc >= 11){

			if(std::string(argv[7])== "-v") {

				float left = atof(argv[8]);
				float right = atof(argv[9]);
				int8_t b;
				AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b);
				AudioArray <int8_t> newArray = array * std::make_pair(left, right); 
				
				writeOutMonoAudioFile("softsusan", b, newArray);
			}
			
			else if(std::string(argv[9])== "-v") {

				
			}

		}
		
		int8_t b;
		AudioArray <std::pair<int8_t, int8_t >, 2> array =  readInStereoAudioFile(soundFile1, b);
		writeOutStereoAudioFile("susan", b, array);
		 

	}

	else {

		std::cerr << "Insufficient argument number entered." << std::endl;
		return 1;
	}

	return 0;
}
