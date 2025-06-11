#pragma once
#include "DLinkedLists.h"

template<class KeyType, class DataType>
class HashEntry
{
public:
	KeyType m_key;
	DataType m_data;
};

template<class KeyType, class DataType>
class HashTable
{
public:
	typedef HashEntry<KeyType, DataType> Entry;
	int m_size;
	int m_count;
	Array<DLinkedList<Entry>> m_table;
	unsigned long int (*m_hash)(KeyType);

	HashTable(int p_size, unsigned long int (*p_hash)(KeyType)) : m_table(p_size)
	{
		// set the size, hash function, and count
		m_size = p_size;
		m_hash = p_hash;
		m_count = 0;
	}

	void Insert(KeyType p_key, DataType p_data)
	{
		Entry entry;
		entry.m_data = p_data;
		entry.m_key = p_key;
		int index = m_hash(p_key) % m_size;
		m_table[index].Append(entry);
		m_count++;
	}

	Entry* Find(KeyType p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListIterator<Entry> itr = m_table[index].GetIterator();
		while (itr.Valid())
		{
			if (itr.Item().m_key == p_key)
			{
				return &(itr.Item());
			}
			itr.Forth();
		}
		return 0;
	}

	bool Remove(KeyType p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListIterator<Entry> itr = m_table[index].GetIterator();
		while (itr.Valid))
		{
			if (itr.Item().m_key == p_key)
			{
				m_table[index].Remove(itr);
				m_count--;
				return true;
			}
			itr.Forth();
		}
		return false;
	}

};