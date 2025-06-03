#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include "Array.h"
#include "Bitvector.h"

template<class Datatype>
class Array2D
{
public:
	Datatype* m_array;
	int m_width;
	int m_height;

	Array2D(int p_width, int p_height)
	{
		m_array = new Datatype[p_width * p_height];
		m_width = p_width;
		m_height = p_height;
	}

	~Array2D()
	{
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = 0;
	}

	Datatype& Get(int p_x, int p_y)
	{
		return m_array[p_y * m_width + p_x];
	}

	void Resize(int p_width, int p_height)
	{
		Datatype* newarray = new Datatype[p_width * p_height];
		if (newarray == 0)
		{
			return;
		}
		int x, y, t1, t2;
		int minx = (p_width < m_width ? p_width : m_width);
		int miny = (p_height < m_height ? p_height : m_height);
		for (y = 0; y < miny; y++)
		{
			t1 = y * p_width;
			t2 = y * m_width;
			for (x = 0; x < minx; x++)
			{
				newarray[t1 + x] = m_array[t2 + x];
			}
		}
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = newarray;
		m_width = p_width;
		m_height = p_height;
	}

	int Width()
	{
		return m_width;
	}

	int Height()
	{
		return m_height;
	}

	int Size()
	{
		return m_width * m_height;
	}
};

template<class Datatype>
class Array3D
{
public:
	
	// constructor
	Array3D(int p_width, int p_height, int p_depth)
	{
		m_array = new Datatype[p_width * p_height * p_depth];
		m_width = p_width;
		m_height = p_height;
		m_depth = p_depth;
	}

	// destructor
	~Array3D()
	{
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = 0;
	}

	Datatype& Get(int p_x, int p_y, int p_z)
	{
		return m_array[(p_z * m_width * m_height) + (p_y * m_width) + p_x];
	}

	void Resize(int p_width, int p_height, int p_depth)
	{
		// create a new array
		Datatype* newarray = new Datatype[p_width * p_height * p_depth];
		if (newarray == 0)
		{
			return;
		}
		// create the three coordinate variables and the four temp
		// variables
		int x, y, z, t1, t2, t3, t4;
		// determine the minimum of all dimensions.
		int minx = (p_width < m_width ? p_width : m_width);
		int miny = (p_height < m_height ? p_height : m_height);
		int minz = (p_depth < m_depth ? p_depth : m_depth);
		// loop through each cell and copy everything over
		for (z = 0; z < minz; z++)
		{
			// precalculate the outer term (z) of the access algorithm
			t1 = z * p_width * p_height;
			t2 = z * m_width * m_height;
		}
		for (y = 0; y < miny; y++)
		{
			// precalculate the middle term (y) of the access algorithm
			t3 = y * p_width;
			t4 = y * m_width;
			for (x = 0; x < minx; x++)
			{
				// move the data to the new array
				newarray[t1 + t3 + x] = m_array[t2 + t4 + x];
			}
		}
		// delete the old array
		if (m_array != 0)
		{
			delete[] m_array;
		}
		// set the new array, and the width, height, and depth
		m_array = newarray;
		m_width = p_width;
		m_height = p_height;
		m_depth = p_depth;
	}

		int Size()
		{
			return m_width * m_height * m_depth;
		}

		int Width()
		{
			return m_width;
		}

		int Height()
		{
			return m_height;
		}

		int Depth()
		{
			return m_depth;
		}

	private:
		Datatype* m_array;
		int m_width;
		int m_height;
		int m_depth;
};


int main()
{
	// declare the arrays.
	Array2D<int> iarray(5, 5);
	Array2D<float> farray(4, 4);

	int i, x, y;
	float f;
	// We cannot do this with the Array2D class:
	// iarray[4][4] = 10
	// do this instead:
	iarray.Get(4, 4) = 10;
	//set a cell in farray.
	farray.Get(3, 2) = 0.5f;
	// retrieve the cells that we just set.
	i = iarray.Get(4, 4);
	f = farray.Get(3, 2);
	// get the size of each array.
	i = iarray.Size();
	i = farray.Size();
	// fill integer array with consecutive numbers
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 5; x++)
		{
			iarray.Get(x, y) = y * 5 + x;
		}
	}

	//resize teh array to make it larger:
	iarray.Resize(6, 6);
	// resize the array to make it smaller:
	iarray.Resize(3, 3);

	std::cout << iarray.Size() << "\n";
	std::cout << farray.Size() << "\n";

}