// File with Unit Tests
#define CATCH_CONFIG_MAIN //So that catch will define a main method
#include "catch.hpp"
#include "Audio.h"
#include <iostream>
#include <cstdint>
using namespace urssin001;

TEST_CASE("Mono audio add","This tests that the adding of two mono audio files works correctly.")
{

	std::vector<int8_t> buffer1 = {int8_t(1), int8_t(2)};
	std::vector<int8_t> buffer2 = {int8_t(3), int8_t(4)};
	std::vector<int8_t> addBuffer = {int8_t(4), int8_t(6)};
	AudioArray <int8_t> array1(buffer1);
	AudioArray <int8_t> array2(buffer2);
	AudioArray <int8_t> add = array1 + array2;

	// boundary case

	std::vector<int8_t> buffer3 = {INT8_MIN, INT8_MAX};
	std::vector<int8_t> buffer4 = {int8_t(-3), int8_t(4)};
	std::vector<int8_t> boundaryBuffer = {INT8_MIN, INT8_MAX};
	AudioArray <int8_t> array3(buffer3);
	AudioArray <int8_t> array4(buffer4);
	AudioArray <int8_t> bAdd = array3 + array4;

	for(int i = 0; i < add.getSize(); ++i) {
		REQUIRE(add[i] == addBuffer[i]);
		REQUIRE(bAdd[i] == boundaryBuffer[i]);
	}

}

TEST_CASE("Stereo audio add","This tests that the adding of two stereo audio files works correctly.")
{
	std::vector<std::pair<int16_t, int16_t >> buffer1 = {std::make_pair(int16_t(1), int16_t(2))};
	std::vector<std::pair<int16_t, int16_t >> buffer2 = {std::make_pair(int16_t(3), int16_t(4))};
	std::vector<std::pair<int16_t, int16_t >> addBuffer = {std::make_pair(int16_t(4), int16_t(6))};

	AudioArray <std::pair<int16_t, int16_t >, 2> array1(buffer1);
	AudioArray <std::pair<int16_t, int16_t >, 2> array2(buffer2);
	AudioArray <std::pair<int16_t, int16_t >, 2> add = array1 + array2;

	// boundary case
	std::vector<std::pair<int16_t, int16_t >> buffer3 = {std::make_pair(INT16_MIN ,  INT16_MAX )};
	std::vector<std::pair<int16_t, int16_t >> buffer4 = {std::make_pair(int16_t(-3), int16_t(4))};
	std::vector<std::pair<int16_t, int16_t >> boundaryBuffer = {std::make_pair( INT16_MIN ,  INT16_MAX)};

	AudioArray <std::pair<int16_t, int16_t >, 2> array3(buffer3);
	AudioArray <std::pair<int16_t, int16_t >, 2> array4(buffer4);
	AudioArray <std::pair<int16_t, int16_t >, 2> addBoundary = array3 + array4;

	for(int i = 0; i < add.getSize(); ++i) {
		REQUIRE(add[i].first == addBuffer[i].first);
		REQUIRE(add[i].second == addBuffer[i].second);
		REQUIRE(addBoundary[i].first == boundaryBuffer[i].first);
		REQUIRE(addBoundary[i].second == boundaryBuffer[i].second);
	}

}

TEST_CASE("Mono audio concatenation","This tests that concatenation of two mono audio files works correctly.")
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

TEST_CASE("Stereo audio volume factor","This tests that the volume factor operation for stereo audio files works correctly.")
{
	std::vector<std::pair<int8_t, int8_t>> buffer = {std::make_pair(int8_t(1), int8_t(2))};
	std::vector<std::pair<int8_t, int8_t>> volBuffer = {std::make_pair(int8_t(1 * 0.2f), int8_t(2 * 0.5f) )};
	AudioArray <std::pair<int8_t, int8_t>,2> array(buffer);
	AudioArray <std::pair<int8_t, int8_t>,2>  a = array * std::make_pair(0.2f, 0.5f); 

	for(int i = 0; i < a.getSize(); ++i) {
		REQUIRE(a[i].first == volBuffer[i].first);
		REQUIRE(a[i].second == volBuffer[i].second);

	}
}

TEST_CASE("Mono audio volume factor","This tests that the volume factor operation for mono audio files works correctly.")
{
	std::vector<int8_t> buffer = {int8_t(1), int8_t(2)};
	std::vector<int8_t> volBuffer = {int8_t(1 * 0.2f), int8_t(2 * 0.2f)};
	AudioArray <int8_t> array(buffer);
	AudioArray <int8_t> a = array * std::make_pair(0.2f, 0.5f); 

	for(int i = 0; i < a.getSize(); ++i) {
		REQUIRE(a[i] == volBuffer[i]);
	}
}

TEST_CASE("Mono audio cut","This tests that the cutting of over the given range for mono audio files works correctly.")
{
	std::vector<int8_t> buffer = {int8_t(1), int8_t(2), int8_t(3), int8_t(4)};
	std::vector<int8_t> cutBuffer = {int8_t(1), int8_t(4)};
	AudioArray <int8_t> array(buffer);
	AudioArray <int8_t> cut = array ^ std::make_pair(1, 2);

	for(int i = 0; i < cut.getSize(); ++i) {
		REQUIRE(cut[i] == cutBuffer[i]);
	}
}

