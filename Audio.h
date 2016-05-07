#ifndef AUDIO_H
#define AUDIO_H
#include <cstdint>
#include <vector>
#include <iostream>
#include <assert.h>
namespace urssin001 {

	// core audio template to manipulate mono data
	
	template <typename T, int channels = 1> class AudioArray {
		private:
			std::vector<T> data_vector;
			int size;
		public:
			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); }
			T & operator[] (int index) { return data_vector[index]; }
			void resizeArray(int N) { size = N; data_vector.resize(size); }
			int getSize() { return size; };
			//copy semantics
			AudioArray(AudioArray <T> & rhs): size(rhs.size) {
				data_vector.resize(size);
				for(int i = 0; i < size; ++i) {
						data_vector[i] = rhs.data_vector[i];
				}
			}

			
			AudioArray& operator=(const AudioArray<T> rhs) {
				if(this != &rhs) {
					size = rhs.size;
					data_vector.resize(size);
					for(int i = 0; i < size; ++i) {
						data_vector[i] = rhs.data_vector[i];

					}

				}

				return *this;
			}

			// move semantics

			AudioArray(AudioArray<T> && rhs): size(rhs.size), data_vector(std::move(rhs.data_vector)) { }

			AudioArray& operator= (AudioArray<T> && rhs) {
				if(this != &rhs) {
					data_vector.clear();
					size = rhs.size;
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
		
	};

	// specialized Audio template to manipulate the data which
	// consists of 1 pair of samples per time step, L and R

	template <typename T> class AudioArray< std::pair<T, T>, 2> {
		private:
			std::vector<std::pair<T, T> > data_vector;
			int size;
		public:
			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); }
			std::pair <T, T> & operator[](int index) { return data_vector[index]; }
			void resizeArray(int N) { size = N; data_vector.resize(size); }
	};

}

#endif