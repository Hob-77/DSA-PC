#pragma once

class Bitvector
{
public:
	uint32_t* m_array;
	int m_size;

	Bitvector(int p_size)
	{
		m_array = 0;
		m_size = 0;
		Resize(p_size);
	}

	~Bitvector()
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
		uint32_t* newvector = 0;
		if (p_size % 32 == 0)
		{
			p_size = p_size / 32;
		}
		else
		{
			p_size = (p_size / 32) + 1;
		}

		newvector = new uint32_t[p_size];
		if (newvector == 0)
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
			newvector[index] = m_array[index];
		}
		m_size = p_size;
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = newvector;
	}

	bool operator[](int p_index)
	{
		int cell = p_index / 32;
		int bit = p_index % 32;
		return (m_array[cell] & (1 << bit)) >> bit;
	}

	void Set(int p_index, bool p_value)
	{
		int cell = p_index / 32;
		int bit = p_index % 32;
		if (p_value == true)
		{
			m_array[cell] = (m_array[cell] | (1 << bit));
		}
		else
		{
			m_array[cell] = (m_array[cell] & (~(1 << bit)));
		}
	}

	void ClearAll()
	{
		int index;
		for (index = 0; index < m_size; index++)
		{
			m_array[index] = 0;
		}
	}

	void SetAll()
	{
		int index;
		for (index = 0; index < m_size; index++)
		{
			m_array[index] = 0xFFFFFFFF;
		}
	}

	bool WriteFile(const char* p_filename)
	{
		FILE* outfile = 0;
		size_t written = 0;
		outfile = fopen(p_filename, "wb");
		if (outfile == 0)
		{
			return false;
		}
		written = fwrite(m_array, sizeof(uint32_t), m_size, outfile);
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
		size_t read = 0;
		infile = fopen(p_filename, "rb");
		if (infile == 0)
		{
			return false;
		}
		read = fread(m_array, sizeof(uint32_t), m_size, infile);
		fclose(infile);
		if (read != m_size)
		{
			return false;
		}
		return true;
	}
};