TEST_CASE("Stereo audio cut","This tests that the cutting of over the given range for stereo audio files works correctly.")
{
	std::vector<std::pair<int16_t, int16_t >> buffer =
	 {std::make_pair(int16_t(1), int16_t(2)) ,std::make_pair(int16_t(3), int16_t(4)), std::make_pair(int16_t(7), int16_t(6))};
	std::vector<std::pair<int16_t, int16_t >> cutBuffer = 
	 {std::make_pair(int16_t(1), int16_t(2)) , std::make_pair(int16_t(7), int16_t(6))};
	AudioArray <std::pair<int16_t, int16_t >, 2> array(buffer);
	AudioArray <std::pair<int16_t, int16_t >, 2> cut = array ^ std::make_pair(1, 2);

	for(int i = 0; i < cut.getSize(); ++i) {
		REQUIRE(cut[i].first == cutBuffer[i].first);
		REQUIRE(cut[i].second == cutBuffer[i].second);
	}
}

TEST_CASE("Mono audio reverse","This tests that reverse of mono audio files works correctly.")
{
	std::vector<int8_t> buffer = {int8_t(1), int8_t(2)};
	std::vector<int8_t> revBuffer = {int8_t(2), int8_t(1)};
	AudioArray <int8_t> array(buffer);
	AudioArray <int8_t> reverse = array.reverseAudio();
	for(int i = 0; i < reverse.getSize(); ++i) {
		REQUIRE(reverse[i] == revBuffer[i]);
	}

}

TEST_CASE("Mono audio rms","This tests that the calculation of RMS for mono audio files works correctly.")
{

	std::vector<int8_t> buffer = {int8_t(1), int8_t(2)};
	AudioArray <int8_t> array(buffer);
	float result = std::sqrt(0.5f * (1 + 4));
	REQUIRE(array.computeRMS() == result);
}

TEST_CASE("Stereo audio rms","This tests that the calculation of RMS for stereo audio files works correctly.")
{
	std::vector<std::pair<int8_t, int8_t >> buffer = {std::make_pair(int8_t(1), int8_t(2)), std::make_pair(int8_t(2), int8_t(1))};
	AudioArray <std::pair<int8_t, int8_t >, 2> array(buffer);
	float result = std::sqrt(0.5f * (1 + 4));
	REQUIRE(array.computeRMS().first == result);
	REQUIRE(array.computeRMS().second == result);
}



TEST_CASE("Mono audio ranged add","This tests that ranged add of two mono audio files works correctly.")
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

TEST_CASE("Stereo audio ranged add","This tests that ranged add of two stereo audio files works correctly.")
{

	std::vector<std::pair<int8_t, int8_t >> buffer1 = {std::make_pair(int8_t(1), int8_t(2)), std::make_pair(int8_t(9), int8_t(8))};
	std::vector<std::pair<int8_t, int8_t >> buffer2 = {std::make_pair(int8_t(3), int8_t(4)), std::make_pair(int8_t(1), int8_t(2))};
	std::vector<std::pair<int8_t, int8_t >> rangedAdd = {std::make_pair(int8_t(4), int8_t(6)), std::make_pair(int8_t(10), int8_t(10))};
	std::pair<int, int> range1 = std::make_pair(0, 1);
	AudioArray <std::pair<int8_t, int8_t >, 2> array1(buffer1);
	AudioArray <std::pair<int8_t, int8_t >, 2> array2(buffer2);
	array1.setSamplingRate(1);
	array2.setSamplingRate(1);
	AudioArray <std::pair<int8_t, int8_t >, 2> result = array1.rangedAdd(array2, range1, range1);
	for(int i = 0; i < result.getSize(); ++i) {
		REQUIRE(result[i].first == rangedAdd[i].first);
		REQUIRE(result[i].second == rangedAdd[i].second);
	}

}

TEST_CASE("Mono audio normalise","This tests that normalisation of a mono audio file works correctly.")
{
	float currentRMS = std::sqrt(0.25f* (1 + 4 + 81 + 64));
	float desiredRMS = 3.0f;
	float ratio = desiredRMS / currentRMS;
	std::vector<int8_t> buffer = {int8_t(1), int8_t(2), int8_t(9), int8_t(8)};
	std::vector<int8_t> normBuffer = {int8_t(1 * ratio), int8_t(2 * ratio), int8_t(9 * ratio), int8_t(8 * ratio)};
	AudioArray <int8_t> array(buffer);
	
	
	REQUIRE(currentRMS == array.computeRMS());
	AudioArray <int8_t> n = array.norm(desiredRMS);

	for(int i = 0; i < n.getSize(); ++i) {
		REQUIRE(n[i] == normBuffer[i]);
	}

}

TEST_CASE("Stereo audio normalise","This tests that normalisation of a stereo audio file works correctly.")
{
	std::pair<float, float > currentRMS = std::make_pair(std::sqrt(0.5f* (1 + 81)), std::sqrt(0.5f * (4 + 64)));
	std::pair<float, float > desiredRMS = std::make_pair(3.0f, 3.0f);
	std::pair<float, float > ratio = std::make_pair(( desiredRMS.first / currentRMS.first), (desiredRMS.second / currentRMS.second));
	std::vector<std::pair<int8_t, int8_t >> buffer = {std::make_pair(int8_t(1), int8_t(2)), std::make_pair(int8_t(9), int8_t(8))};
	std::vector<std::pair<int8_t, int8_t >> normBuffer = 
	 {std::make_pair(int8_t(1 * ratio.first), int8_t(2 * ratio.second)), std::make_pair(int8_t(9 * ratio.first), int8_t(8  * ratio.second))};
	AudioArray <std::pair<int8_t, int8_t >, 2> array(buffer);
	
	
	REQUIRE(currentRMS == array.computeRMS());
	AudioArray <std::pair<int8_t, int8_t >, 2>  n = array.norm(desiredRMS);

	for(int i = 0; i < n.getSize(); ++i) {
		REQUIRE(n[i].first == normBuffer[i].first);
		REQUIRE(n[i].second == normBuffer[i].second);
	}

}


