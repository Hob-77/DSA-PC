#include <iostream>
#include <algorithm>

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

class Monster
{
public:
	int m_x;
	int m_y;
	int m_hitpoints;
};

Array<Monster> g_monsterarray(32);
int g_monsters = 0;

bool AddMonster()
{
	if (g_monsters == g_monsterarray.Size())
		g_monsterarray.Resize(g_monsterarray.Size() + 32);
	g_monsterarray[g_monsters].m_x = rand() % 640;
	g_monsterarray[g_monsters].m_y = rand() % 480;
	g_monsterarray[g_monsters].m_hitpoints = 11 + (rand() % 10);
	g_monsters++;
	return true;
}

void RemoveMonster(int p_index)
{
	g_monsters--;
	g_monsterarray[p_index] = g_monsterarray[g_monsters];
}

void CheckMonsters()
{
	int index = 0;
	while (index < g_monsters)
	{
		if (g_monsterarray[index].m_hitpoints <= 0)
		{
			RemoveMonster(index);
		}
		else
		{
			index++;
		}
	}
}

int main()
{
	AddMonster();
	AddMonster();
	AddMonster();

	std::cout << "Added " << g_monsters << " monsters\n";

	g_monsterarray[0].m_hitpoints = 0;

	CheckMonsters();

	std::cout << "After cleanup: " << g_monsters << " monsters\n";
}