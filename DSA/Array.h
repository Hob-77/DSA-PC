
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