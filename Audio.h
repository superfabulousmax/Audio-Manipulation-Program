#ifndef AUDIO_H
#define AUDIO_H
#include <cstdint>
#include <vector>
namespace urssin001 {
	// core audio template to manipulate mono data
	
	template <typename T>
	class AudioArray {
		private:
			std::vector<T> data_vector;
			int size;
		public:
			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); }
			T & operator[](int index) { return data_vector[index]; }
			void resizeArray(int N) { size = N; data_vector.resize(size); }
	};

	// specialized Audio template to manipulate the data which
	// consists of 1 pair of samples per time step, L and R
	template <typename T>
	class AudioArray< std::pair<T, T> > {
		private:
			std::vector<std::pair<T, T> > data_vector;
			int size;
		public:
			AudioArray(int N = 0) : size(N) { data_vector.reserve(size); }
	};

}

#endif