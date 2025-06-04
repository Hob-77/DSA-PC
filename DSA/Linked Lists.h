#pragma once

template<class Datatype>
class SListNode
{
public:
	Datatype m_data;
	SListNode<Datatype>* m_next;

	void InsertAfter(Datatype p_data)
	{
		// create the new node.
		SListNode<Datatype>* newnode = new SListNode<Datatype>;
		newnode->m_data = p_data;
		// make the new node point to the next node.
		newnode->m_next = m_next;
		// make the previous node point to the new node
		m_next = newnode;
	}

};

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
			// make the next node the current node.
			itr = next;
		}
	}

	void Append(Datatype p_data)
	{
		if (m_head == 0)
		{
			// create a new head node.
			m_head = m_tail = new SListNode<Datatype>;
			m_head->m_data = p_data;
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
			// then delete the head and make the pointer
			// point to node.
			delete m_head;
			m_head = node;
			// if the head is null, than you've just deleted the only node
			// in the list. set the tail to 0.
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

	SListIterator<Datatype> GetIterator()
	{
		return SListIterator<Datatype>(this, m_head);
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