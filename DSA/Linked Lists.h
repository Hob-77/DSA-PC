#pragma once

template<class Datatype> class SDListNode;
template<class Datatype> class SDLinkedList;
template<class Datatype> class SDListIterator;

template<class Datatype>
class SDListNode
{
public:
	Datatype m_data;
	SDListNode<Datatype>* m_next;
	SDListNode<Datatype>* m_prev;

	void InsertAfter(Datatype p_data)
	{
		// create the new node.
		SDListNode<Datatype>* newnode = new SDListNode<Datatype>;
		newnode->m_data = p_data;
		// make the new node point to the next node.
		newnode->m_next = m_next;
		// make the previous node point to the new node
		newnode->m_prev = this;

		if (m_next != nullptr)
		{
			m_next->m_prev = newnode;
		}
		m_next = newnode;
	}

};

template<class Datatype>
class SDLinkedList
{
public:
	SDListNode<Datatype>* m_head;
	SDListNode<Datatype>* m_tail;
	int m_count;

	SDLinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}

	~SDLinkedList()
	{
		// temporary node pointers.
		SDListNode<Datatype>* itr = m_head;
		SDListNode<Datatype>* next;
		while (itr != 0)
		{
			// save the pointer to the next node.
			next = itr->m_next;
			// delete the current node.
			delete itr;
			// make the next node the current node.
			itr = next;
		}
	}

	void Append(Datatype p_data)
	{
		if (m_head == 0)
		{
			// create a new head node.
			m_head = m_tail = new SDListNode<Datatype>;
			m_head->m_data = p_data;
			m_head->m_next = nullptr;
			m_head->m_prev = nullptr;
		}
		else
		{
			// insert a new node
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_next;
		}
		m_count++;
	}

	void Prepend(Datatype p_data)
	{
		// create the new node.
		SDListNode<Datatype>* newnode = new SDListNode<Datatype>;
		newnode->m_data = p_data;
		newnode->m_next = m_head;
		newnode->m_prev = nullptr;

		if (m_head != nullptr)
		{
			m_head->m_prev = newnode;
		}

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
		SDListNode<Datatype>* node = nullptr;
		if (m_head != nullptr)
		{
			// make node point to the next node.
			node = m_head->m_next;
			// then delete the head and make the pointer
			// point to node.
			delete m_head;
			m_head = node;

			if (m_head != nullptr)
			{
				m_head->m_prev = nullptr;
			}
			else
			{
				m_tail = nullptr;
			}
			m_count--;
		}
	}

	void RemoveTail()
	{
		// if the list isn't empty, then remove a node.
		if (m_tail != 0)
		{
			// if the head is equal to the tail, then the list has 1 node
			if (m_head == m_tail)
			{
				// delete the node and set both pointers to 0.
				delete m_head;
				m_head = m_tail = 0;
			}
			else
			{
				// With doubly linked list, we can directly access previous node!
				SDListNode<Datatype>* node = m_tail->m_prev;
				delete m_tail;
				m_tail = node;
				m_tail->m_next = 0;
			}
			m_count--;
		}
	}

	SDListIterator<Datatype> GetIterator()
	{
		return SDListIterator<Datatype>(this, m_head);
	}

	// inserts an item after the current iterator or appends data if iterator is invalid.
	void Insert(SDListIterator<Datatype>& p_iterator, Datatype p_data)
	{
		// if the iterator doesn't belong to this list, do nothing.
		if (p_iterator.m_list != this)
		{
			return;
		}
		if (p_iterator.m_node != 0)
		{
			// if the iterator is valid, then insert the node
			p_iterator.m_node->InsertAfter(p_data);
			// if the iterator is the tail node, then update the tail pointer to point ot the new node.
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

	void Remove(SDListIterator<Datatype>& p_iterator)
	{
		if (p_iterator.m_list != this || p_iterator.m_node == 0)
			return;

		SDListNode<Datatype>* node = p_iterator.m_node;

		// Move iterator forward before removing
		p_iterator.Forth();

		// Update the previous node's next pointer
		if (node->m_prev != nullptr)
			node->m_prev->m_next = node->m_next;
		else
			m_head = node->m_next;  // We're removing the head

		// Update the next node's prev pointer
		if (node->m_next != nullptr)
			node->m_next->m_prev = node->m_prev;
		else
			m_tail = node->m_prev;  // We're removing the tail

		delete node;
		m_count--;
	}

	bool SaveToDisk(char* p_filename)
	{
		FILE* outfile = 0;
		SDListNode<Datatype>* itr = m_head;
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
class SDListIterator
{
public:
	SDListNode<Datatype>* m_node;
	SDLinkedList<Datatype>* m_list;

	SDListIterator(SDLinkedList<Datatype>* p_list = 0, SDListNode<Datatype>* p_node = 0)
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

	void Back()
	{
		if (m_node != 0)
		{
			m_node = m_node->m_prev;
		}
	}
	
	void End()
	{
		if (m_list != 0)
		{
			m_node = m_list->m_tail;
		}
	}

};