#ifndef AUDIO_H
#define AUDIO_H
#include <cstdint>
#include <vector>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <algorithm>
#include <limits> 
#include <numeric>
#include <cmath>
namespace urssin001 {
	
	// core audio template to manipulate mono data
	
	template <typename T, int channels = 1> class AudioArray {
		private:
			std::vector<T> data_vector;
			int size;
			int samplingRate;
		public:

			// custom functor for mono normalisation

			class normalise {
				private:
					float desiredRMS;
					float currentRMS;
					float ratio;
					const T min = std::numeric_limits<T>::min();
					const T max = std::numeric_limits<T>::max();

				public:
					normalise(float current, float desired) : currentRMS(current), desiredRMS(desired){ ratio = desiredRMS/currentRMS; }

					T operator () (T amp) {
						if(amp * ratio > max) return max;
						else if (amp * ratio < min) return min;
						else return amp *ratio;
					}
			};


			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); samplingRate = 44100; }
			// constructor for unit tests
			AudioArray(std::vector<T> customBuffer): data_vector(customBuffer), size(customBuffer.size()) { }
			T & operator[] (int index) { return data_vector[index]; }
			void resizeArray(int N) { size = N; data_vector.resize(size); }
			int getSize() { return size; }
			void setSamplingRate(int rate) { samplingRate = rate; } 

			//copy semantics
			AudioArray(AudioArray <T> & rhs): size(rhs.size), samplingRate(rhs.samplingRate) {
				data_vector.resize(size);
				for(int i = 0; i < size; ++i) {
						data_vector[i] = rhs.data_vector[i];
				}
			}

			
			AudioArray& operator=(const AudioArray<T> rhs) {
				if(this != &rhs) {
					size = rhs.size;
					samplingRate = rhs.samplingRate;
					data_vector.resize(size);
					for(int i = 0; i < size; ++i) {
						data_vector[i] = rhs.data_vector[i];

					}

				}

				return *this;
			}

			// move semantics

			AudioArray(AudioArray<T> && rhs): size(rhs.size), samplingRate(rhs.samplingRate) , data_vector(std::move(rhs.data_vector)) { }

			AudioArray& operator= (AudioArray<T> && rhs) {
				if(this != &rhs) {
					data_vector.clear();
					size = rhs.size;
					samplingRate = rhs.samplingRate;
					data_vector.resize(size);
					data_vector = std::move(rhs.data_vector);
				}

				return *this;

			}

			// volume operation

			AudioArray<T> operator * (std::pair <float, float> volume) {
				assert(volume.first >= 0 & volume.first <= 1);
				AudioArray<T> temp = *this;
				for(int i = 0; i < size; i++) {
					temp[i] = temp[i] * volume.first;
				}

				return temp;
			}

			// concatenate audio file A and B

			AudioArray<T> operator|(AudioArray<T> A) {
				assert(this->size == A.size);
				AudioArray<T> temp = *this;
				temp.resizeArray(2*size);


				for(int i = 0; i < size; i++) {
				 	temp[i + size] = A[i];
				}
				return temp;
			}

			// add audio file A and B

			AudioArray<T> operator+(AudioArray<T> A) {
				assert(this->size == A.size);
				AudioArray<T> temp = *this;
				const T min = std::numeric_limits<T>::min();
				const T max = std::numeric_limits<T>::max();
				
				for(int i = 0; i < size; i++) {
				 	if(temp[i] + A[i] > max) temp[i] = max;
				 	else if(temp[i] + A[i] < min) temp[i] = min;
				 	else temp[i] += A[i];
				}
				return temp;
			}

			// cut order over range r1 - r2

			AudioArray<T> operator ^ (std::pair <int, int> range) {
				assert(range.first >= 0 & range.second < this->getSize() & (range.first < range.second));

				AudioArray<T> temp = *this;
				int counter = 0;
				int start = range.first;
				int end = range.second;

				std::remove_if( temp.data_vector.begin(), temp.data_vector.end(), 
					[&counter, start, end] (const T & val)
					{
						bool rem = false;
						if(counter >= start & counter <= end) {
							rem = true;
						}
						
						++counter;

						return rem;

					}
				);

				temp.resizeArray( temp.getSize() - (end - start) - 1); // get rid of stuff at the end that resulted from remove_if 
				
				return temp;


			}

			// reverse audio

			AudioArray<T> reverseAudio() {

				AudioArray<T> temp = *this;

				std::reverse(temp.data_vector.begin(), temp.data_vector.end());

				return temp;

			}

			float computeRMS() {
				AudioArray<T> temp = *this;
				int M = temp.getSize();
				float result = std::accumulate(temp.data_vector.begin(), temp.data_vector.end(), 0,
						[](int sum, const T & val)
						{
							return sum + val * val;

						}
				);

				return std::sqrt((1.0f/M) * result);

			}

			// radd
			AudioArray<T>& rangedAdd(AudioArray<T> & other, std::pair <int, int> range1, std::pair <int, int> range2) {
				// Length of the audio clip in seconds = NumberOfSamples / (float) samplingRate.
				int start1 = range1.first * samplingRate;
				int end1 = range1.second * samplingRate;
				int start2 = range2.first * samplingRate;
				int end2 = range2.second * samplingRate;
				assert((end1 - start1) == (end2 - start2));
				
				AudioArray<T> temp1 = *this;
				AudioArray<T> temp2 = other;

				temp1.resizeArray(end1 - start1 + 1);
				temp2.resizeArray(end2 - start2 + 1);

				std::copy(this->data_vector.begin() + start1, this->data_vector.begin() + start1 + end1 + 1, temp1.data_vector.begin());
				std::copy(other.data_vector.begin() + start2, other.data_vector.begin() + start2 + end2 + 1, temp2.data_vector.begin());
				AudioArray<T> result = temp1 + temp2;
				*this = result;
				return *this;

			}

			// normalise

			AudioArray<T> norm(float desiredRMS) {
				AudioArray<T> temp = *this;
				float currentRMS = temp.computeRMS();
				std::transform(temp.data_vector.begin(), temp.data_vector.end(), temp.data_vector.begin(), normalise (currentRMS, desiredRMS));
				return temp;
			}

	};

	// specialized Audio template to manipulate the data which
	// consists of 1 pair of samples per time step, L and R

	template <typename T> class AudioArray< std::pair<T, T>, 2> {
		private:
			std::vector<std::pair<T, T> > data_vector;
			int size;
			int samplingRate;
		public:
			// custom functor for stereo normalisation

			class normalise {
				private:
					std::pair<float, float>  desiredRMS;
					std::pair<float, float>  currentRMS;
					std::pair<float, float> ratio;
					const T min = std::numeric_limits<T>::min();
					const T max = std::numeric_limits<T>::max();

				public:
					normalise(std::pair<float, float> current, std::pair<float, float>  desired) : currentRMS(current), desiredRMS(desired)
					{
					 	ratio = std::make_pair(float( desiredRMS.first / currentRMS.first), float(desiredRMS.second / currentRMS.second));
					}

					std::pair<T,T> operator () (std::pair<T,T> amp) {

						std::pair<T,T> newAmp = amp;
						if(amp.first * ratio.first > max) newAmp.first = max;
						else if (amp.first * ratio.first < min)  newAmp.first = min;
						else newAmp.first = amp.first *ratio.first;

						if(amp.second * ratio.second > max) newAmp.second = max;
						else if (amp.second * ratio.second < min)  newAmp.second = min;
						else newAmp.second = amp.second *ratio.second;

						return newAmp;
					}
			};
			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); samplingRate = 44100;}
			AudioArray(std::vector<std::pair <T, T>> customBuffer): data_vector(customBuffer), size(customBuffer.size()) { }
			std::pair <T, T> & operator[](int index) { return data_vector[index]; }
			void resizeArray(int N) { size = N; data_vector.resize(size); }
			int getSize() { return size; }
			void setSamplingRate(int rate) { samplingRate = rate; } 

			//copy semantics
			AudioArray(AudioArray < std::pair<T, T>, 2> & rhs): size(rhs.size), samplingRate(rhs.samplingRate) {
				data_vector.resize(size);
				for(int i = 0; i < size; ++i) {
						data_vector[i].first = rhs.data_vector[i].first;
						data_vector[i].second = rhs.data_vector[i].second;
				}
			}

			
			AudioArray& operator=(const AudioArray< std::pair<T, T>, 2> rhs) {
				if(this != &rhs) {
					size = rhs.size;
					samplingRate = rhs.samplingRate;
					data_vector.resize(size);
					for(int i = 0; i < size; ++i) {
						data_vector[i].first = rhs.data_vector[i].first;
						data_vector[i].second = rhs.data_vector[i].second;

					}
				}
				return *this;
			}

			// move semantics

			AudioArray(AudioArray< std::pair<T, T>, 2> && rhs): size(rhs.size), samplingRate(rhs.samplingRate), data_vector(std::move(rhs.data_vector)) { }

			AudioArray& operator= (AudioArray< std::pair<T, T>, 2> && rhs) {
				if(this != &rhs) {
					data_vector.clear();
					size = rhs.size;
					samplingRate = rhs.samplingRate;
					data_vector.resize(size);
					data_vector = std::move(rhs.data_vector);
				}

				return *this;

			}

			// add audio file A and B

			AudioArray< std::pair<T, T>, 2> operator+(AudioArray< std::pair<T, T>, 2> A) {
				assert(this->size == A.size);
				AudioArray< std::pair<T, T>, 2>temp = *this;
				const T min = std::numeric_limits<T>::min();
				const T max = std::numeric_limits<T>::max();
				
				for(int i = 0; i < size; i++) {
				 	if(temp[i].first + A[i].first > max) temp[i].first = max;
				 	else if(temp[i].first + A[i].first < min) temp[i].first = min;
				 	else temp[i].first += A[i].first;

				 	if(temp[i].second + A[i].second > max) temp[i].second = max;
				 	else if(temp[i].second + A[i].second < min) temp[i].second = min;
				 	else temp[i].second += A[i].second;
				}

				return temp;
			}

			// cut order over range r1 - r2

			AudioArray< std::pair<T, T>, 2>operator ^ (std::pair <int, int> range) {
				assert(range.first >= 0 & range.second < this->getSize() & (range.first < range.second));

				AudioArray< std::pair<T, T>, 2> temp = *this;
				int counter = 0;
				int start = range.first;
				int end = range.second;

				std::remove_if( temp.data_vector.begin(), temp.data_vector.end(), 
					[&counter, start, end] (const std::pair<T, T> & val)
					{
						bool rem = false;
						if(counter >= start & counter <= end) {
							rem = true;
						}
						
						++counter;

						return rem;

					}
				);

				temp.resizeArray( temp.getSize() - (end - start) - 1); // get rid of stuff at the end that resulted from remove_if 
				
				return temp;


			}

			// volume operation

			AudioArray< std::pair<T, T>, 2> operator * (std::pair <float, float> volume) {
				assert(volume.first >= 0 & volume.first <= 1 & volume.second >= 0 & volume.second <= 1);
				AudioArray< std::pair<T, T>, 2>  temp = *this;
				for(int i = 0; i < size; i++) {
					temp[i].first = temp[i].first * volume.first;
					temp[i].second = temp[i].second * volume.second;
				}

				return temp;
			}

			// concatenate audio file A and B

			AudioArray< std::pair<T, T>, 2> operator|(AudioArray< std::pair<T, T>, 2> A) {
				assert(this->size == A.size);
				AudioArray< std::pair<T, T>, 2> temp = *this;
				temp.resizeArray(2*size);

				for(int i = 0; i < size; i++) {
				 	temp[i + size].first = A[i].first;
				 	temp[i + size].second = A[i].second;
				}

				return temp;
			}


			// reverse audio

			AudioArray<std::pair<T, T>, 2> reverseAudio() {

				AudioArray<std::pair<T, T>, 2>  temp = *this;

				std::reverse(temp.data_vector.begin(), temp.data_vector.end());

				return temp;

			}

			std::pair<float, float> computeRMS() {
				AudioArray<std::pair<T, T>, 2>  temp = *this;
				int M = temp.getSize();
				float result1 = std::accumulate(temp.data_vector.begin(), temp.data_vector.end(), 0,
						[](int sum, const std::pair<T, T> & val)
						{
							return sum + (val.first * val.first);
						}
				);

				float result2 = std::accumulate(temp.data_vector.begin(), temp.data_vector.end(), 0,
						[](int sum, const std::pair<T, T> & val)
						{
							return sum + (val.second * val.second);
						}
				);

				return std::make_pair(std::sqrt((1.0f/M) * result1), std::sqrt((1.0f/M) * result2));

			}


			// radd
			AudioArray<std::pair<T, T>, 2>& rangedAdd(AudioArray<std::pair<T, T>, 2> & other, std::pair <int, int> range1, std::pair <int, int> range2) {
				// Length of the audio clip in seconds = NumberOfSamples / (float) samplingRate.
				int start1 = range1.first * samplingRate;
				int end1 = range1.second * samplingRate;
				int start2 = range2.first * samplingRate;
				int end2 = range2.second * samplingRate;
				assert((end1 - start1) == (end2 - start2));
				
				AudioArray<std::pair<T, T>, 2>temp1 = *this;
				AudioArray<std::pair<T, T>, 2> temp2 = other;

				temp1.resizeArray(end1 - start1 + 1);
				temp2.resizeArray(end2 - start2 + 1);

				std::copy(this->data_vector.begin() + start1, this->data_vector.begin() + start1 + end1 + 1, temp1.data_vector.begin());
				std::copy(other.data_vector.begin() + start2, other.data_vector.begin() + start2 + end2 + 1, temp2.data_vector.begin());
				AudioArray<std::pair<T, T>, 2> result = temp1 + temp2;
				*this = result;
				return *this;

			}

			// normalise

			AudioArray<std::pair<T, T>, 2> norm(std::pair<float, float> desiredRMS) {
				AudioArray<std::pair<T, T>, 2> temp = *this;
				std::pair<float, float> currentRMS = temp.computeRMS();
				std::transform(temp.data_vector.begin(), temp.data_vector.end(), temp.data_vector.begin(), normalise (currentRMS, desiredRMS));
				return temp;
			}
	};

}

#endif