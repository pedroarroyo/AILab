#ifndef TETRIS_GAME_MATH_H
#define TETRIS_GAME_MATH_H

#include <cstdint>
#include <vector>

namespace Util
{
	struct GridExtents
	{
		uint32_t m_numRows;
		uint32_t m_numColumns;
	};

	struct Size
	{
		uint32_t m_height;
		uint32_t m_width;
	};

	template<typename T>
	struct Vector2
	{
		Vector2(const T& x, const T& y) : m_x(x), m_y(y) {}
		T m_x;
		T m_y;
	};


	template<typename T>
	struct Box2
	{
		Box2(T min, T max) : m_max( max ), m_min( min ) 
		{;}
		T m_max;
		T m_min;
	};

	template<typename T>
	class Array2D
	{
	public:
		Array2D(const T* arr, unsigned sizeX, unsigned sizeY) 
			: m_sizeX(sizeX)
			, m_sizeY(sizeY)
		{
			m_array.resize(sizeX * sizeY);
			m_array.assign(arr, arr + sizeX * sizeY);
		}
		Array2D(const T& val, unsigned sizeX, unsigned sizeY) 
			: m_sizeX(sizeX)
			, m_sizeY(sizeY)
		{
			m_array.resize(sizeX * sizeY);
			std::fill(m_array.begin(), m_array.end(), val);
		}
		~Array2D()
		{
		}

		const T& At(unsigned x, unsigned y) const { return m_array[x +  m_sizeX * y]; }
		void Set(unsigned x, unsigned y, const T& val) { m_array[x +  m_sizeX * y] = val; }

	private:
		std::vector<T> m_array;

		unsigned m_sizeX;
		unsigned m_sizeY;
	};

//	bool Intersect( const Array2D& A, const Array2D& B) 
//	{ 
//		return false; 
//	}  

//	void Merge( Array2D& C, const Array2D& A, const Array2D& B) 
//	{ 
//
//	}  


	//typedef Vector2I _Vector2<int>;
	//typedef Box2I _Box2<Vector2I>;
};
#endif