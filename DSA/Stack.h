#pragma once
#include "Array.h"
#include "Linked Lists.h"

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
		if (this->m_size != m_top)
		{
			this->m_array[m_top] = p_data;
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
		return this->m_array[m_top - 1];
	}

	int Count()
	{
		return m_top;
	}
};

template<class Datatype>
class LStack : public SDLinkedList<Datatype>
{
public:

	void Push(Datatype p_data)
	{
		this->Append(p_data);
	}

	void Pop()
	{
		this->RemoveTail();
	}

	Datatype Top()
	{
		return this->m_tail->m_data;
	}

	int Count()
	{
		return this->m_count;
	}
};