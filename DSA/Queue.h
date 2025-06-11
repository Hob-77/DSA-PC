#pragma once
#include "DLinkedLists.h"
#include "Array.h"

template<class Datatype>
class LQueue : public DLinkedList<Datatype>
{
public:

	void Enqueue(Datatype p_data)
	{
		Append(p_data);
	}

	void Dequeue()
	{
		RemoveHead();
	}

	Datatype Front()
	{
		return m_head->m_data;
	}
	
	int Count()
	{
		return m_count;
	}

};

template<class Datatype>
class AQueue : public Array<Datatype>
{
public:
	int m_front;
	int m_count;

	AQueue(int p_size) : Array<Datatype>(p_size)
	{
		m_front = 0;
		m_count = 0;
	}

	bool Enqueue(Datatype p_data)
	{
		if (m_size != m_count)
		{
			m_array[(m_count + m_front) % m_size] = p_data;
			m_count++;
			return true;
		}
		return false;
	}

	void Dequeue()
	{
		if (m_count > 0)
		{
			m_count--;
			m_front++;
			if (m_front == m_size)
			{
				m_front = 0;
			}
		}
	}

	Datatype Front()
	{
		return m_array[m_front];
	}

	Datatype& operator[] (int p_index)
	{
		return m_array[(p_index + m_front) % m_size];
	}

	void Resize(int p_newsize)
	{
		if (p_newsize < m_count)
		{
			p_newsize = m_count;
		}

		Datatype* newarray = new Datatype[p_newsize];

		for (int i = 0; i < m_count; i++)
		{
			newarray[i] = m_array[(m_front + i) % m_size];
		}

		if (m_array != 0)
		{
			delete[] m_array;
		}

		m_array = newarray;
		m_size = p_newsize;
		m_front = 0;
	}

};