#ifndef FILEIO_H
#define FILEIO_H
#include <fstream>
#include <string>
#include <iostream>
#include "Audio.h"
namespace urssin001 {

	template<typename T>
	AudioArray<T>  readInMonoAudioFile(std::string filename, T bits){

		AudioArray <T> array;
		std::ifstream readAudio(filename+".raw", std::ios::in | std::ios::binary);
		if(!readAudio) {
			std::cerr << "Could not read "+filename << std::endl;
		}
		
		else {
			// NumberOfSamples = fileSizeInBytes / (sizeof(intN_t) * channels)
			readAudio.seekg(0, readAudio.end);
			int fileSizeInBytes = readAudio.tellg();
			int NumberOfSamples = fileSizeInBytes / (sizeof(T) * 1);
			array.resizeArray(NumberOfSamples);

			for(int i = 0; i < NumberOfSamples; ++i) {

				readAudio >> array[i];
				std::cerr << (int)array[i] << std::endl;
			}


			readAudio.close();
		}
		return array;

	}

	void readInStereoAudioFile(std::string filename);
	void writeOutAudioFile(std::string filename);


}


#endif