#pragma once

template<class Datatype>
class SListNode
{
public:
	Datatype m_data;
	SListNode<Datatype>* m_next;

	void InsertAfter(Datatype p_data)
	{
		// create the new node
		SListNode<Datatype>* newnode = new SListNode<Datatype>;
		newnode->m_data = p_data;
		// make the new node point to the next node.
		newnode->m_next = m_next;
		// make the previous node point to the new node
		m_next = newnode;
	}
};

template<class Datatype>
class SListIterator;

template<class Datatype>
class SLinkedList
{
public:
	SListNode<Datatype>* m_head;
	SListNode<Datatype>* m_tail;
	int m_count;

	SLinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}

	~SLinkedList()
	{
		// temporary node pointers.
		SListNode<Datatype>* itr = m_head;
		SListNode<Datatype>* next;
		while (itr != 0)
		{
			// save the pointer to the next node.
			next = itr->m_next;
			// delete the current node.
			delete itr;
			// make teh next node the current node.
			itr = next;
		}
	}

	void Append(Datatype p_data)
	{
		if (m_head == 0)
		{
			// create a new head node
			m_head = m_tail = new SListNode<Datatype>;
			m_head->m_data = p_data;
		}
		else
		{
			// insert a new node after the tail and reset the tail
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_next;
		}
		m_count++;
	}

	void Prepend(Datatype p_data)
	{
		// create the new node.
		SListNode<Datatype>* newnode = new SListNode<Datatype>;
		newnode->m_data = p_data;
		newnode->m_next = m_head;
		// set the head node and the tail node if needed.
		m_head = newnode;
		if (m_tail == 0)
		{
			m_tail = m_head;
		}
		m_count++;
	}

	void RemoveHead()
	{
		SListNode<Datatype>* node = 0;
		if (m_head != 0)
		{
			// make node point to the next node.
			node = m_head->m_next;
			// then delete the ehad and make the pointer
			// point to the node.
			delete m_head;
			m_head = node;
			// if the head is null, than you've just deleted the only node in the list. set the tail to 0.
			if (m_head == 0)
			{
				m_tail = 0;
			}
			m_count--;
		}
	}

	void RemoveTail()
	{
		SListNode<Datatype>* node = m_head;
		// if the list isn't empty, then remove a node.
		if (m_head != 0)
		{
			// if the head is equal to the tail, then the list has 1 node, and you are removing it.
			if (m_head == m_tail)
			{
				// delete the node and set both pointers to 0.
				delete m_head;
				m_head = m_tail = 0;
			}
			else
			{
				// skip ahead until you find the node right before the tail node
				while (node->m_next != m_tail)
				{
					node = node->m_next;
				}
				// make the tail point to the node before the current tail and delete the old tail.
				m_tail = node;
				delete node->m_next;
				node->m_next = 0;
			}
			m_count--;
		}
	}

	// inserts an item after the current iterator or appends data if iterator is invalid.
	void Insert(SListIterator<Datatype>& p_iterator, Datatype p_data)
	{
		// if the iterator doesn’t belong to this list, do nothing. 
		if (p_iterator.m_list != this)
		{
			return;
		}
		if (p_iterator.m_node != 0)
		{
			// if the iterator is valid, then insert the node
			p_iterator.m_node->InsertAfter(p_data);
			// if the iterator is the tail node, then
			// update the tail pointer to point to the
			// new node.
			if (p_iterator.m_node == m_tail)
			{
				m_tail = p_iterator.m_node->m_next;
			}
			m_count++;
		}
		else
		{
			// if the iterator is invalid, just append the data
			Append(p_data);
		}
	}

	void Remove(SListIterator<Datatype>& p_iterator)
	{
		SListNode<Datatype>* node = m_head;
		// if the iterator doesn’t belong to this list, do nothing.
		if (p_iterator.m_list != this)
		{
			return;
		}
		// if node is invalid, do nothing.
		if (p_iterator.m_node == 0)
		{
			return;
		}
		if (p_iterator.m_node == m_head)
		{
			// move the iterator forward and delete the head.
			p_iterator.Forth();
			RemoveHead();
		}
		else
		{
			// scan forward through the list until you find 
		   // the node prior to the node you want to remove 
			while (node->m_next != p_iterator.m_node)
			{
				node = node->m_next;
			}
			// move the iterator forward. 
			p_iterator.Forth();
			// if the node you are deleting is the tail, 
			// update the tail node. 
			if (node->m_next == m_tail)
			{
				m_tail = node;
			}
			// delete the node.
			delete node->m_next;
			// re-link the list.
			node->m_next = p_iterator.m_node;
		}
		m_count--;
	}

	SListIterator<Datatype> GetIterator()
	{
		return SListIterator<Datatype>(this, m_head);
	}

	bool SaveToDisk(char* p_filename)
	{
		FILE* outfile = 0;
		SListNode* itr = m_head;
		outfile = fopen(p_filename, "wb");
		if (outfile == 0)
		{
			return false;
		}
		fwrite(&m_count, sizeof(int), 1, outfile);
		while (itr != 0)
		{
			fwrite(&(itr->m_data), sizeof(Datatype), 1, outfile);
			itr = itr->m_next;
		}
		fclose(outfile);
		return true;
	}

	bool ReadFromDisk(char* p_filename)
	{
		FILE* infile = 0;
		Datatype buffer;
		int count = 0;
		infile = fopen(p_filename, "rb");
		if (infile == 0)
		{
			return false;
		}
		fread(&count, sizeof(int), 1, infile);
		while (count != 0)
		{
			fread(&buffer, sizeof(Datatype), 1, infile);
			Append(buffer);
			count--;
		}
		fclose(infile);
		return true;
	}
	
};

template<class Datatype>
class SListIterator
{
public:
	SListNode<Datatype>* m_node;
	SLinkedList<Datatype>* m_list;

	SListIterator(SLinkedList<Datatype>* p_list = 0, SListNode<Datatype>* p_node = 0)
	{
		m_list = p_list;
		m_node = p_node;
	}

	void Start()
	{
		if (m_list != 0)
		{
			m_node = m_list->m_head;
		}
	}

	void Forth()
	{
		if (m_node != 0)
		{
			m_node = m_node->m_next;
		}
	}

	Datatype& Item()
	{
		return m_node->m_data;
	}

	bool Valid()
	{
		return (m_node != 0);
	}

};