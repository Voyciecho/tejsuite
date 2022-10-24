
#include <string>
#include <gtest/gtest.h>

namespace {

struct Node
{
    int *data;
    struct Node *next;
};

class LinkedList
{
public:
    LinkedList() : m_head(nullptr)
    {}

    ~LinkedList()
    {
        while (pop_front()) ;
    }

    Node *push_front(int val);
    Node *pop_front();
    void reverse();

    bool empty() const;
    int sum() const;
    std::string print() const;

private:
    Node *m_head;
};

Node *LinkedList::push_front(int val)
{
    // Add new node at the front

    Node *n = new Node;
    n->data = new int(val);
    n->next = m_head;
    m_head = n;

    return m_head;
}

Node *LinkedList::pop_front()
{
    // pop_front latest node

    if (!empty())
    {
        Node *n = m_head->next;
        delete m_head->data;
        delete m_head;
        m_head = n;
    }

    return m_head;
}

void LinkedList::reverse()
{
    // Step through the linked list and reverse order

    if (m_head && m_head->next)
    {
        Node *prev = nullptr;
        Node *next = m_head->next;

        while(m_head && m_head->next)
        {
            // Swap direction on current node
            m_head->next = prev;

            // Move to the next node
            prev   = m_head;
            m_head = next;
            next   = m_head->next;
        }

        // Swap direction of the last node
        m_head->next = prev;
    }
}

bool LinkedList::empty() const
{
    return (m_head ? false : true);
}

int LinkedList::sum() const
{
    // Calculate the sum of all data

    int sum = 0;
    Node *head = m_head;

    while (head)
    {
        sum += *(head->data);
        head = head->next;
    }

    return sum;
}

std::string LinkedList::print() const
{
    // Print contents of the list into a string

    std::string s;
    Node *head = m_head;

    while (head)
    {
        s += std::to_string(*(head->data)) + " -> ";
        head = head->next;
    }
    s += "null";

    return s;
}

}

TEST(LinkedListTest, LinkedListReverseTest) {

    LinkedList list{};

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    EXPECT_EQ(list.sum(), 10);
    EXPECT_EQ(list.print().compare("4 -> 3 -> 2 -> 1 -> null"), 0);
    std::cout << "Sum: " << list.sum() << " Nodes: " << list.print() << std::endl;

    list.pop_front();
    EXPECT_EQ(list.sum(), 6);
    EXPECT_EQ(list.print().compare("3 -> 2 -> 1 -> null"), 0);
    std::cout << "Sum: " << list.sum() << " Nodes: " << list.print() << std::endl;

    list.reverse();
    EXPECT_EQ(list.sum(), 6);
    EXPECT_EQ(list.print().compare("1 -> 2 -> 3 -> null"), 0);
    std::cout << "Sum: " << list.sum() << " Nodes: " << list.print() << std::endl;

    list.pop_front();
    EXPECT_EQ(list.sum(), 5);
    EXPECT_EQ(list.print().compare("2 -> 3 -> null"), 0);
    std::cout << "Sum: " << list.sum() << " Nodes: " << list.print() << std::endl;

    list.pop_front();
    list.pop_front();
    std::cout << "Sum: " << list.sum() << " Nodes: " << list.print() << std::endl;
    EXPECT_EQ(list.sum(), 0);
    EXPECT_EQ(list.print().compare("null"), 0);

    list.pop_front();
    EXPECT_EQ(list.sum(), 0);
    EXPECT_EQ(list.print().compare("null"), 0);
}
