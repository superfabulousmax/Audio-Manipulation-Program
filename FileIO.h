#ifndef FILEIO_H
#define FILEIO_H
#include <fstream>
#include <string>
#include <iostream>
#include "Audio.h"
namespace urssin001 {


	static int fileSize;
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
			readAudio.seekg(0, readAudio.beg);
			fileSize = fileSizeInBytes;
			int NumberOfSamples = fileSizeInBytes / (sizeof(T) * 1);
			
			array.resizeArray(NumberOfSamples);

			

			readAudio.read((char *) &(array[0]), fileSizeInBytes);


			readAudio.close();
		}
		return array;

	}

	template<typename T>
	AudioArray<std::pair<T, T>, 2>  readInStereoAudioFile(std::string filename, T bits){

		AudioArray <std::pair<T, T>, 2 > array;
		std::ifstream readAudio(filename+".raw", std::ios::in | std::ios::binary);
		if(!readAudio) {
			std::cerr << "Could not read "+filename << std::endl;
		}
		
		else {
			// NumberOfSamples = fileSizeInBytes / (sizeof(intN_t) * channels)
			readAudio.seekg(0, readAudio.end);
			int fileSizeInBytes = readAudio.tellg();
			readAudio.seekg(0, readAudio.beg);
			fileSize = fileSizeInBytes;
			int NumberOfSamples = fileSizeInBytes / (sizeof(T) * 2);
			
			array.resizeArray(NumberOfSamples);

			
			for(int i = 0; i < NumberOfSamples; i++) {
				readAudio.read((char *) &(array[i].first), sizeof(T) );
				readAudio.read((char *) &(array[i].second), sizeof(T) );
			}
			


			readAudio.close();
		}
		return array;


	}

	template<typename T>
	void writeOutMonoAudioFile(std::string filename, T bits, AudioArray<T> & array) {

		std::ofstream writeAudio(filename+".raw", std::ios::out | std::ios::binary);
		if(!writeAudio) {
			std::cerr << "Could not write "+filename << std::endl;
		}
		
		else {
			

			writeAudio.write((char *) &(array[0]), fileSize);
			

			writeAudio.close();

		}

	}

	template<typename T>
	void writeOutStereoAudioFile(std::string filename, T bits, AudioArray<std::pair<T, T>, 2> & array) {

		std::ofstream writeAudio(filename+".raw", std::ios::out | std::ios::binary);
		if(!writeAudio) {
			std::cerr << "Could not write "+filename << std::endl;
		}
		
		else {
			
			int NumberOfSamples = fileSize / (sizeof(T) * 2);
		
			
			for(int i = 0; i < NumberOfSamples; i++) {
				writeAudio.write((char *) &(array[i].first), sizeof(T) );
				writeAudio.write((char *) &(array[i].second), sizeof(T) );
			}
			
			

			writeAudio.close();

		}

	}


}


#endif