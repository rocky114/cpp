#include <iostream>
#include <algorithm>
#include <vector>

class Message
{
private:
    std::string msg {};
    int index {};
public:
    Message(std::string msg, int index) : msg{msg}, index{index}
    {

    }
    const std::string& get_text()
    {
        return msg;
    } 

    bool operator<(const Message& second) 
    {
        return index < second.index;
    }
};

class MessageFactory
{
public:
    static int counter;
    Message create_message(const std::string& text)
    {
        Message m {text, counter};
        counter++;

        return m;
    }
};

class Recipient
{
private:
    std::vector<Message> messages;

    void fix_order()
    {
        std::sort(messages.begin(), messages.end());
    }
public:
    void receive(const Message& msg)
    {
        messages.push_back(msg);
    }

    void print_messages()
    {
        fix_order();

        for (auto& msg : messages) {
            std::cout << msg.get_text() << std::endl;
        }

        messages.clear();
    }
};

class Network
{
public:
    static void send_messages(std::vector<Message> messages, Recipient& recipient)
    {
        std::random_shuffle(messages.begin(), messages.end());
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};

int MessageFactory::counter = 1;

int main()
{    
    MessageFactory message_factory {};
    Recipient recipient {};

    std::vector<Message> messages;
    std::string text;

    while (std::getline(std::cin, text))
    {
        messages.push_back(message_factory.create_message(text));
    }

    Network::send_messages(messages, recipient);
    recipient.print_messages();
    
    return 0;
}