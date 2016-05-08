#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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
	int s = argc;
	std::vector<std::string> v(argv, argv + argc);
	if ( s >= 9)
	{
		if(std::string(argv[7]) == "-o") s = argc - 2;
		
		if(std::string(argv[7]) == "-o") {
			outFileName = v[8];
			// discard the output file information 
			// once have file name
			v.erase(v.begin() + 7);
			v.erase(v.begin() + 7);
		}
		num_of_channels = atoi(argv[6]);
		samples_per_sec = atoi(argv[2]);
		bit_count = atoi(argv[4]);
	}

	else {

		std::cerr << "Insufficient argument number entered." << std::endl;
		return 1;
	}

	if (s == 9) {
		if(std::string(v[7]) == "-rev") {
			soundFile1 = v[s - 1];
			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						int8_t b = 8;
						AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> newArray = array.reverseAudio(); 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					int16_t b = 16;
					AudioArray <int16_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> newArray = array.reverseAudio();
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array.reverseAudio();
					writeOutStereoAudioFile(outFileName, b, newArray);

					
				}

				else if (bit_count == 16) {

					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array.reverseAudio();
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel


		} // end rev

		if(std::string(v[7]) == "-rms") {
			soundFile1 = v[s - 1];
			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						int8_t b = 8;
						AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						float rms = array.computeRMS(); 
						std::cout << "Computed RMS is: " << rms << std::endl;

					}
				

				else if (bit_count == 16) {

					int16_t b = 16;
					AudioArray <int16_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					float rms = array.computeRMS(); 
					std::cout << "Computed RMS is: " << rms << std::endl;

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					std::pair<float, float> rms = array.computeRMS();
					std::cout << "Computed RMS is: " << std::endl;
					std::cout << "For L: " <<  rms.first << std::endl;
					std::cout << "For R: " <<  rms.second << std::endl;

					
				}

				else if (bit_count == 16) {

					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					std::pair<float, float> rms = array.computeRMS();
					std::cout << "Computed RMS is: " << std::endl;
					std::cout << "For L: " <<  rms.first << std::endl;
					std::cout << "For R: " <<  rms.second << std::endl;

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel

		} // end rms
	} // end s=9

	if (s == 10) {

		if(std::string(v[7]) == "-add") {

			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						soundFile1 = v[s - 2];
						soundFile2 = v[s - 1];
						int8_t b = 8;
						AudioArray <int8_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
						AudioArray <int8_t> newArray = array1 + array2; 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int16_t b = 16;
					AudioArray <int16_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <int16_t> newArray = array1 + array2; 
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array1 + array2; 
					writeOutStereoAudioFile(outFileName, b, newArray);

					
				}

				else if (bit_count == 16) {

					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array1 + array2; 
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel

		}// end add operation

		if(std::string(v[7]) == "-cat") {

			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						soundFile1 = v[s - 2];
						soundFile2 = v[s - 1];
						int8_t b = 8;
						AudioArray <int8_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
						AudioArray <int8_t> newArray = array1 | array2; 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int16_t b = 16;
					AudioArray <int16_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <int16_t> newArray = array1 | array2; 
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array1 | array2; 
					writeOutStereoAudioFile(outFileName, b, newArray);

	
				}

				else if (bit_count == 16) {

					soundFile1 = v[s - 2];
					soundFile2 = v[s - 1];
					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array1 | array2; 
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel

		}// end cat operation

	} // end s = 10

	if (s == 11) {
		if(std::string(v[7]) == "-cut") {
			soundFile1 = v[s - 1];
			int start = atoi(v[8].c_str());
			int end = atoi(v[9].c_str());
			std::pair< int , int > range = std::make_pair(start, end);
			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						int8_t b = 8;
						AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> newArray = array ^ range; 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <int16_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> newArray = array ^ range; 
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array ^ range;  
					writeOutStereoAudioFile(outFileName, b, newArray);

	
				}

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array ^ range;  
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel
		} // end cut op

		if(std::string(v[7]) == "-v") {
			soundFile1 = v[s - 1];
			float start = atof(v[8].c_str());
			float end = atof(v[9].c_str());
			std::pair< float , float > range = std::make_pair(start, end);
			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						int8_t b = 8;
						AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> newArray = array * range; 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <int16_t> array =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> newArray = array * range; 
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array * range;  
					writeOutStereoAudioFile(outFileName, b, newArray);

	
				}

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array * range;  
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel
		} // end vol op



	} // end s = 11

	if (s == 14) {
		if(std::string(v[7]) == "-radd") {
			soundFile1 = v[s - 2];
			soundFile2 = v[s - 1];
			int start1 = atoi(v[8].c_str());
			int end1 = atoi(v[9].c_str());
			std::pair< int , int > range1 = std::make_pair(start1, end1);

			int start2 = atoi(v[10].c_str());
			int end2 = atoi(v[11].c_str());
			std::pair< int , int > range2 = std::make_pair(start2, end2);
			if(num_of_channels == 1) {

				if(bit_count == 8) {
					
						int8_t b = 8;
						AudioArray <int8_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
						AudioArray <int8_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
						AudioArray <int8_t> newArray = array1.rangedAdd(array2, range1, range2); 
						writeOutMonoAudioFile(outFileName, b, newArray);

					}
				

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <int16_t> array1 =  readInMonoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <int16_t> array2 =  readInMonoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <int16_t> newArray = array1.rangedAdd(array2, range1, range2); 
					writeOutMonoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			} // end mono channel

			else if(num_of_channels == 2){

				if(bit_count == 8) {
					
					
					int8_t b = 8;
					AudioArray <std::pair<int8_t, int8_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int8_t, int8_t>, 2> newArray = array1.rangedAdd(array2, range1, range2); 
					writeOutStereoAudioFile(outFileName, b, newArray);

	
				}

				else if (bit_count == 16) {

					
					int16_t b = 16;
					AudioArray <std::pair<int16_t, int16_t>, 2> array1 =  readInStereoAudioFile(soundFile1, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> array2 =  readInStereoAudioFile(soundFile2, b, samples_per_sec);
					AudioArray <std::pair<int16_t, int16_t>, 2> newArray = array1.rangedAdd(array2, range1, range2); 
					writeOutStereoAudioFile(outFileName, b, newArray);

				}

				else{

					std::cerr << "Invalid bit number entered." << std::endl;
					return 1;
				}

			}// end stereo channel

		} // end radd op

	} // end s = 14

	// if( argc>= 8 ) {
	// 	samples_per_sec = atoi(argv[2]);
	// 	bit_count = atoi(argv[4]);
	// 	num_of_channels = atoi(argv[6]);
	// 	soundFile1 = argv[argc -1];
	// 	if(argc >= 9)
	// 	{
	// 		if(std::string(argv[7])== "-rev") {
			
	// 			int8_t b;
	// 			AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b);
	// 			AudioArray <int8_t> newArray = array.reverseAudio();
	// 			writeOutMonoAudioFile("revsusan", b, newArray);
	// 		}

	// 		if(std::string(argv[7])== "-rms") {
			
	// 			int8_t b;
	// 			AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b);
	// 			float rms = array.computeRMS();
	// 			std::cout << "Computed RMS is: " << rms << std::endl;
	// 		}
	// 	}
	// 	if(argc >= 10){

	// 		if(std::string(argv[7])== "-v") {

	// 			float left = atof(argv[8]);
	// 			float right = atof(argv[9]);
	// 			int16_t b;
	// 			AudioArray <std::pair<int16_t, int16_t >, 2> array =  readInStereoAudioFile(soundFile1, b);
	// 			//AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b);
	// 			AudioArray <std::pair<int16_t, int16_t > , 2>newArray = array * std::make_pair(left, right); 
				
	// 			writeOutStereoAudioFile("volsusan", b, newArray);
	// 		}

	// 		if(std::string(argv[7])== "-cut") {
	// 			int start = atoi(argv[8]);
	// 			int end = atoi(argv[9]);
	// 			int8_t b;
	// 			AudioArray <int8_t> array =  readInMonoAudioFile(soundFile1, b);
	// 			AudioArray <int8_t> newArray = array ^ std::make_pair(start, end); 
	// 			writeOutMonoAudioFile("cutsusan", b, newArray);
	// 		}

	// 		if(std::string(argv[7])== "-cat") {
	// 			soundFile2 =  argv[argc - 1];
	// 			soundFile1 =  argv[argc - 2];
	// 			// int8_t b;
	// 			// AudioArray <int8_t> array1 =  readInMonoAudioFile(soundFile1, b);
	// 			// AudioArray <int8_t> array2 =  readInMonoAudioFile(soundFile2, b);
	// 			// AudioArray <int8_t> newArray = array1 | array2; 
	// 			int16_t b;
	// 			AudioArray <std::pair<int16_t, int16_t >, 2> array1 =  readInStereoAudioFile(soundFile1, b);
	// 			AudioArray <std::pair<int16_t, int16_t >, 2> array2 =  readInStereoAudioFile(soundFile2, b);
	// 			AudioArray <std::pair<int16_t, int16_t >, 2> newArray = array1 | array2;
	// 			writeOutStereoAudioFile("catsusan", b, newArray);

	// 		}

	// 		if(std::string(argv[7])== "-add") {
	// 			soundFile2 =  argv[argc - 1];
	// 			soundFile1 =  argv[argc - 2];
	// 			int8_t b;
	// 			AudioArray <int8_t> array1 =  readInMonoAudioFile(soundFile1, b);
	// 			AudioArray <int8_t> array2 =  readInMonoAudioFile(soundFile2, b);
	// 			AudioArray <int8_t> newArray = array1 + array2; 
	// 			writeOutMonoAudioFile("addsusan", b, newArray);
	// 		}


	// 	}
	// 	if(argc >= 12){
	// 		if(std::string(argv[7])== "-radd") {
	// 			int start = atoi(argv[8]);
	// 			int end = atoi(argv[9]);
	// 			soundFile2 =  argv[argc - 1];
	// 			soundFile1 =  argv[argc - 2];

	// 		}

	// 	}
		
	// 	// int8_t b;
	// 	// AudioArray <std::pair<int8_t, int8_t >, 2> array =  readInStereoAudioFile(soundFile1, b);
	// 	// writeOutStereoAudioFile("susan", b, array);
		 

	// }

	

	return 0;
}
