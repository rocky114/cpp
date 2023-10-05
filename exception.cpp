#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class BadLengthException : public exception
{
public:
    BadLengthException(int length) : message_(to_string(length)) {}
    const char *what() const noexcept override { return message_.c_str(); }

private:
    string message_;
};

bool checkUsername(string username)
{
    bool isValid{true};

    int n = username.length();
    if (n < 5)
    {
        throw BadLengthException(n);
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (username[i] == 'w' && username[i + 1] == 'w')
        {
            isValid = false;
        }
    }

    return isValid;
}

int main()
{
    int n;

    cin >> n;

    while (n--)
    {
        string username;
        cin >> username;

        try
        {
            bool isValid = checkUsername(username);
            if (isValid)
            {
                cout << "Valid" << endl;
            }
            else
            {
                cout << "Invalid" << endl;
            }
        }
        catch (BadLengthException e)
        {
            cout << "Too short: " << e.what() << endl;
        }
    }

    return 0;
}