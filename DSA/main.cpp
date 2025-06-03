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
	std::cout << "===Intializing arrays===" << "\n";

	// declare the arrays.
	Array3D<int> iarray(2, 5, 3);
	Array3D<float> farray(3, 4, 5);
	int i, x, y, z;
	float f;

	std::cout << "The size of int array: " << iarray.Size() << "\n";
	std::cout << "The size of float array: " << farray.Size() << "\n";

	std::cout << "Setting cells" << "\n";
	// set a few cells
	iarray.Get(1, 4, 0) = 10;
	farray.Get(3, 2, 3) = 0.5f;

	std::cout << "Retrieving cells" << "\n";
	// retrieve the cells that we just set.
	i = iarray.Get(1, 4, 0);
	f = farray.Get(3, 2, 3);

	std::cout << "Getting the size of each array" << "\n";
	// get the size of each array.
	i = iarray.Size();
	i = farray.Size();

	std::cout << "Filling array with consectuive numbers" << "\n";
	// fill the integer array with consectuive numbers
	for (z = 0; z < 3; z++)
	{
		for (y = 0; y < 5; y++)
		{
			for (x = 0; x < 2; x++)
			{
				iarray.Get(x, y, z) = (z * 2 * 5) + (y * 2) + x;
			}
		}
	}

	std::cout << "Printing contents of integer array" << "\n";

	for (z = 0; z < iarray.Depth(); z++)
	{
		std::cout << "Layer " << z << ":\n";
		std::cout << "--------\n";

		for (y = 0; y < iarray.Height(); y++)
		{
			for (x = 0; x < iarray.Width(); x++)
			{
				std::cout << iarray.Get(x, y, z);
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	std::cout << "Resizing arrays: " << "\n";

	// resize the array to make it larger:
	iarray.Resize(3, 6, 4);
	std::cout << "Made integer array bigger: " << iarray.Size() << "\n";
	// resize the array to make it smaller:
	iarray.Resize(2, 2, 2);
	std::cout << "Made integer array smaller: " << iarray.Size() << "\n";

	farray.Resize(10, 10, 10);
	std::cout << "Made float array huge: " << farray.Size() << "\n";

	farray.Resize(2, 3, 4);
	std::cout << "Made float array small:" << farray.Size() << "\n";

	iarray.~Array3D();
	farray.~Array3D();

}