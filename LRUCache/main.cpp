#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node
{
    Node *next;
    Node *prev;
    int value;
    int key;
    Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val){};
    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val){};
};

class Cache
{

protected:
    map<int, Node *> mp;            //map the key to the node in the linked list
    int cp;                         //capacity
    Node *tail;                     // double linked list tail pointer
    Node *head;                     // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0;       //get function
};

class LRUCache : protected Cache
{
private:
    void mClean()
    {
        head = nullptr;
        tail = nullptr;
        for (auto i = mp.begin(); i != mp.end(); i++)
        {
            if (i->second)
            {
                delete i->second;
            }
        }
        mp.clear();
    }

    inline const int gMapSize()
    {
        return mp.size();
    }

    inline const int mMapInsert(int key, Node *node)
    {
        mp.insert(make_pair(key, node));
        return mp.size();
    }

    inline void mMapRemove(std::map<int, Node *>::iterator key)
    {
        mp.erase(key);
    }

    /**
     * @brief 
     * 
     * @param iNode insert node
     * @param pNode node to be insert iNode to
     */
    void mInsertNode(Node *iNode, Node *pNode)
    {
        if (!iNode || !pNode)
            return;

        iNode->prev = pNode->prev;
        iNode->next = pNode;
        pNode->prev = iNode;
    }

    /**
     * @brief Insert iNode to the first Node
     *  Its prev node is head 
     * 
     * @param iNode 
     */
    void mInsert2Head(Node *iNode)
    {
        mInsertNode(iNode, head);
        head = iNode;
    }

    int mPickNode(Node *rNode)
    {
        if (!rNode)
            return -1;
        Node *next = rNode->next;
        Node *prev = rNode->prev;

        if (next)
            next->prev = prev;
        if (prev)
            prev->next = next;

        rNode->prev = NULL;
        rNode->next = NULL;

        /**
         * check if picked node is a head or tail node
         * reset value of head or tail if true
         */
        if (rNode == tail)
            tail = prev;

        if (rNode == head)
            head = next;
        return 0;
    }

    void mDeleteNode(Node *dNode)
    {
        if (dNode)
        {
            delete dNode;
            dNode = NULL;
        }
    }

public:
    LRUCache(int capacity)
    {
        cp = capacity;
        head = tail = NULL;
    }
    ~LRUCache()
    {
        mClean();
    }

    void set(int key, int value) override
    {
        bool found = false;
        auto fKey = mp.find(key);
        Node *node = NULL;
        Node *lastNode = NULL;

        if (fKey != mp.end())
        {
            found = true;
        }

        if (found)
        {
            node = fKey->second;
            node->value = value;
            if (mPickNode(node) == 0)
            {
                mInsert2Head(node);
            }
        }
        else
        {
            node = new Node(key, value);

            if (gMapSize() < cp)
            {
                if (mMapInsert(key, node) == 1)
                {
                    head = node;
                    tail = node;
                }
                mInsert2Head(node);
            }
            else
            {
                if (tail)
                {
                    auto lastKey = mp.find(tail->key);
                    if (lastKey != mp.end())
                    {
                        lastNode = lastKey->second;
                        mPickNode(lastNode);
                        mDeleteNode(lastNode);
                        mMapRemove(lastKey);

                        mInsert2Head(node);
                        mMapInsert(key, node);
                    }
                }
            }
        }
    }

    int get(int key) override
    {
        int ret = -1;
        Node *foundNode = NULL;
        auto fKey = mp.find(key);

        if (fKey != mp.end())
        {
            foundNode = fKey->second;
            if (foundNode)
            {
                ret = foundNode->value;
                mPickNode(foundNode);
                mInsert2Head(foundNode);
            }
        }
        return ret;
    }
};

int main()
{
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++)
    {
        string command;
        cin >> command;
        if (command == "get")
        {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set")
        {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
