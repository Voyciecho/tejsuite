
#include <string>
#include <unordered_set>
#include <gtest/gtest.h>

namespace {
struct Node
{
    int data;
    struct Node *next;
};

Node *push(Node *head, int val)
{
    // Add new node at the front

    Node *n = new Node;
    n->data = val;
    n->next = head;

    return n;
}

std::string print(Node *head)
{
    // Print contents of the list into a string

    std::string s;

    while (head)
    {
        s += std::to_string(head->data) + " -> ";
        head = head->next;
    }
    s += "null";

    return s;
}

// Method 1: hash table
bool detectLoopWithHashTable(Node *head)
{
    std::unordered_set<Node *> t;
    while (head != NULL)
    {
        if (std::find(t.begin(), t.end(), head) != t.end())
            return true;

        t.insert(head);

        head = head->next;
    }

    return false;
}

// Method 2: Visited Flag
// Add a "visited flag" to each node and walk through list
// until nullptr (no loop) or visited flag set (loop detected)

// Method 3: Floyd’s Cycle-Finding Algorithm
// Create two pointers fast and slow and move fast by 2 nodes,
// while slow by one. Sooner or later fast will catch up with
// slow or will find the end.
bool detectLoopWithFloydAlgo(Node *head)
{
    Node *slow_p = head, *fast_p = head;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p)
            return true;
    }
    return false;
}

}

TEST(LinkedListTest, LinkedListLoopTest) {

    Node *head = nullptr;

    head = push(head, 5);
    head = push(head, 4);
    head = push(head, 3);
    head = push(head, 2);
    head = push(head, 1);

    std::cout << print(head) << "\n";
    EXPECT_EQ(detectLoopWithHashTable(head), false);
    EXPECT_EQ(detectLoopWithFloydAlgo(head), false);

    // Create a loop
    head->next->next->next->next->next = head->next;

    EXPECT_EQ(detectLoopWithHashTable(head), true);
    EXPECT_EQ(detectLoopWithFloydAlgo(head), true);
}
