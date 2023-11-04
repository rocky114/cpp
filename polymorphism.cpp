#include <iostream>
#include <map>

struct Node
{
    Node *next;
    Node *prev;
    int value;
    int key;

    Node(Node *p, Node *n, int k, int val) : prev{p}, next{n}, key{k}, value{val} {};
    Node(int k, int val) : prev(nullptr), next{nullptr}, key{k}, value{val} {}
};

class Cache
{
protected:
    std::map<int, Node *> mp;
    int cp;
    Node *tail;
    Node *head;
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;
};

class LRUCache : public Cache
{
private:
    void update_usage(int k)
    {
        auto node = mp[k];
        if (node == head || node == tail)
            return;

        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = nullptr;
        node->next = head;
        head->prev = node;
        head = node;
    }

public:
    void set(int k, int v) override
    {
        if (mp.find(k) != mp.end())
        {
            mp[k]->value = v;
            update_usage(k);
        }
        else
        {
            Node *new_node = new Node(k, v);
            if (head == nullptr)
            {
                head = new_node;
                tail = new_node;
                mp[k] = new_node;
                return;
            }

            if (mp.size() >= cp)
            {
                mp.erase(tail->key);

                auto new_tail = tail->prev;
                tail->prev->next = nullptr;
                tail = new_node;
            }

            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            mp[k] = new_node;
        }
    }

    int get(int k) override
    {
        if (mp.find(k) != mp.end())
        {
            update_usage(k);

            return mp[k]->value;
        }
        else
        {
            return -1;
        }
    }

    LRUCache(int capacity)
    {
        cp = capacity;
    }
};

int main()
{
    int n, capacity, i;
    std::cin >> n >> capacity;

    LRUCache l(capacity);

    for (i = 0; i < n; i++)
    {
        std::string command;
        std::cin >> command;

        if (command == "get")
        {
            int key;
            std::cin >> key;

            std::cout << l.get(key) << std::endl;
        }
        else if (command == "set")
        {
            int key, value;
            std::cin >> key >> value;

            l.set(key, value);
        }
    }

    return 0;
}