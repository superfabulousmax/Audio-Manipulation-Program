// File with Unit Tests
#define CATCH_CONFIG_MAIN //So that catch will define a main method
#include "catch.hpp"
#include "Audio.h"
#include <iostream>
#include <cstdint>
using namespace urssin001;


TEST_CASE("Mono audio concatenation","This that concatenation of two mono audio files works correctly.")
{

	std::vector<int8_t> buffer1 = {1, 2, 3, 4};
	std::vector<int8_t> buffer2 = {5, 6, 7, 8};
	std::vector<int8_t> catBuffer = {1, 2, 3, 4, 5, 6, 7, 8};
	AudioArray <int8_t> array1(buffer1);
	AudioArray <int8_t> array2(buffer2);
	AudioArray <int8_t> cat = array1 | array2;
	for(int i = 0; i < cat.getSize(); ++i) {
		REQUIRE(cat[i] == catBuffer[i];
	}

}