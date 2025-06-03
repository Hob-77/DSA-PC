
template<class Datatype>
class Array
{
public:
	Datatype* m_array;
	int m_size;

	Array(int p_size)
	{
		m_array = new Datatype[p_size];
		m_size = p_size;
	}

	~Array()
	{
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = 0;
	}

	int Size()
	{
		return m_size;
	}

	void Resize(int p_size)
	{
		Datatype* newarray = new Datatype[p_size];
		if (newarray == 0)
		{
			return;
		}

		int min;
		if (p_size < m_size)
		{
			min = p_size;
		}
		else
		{
			min = m_size;
		}
		int index;
		for (index = 0; index < min; index++)
		{
			newarray[index] = m_array[index];
		}
		m_size = p_size;
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = newarray;
	}

	Datatype& operator[] (int p_index)
	{
		return m_array[p_index];
	}

	operator Datatype* ()
	{
		return m_array;
	}

	void Insert(Datatype p_item, int p_index)
	{
		int index;
		for (index = m_size - 1; index > p_index; index--)
		{
			m_array[index] = m_array[index - 1];
		}
		m_array[p_index] = p_item;
	}

	void Remove(int p_index)
	{
		int index;
		for (index = p_index + 1; index < m_size; index++)
		{
			m_array[index - 1] = m_array[index];
		}
	}

	bool WriteFile(const char* p_filename)
	{
		FILE* outfile = 0;
		int written = 0;
		outfile = fopen(p_filename, "wb");
		if (outfile == 0)
		{
			return false;
		}
		written = fwrite(m_array, sizeof(Datatype), m_size, outfile);
		fclose(outfile);
		if (written != m_size)
		{
			return false;
		}
		return true;
	}

	bool ReadFile(const char* p_filename)
	{
		FILE* infile = 0;
		int read = 0;
		infile = fopen(p_filename, "rb");
		if (infile == 0)
		{
			return false;
		}
		read = fread(m_array, sizeof(Datatype), m_size, infile);
		fclose(infile);
		if (read != m_size)
		{
			return false;
		}
		return true;
	}
};

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
