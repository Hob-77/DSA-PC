#pragma once

template<class Datatype>
class DListNode
{
public:
    Datatype m_data;
    DListNode<Datatype>* m_next;
    DListNode<Datatype>* m_prev;  // Added for doubly linked

    void InsertAfter(Datatype p_data)
    {
        // Following the book's 5-step algorithm:
        // L = this, R = this->m_next, N = newnode

        // Step 1: Create a new node, N
        DListNode<Datatype>* newnode = new DListNode<Datatype>;
        newnode->m_data = p_data;

        // Step 2: Make N's previous pointer point to L
        newnode->m_prev = this;

        // Step 3: Make N's next pointer point to R
        newnode->m_next = m_next;

        // Step 4: L exists (it's this), make L's next point to N
        m_next = newnode;

        // Step 5: If R exists, make R's previous pointer point to N
        if (newnode->m_next != 0)
        {
            newnode->m_next->m_prev = newnode;
        }
    }

};

template<class Datatype>
class DListIterator;

template<class Datatype>
class DLinkedList
{
public:
    DListNode<Datatype>* m_head;
    DListNode<Datatype>* m_tail;
    int m_count;

    DLinkedList()
    {
        m_head = 0;
        m_tail = 0;
        m_count = 0;
    }

    ~DLinkedList()
    {
        // Same as singly linked list
        DListNode<Datatype>* itr = m_head;
        DListNode<Datatype>* next;
        while (itr != 0)
        {
            next = itr->m_next;
            delete itr;
            itr = next;
        }
    }

    void Append(Datatype p_data)
    {
        if (m_head == 0)
        {
            // create a new head node
            m_head = m_tail = new DListNode<Datatype>;
            m_head->m_data = p_data;
            m_head->m_next = 0;
            m_head->m_prev = 0;  // No previous for first node
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
        // Using 5-step algorithm: L = null, R = m_head

        // Step 1: Create the new node
        DListNode<Datatype>* newnode = new DListNode<Datatype>;
        newnode->m_data = p_data;

        // Step 2: Make N's previous pointer point to L (null)
        newnode->m_prev = 0;

        // Step 3: Make N's next pointer point to R (m_head)
        newnode->m_next = m_head;

        // Step 4: L is null, so skip

        // Step 5: If R exists (m_head), make R's previous point to N
        if (m_head != 0)
        {
            m_head->m_prev = newnode;
        }

        // set the head node and the tail node if needed
        m_head = newnode;
        if (m_tail == 0)
        {
            m_tail = m_head;
        }
        m_count++;
    }

    void RemoveHead()
    {
        DListNode<Datatype>* node = 0;
        if (m_head != 0)
        {
            node = m_head->m_next;
            delete m_head;
            m_head = node;

            // Update new head's prev pointer
            if (m_head != 0)
            {
                m_head->m_prev = 0;
            }
            else
            {
                m_tail = 0;
            }
            m_count--;
        }
    }

    void RemoveTail()
    {
        if (m_head != 0)
        {
            if (m_head == m_tail)
            {
                delete m_head;
                m_head = m_tail = 0;
            }
            else
            {
                // Use prev pointer - much simpler!
                DListNode<Datatype>* newTail = m_tail->m_prev;
                delete m_tail;
                m_tail = newTail;
                m_tail->m_next = 0;
            }
            m_count--;
        }
    }

    void Insert(DListIterator<Datatype>& p_iterator, Datatype p_data)
    {
        if (p_iterator.m_list != this)
        {
            return;
        }
        if (p_iterator.m_node != 0)
        {
            p_iterator.m_node->InsertAfter(p_data);
            if (p_iterator.m_node == m_tail)
            {
                m_tail = p_iterator.m_node->m_next;
            }
            m_count++;
        }
        else
        {
            Append(p_data);
        }
    }

    void Remove(DListIterator<Datatype>& p_iterator)
    {
        if (p_iterator.m_list != this)
        {
            return;
        }
        if (p_iterator.m_node == 0)
        {
            return;
        }

        DListNode<Datatype>* node = p_iterator.m_node;

        // Move iterator forward before deleting
        p_iterator.Forth();

        // Update connections
        if (node == m_head)
        {
            m_head = node->m_next;
            if (m_head != 0)
            {
                m_head->m_prev = 0;
            }
        }
        else
        {
            node->m_prev->m_next = node->m_next;
        }

        if (node == m_tail)
        {
            m_tail = node->m_prev;
            if (m_tail != 0)
            {
                m_tail->m_next = 0;
            }
        }
        else
        {
            if (node->m_next != 0)
            {
                node->m_next->m_prev = node->m_prev;
            }
        }

        // Delete the node
        delete node;
        m_count--;

        // Handle empty list
        if (m_count == 0)
        {
            m_head = m_tail = 0;
        }
    }

    DListIterator<Datatype> GetIterator()
    {
        return DListIterator<Datatype>(this, m_head);
    }

    bool SaveToDisk(char* p_filename)
    {
        FILE* outfile = 0;
        DListNode<Datatype>* itr = m_head;
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
class DListIterator
{
public:
    DListNode<Datatype>* m_node;
    DLinkedList<Datatype>* m_list;

    DListIterator(DLinkedList<Datatype>* p_list = 0, DListNode<Datatype>* p_node = 0)
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

    void End()
    {
        if (m_list != 0)
        {
            m_node = m_list->m_tail;
        }
    }

    void Forth()
    {
        if (m_node != 0)
        {
            m_node = m_node->m_next;
        }
    }

    void Back()
    {
        if (m_node != 0)
        {
            m_node = m_node->m_prev;
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