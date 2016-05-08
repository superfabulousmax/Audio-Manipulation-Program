// File with Unit Tests
#define CATCH_CONFIG_MAIN //So that catch will define a main method
#include "catch.hpp"
#include "Audio.h"
#include <iostream>
#include <cstdint>
using namespace urssin001;


TEST_CASE("Mono audio concatenation","This that concatenation of two mono audio files works correctly.")
{

	std::vector<int8_t> buffer1 = {int8_t(1), int8_t(2)};
	std::vector<int8_t> buffer2 = {int8_t(3), int8_t(4)};
	std::vector<int8_t> catBuffer = {int8_t(1), int8_t(2), int8_t(3), int8_t(4)};
	AudioArray <int8_t> array1(buffer1);
	AudioArray <int8_t> array2(buffer2);
	AudioArray <int8_t> cat = array1 | array2;
	for(int i = 0; i < cat.getSize(); ++i) {
		REQUIRE(cat[i] == catBuffer[i]);
	}

}

TEST_CASE("Stereo audio concatenation","This tests that concatenation of two stereo audio files works correctly.")
{

	std::vector<std::pair<int16_t, int16_t >> buffer1 = {std::make_pair(int8_t(1), int8_t(2))};
	std::vector<std::pair<int16_t, int16_t >> buffer2 = {std::make_pair(int8_t(3), int8_t(4))};
	std::vector<std::pair<int16_t, int16_t >> catBuffer = {std::make_pair(int8_t(1), int8_t(2)), std::make_pair(int8_t(3), int8_t(4))};
	AudioArray <std::pair<int16_t, int16_t >, 2> array1(buffer1);
	AudioArray <std::pair<int16_t, int16_t >, 2> array2(buffer2);
	AudioArray <std::pair<int16_t, int16_t >, 2> cat = array1 | array2;

	for(int i = 0; i < cat.getSize(); ++i) {
		REQUIRE(cat[i].first == catBuffer[i].first);
		REQUIRE(cat[i].second == catBuffer[i].second);
	}

}

TEST_CASE("Mono audio ranged add","This tests that ranged add of two stereo audio files works correctly.")
{

	std::vector<int8_t> buffer1 = {int8_t(1), int8_t(2), int8_t(9), int8_t(8)};
	std::vector<int8_t> buffer2 = {int8_t(3), int8_t(4), int8_t(1), int8_t(2)};
	std::vector<int8_t> rangedAdd = {int8_t(6), int8_t(10), int8_t(10)};
	std::pair<int, int> range1 = std::make_pair(1, 3);
	AudioArray <int8_t> array1(buffer1);
	AudioArray <int8_t> array2(buffer2);
	array1.setSamplingRate(1);
	array2.setSamplingRate(1);
	AudioArray <int8_t> result = array1.rangedAdd(array2, range1, range1);
	for(int i = 0; i < result.getSize(); ++i) {
		REQUIRE(result[i] == rangedAdd[i]);
	}

}


