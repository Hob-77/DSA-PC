#pragma once
#include "DLinkedLists.h"
#include "Array.h"

template<class Datatype>
class Lstack : public DLinkedList<Datatype>
{
public:

	void Push(Datatype p_data)
	{
		Append(p_data);
	}

	void Pop()
	{
		RemoveTail();
	}

	Datatype Top()
	{
		return m_tail->m_data;
	}

	int Count()
	{
		return m_count;
	}

};

template<class Datatype>
class AStack : public Array<Datatype>
{
public:
	int m_top;

	AStack(int p_size) : Array<Datatype>(p_size)
	{
		m_top = 0;
	}

	bool Push(Datatype p_data)
	{
		if (m_size != m_top)
		{
			m_array[m_top] = p_data;
			m_top++;
			return true;
		}
		return false;
	}

	void Pop()
	{
		if (m_top > 0)
		{
			m_top--;
		}
	}

	Datatype Top()
	{
		return m_array[m_top - 1];
	}

	int Count()
	{
		return m_top;
	}

};