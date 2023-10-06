#include <iostream>

using namespace std;

class Person
{
private:
    string name{};
    int age{};

public:
    virtual void getdata()
    {
        cin >> name >> age;
    }

    virtual void putdata()
    {
        cout << name << " " << age << " ";
    }
};

class Professor : public Person
{
private:
    static int idp;
    int cur_id{};
    int publications{};

public:
    Professor()
    {
        cur_id = ++idp;
    }

    void getdata() override
    {
        Person::getdata();
        cin >> publications;
    }

    void putdata() override
    {
        Person::putdata();
        cout << publications << " " << cur_id << endl;
    }
};

class Student : public Person
{
private:
    int marks[6]{};
    static int ids;
    int cur_id;
    int sum = 0;

public:
    Student()
    {
        cur_id = ++ids;
    }

    void getdata() override
    {
        Person::getdata();

        for (int i = 0; i < 6; i++)
        {
            cin >> marks[i];
            sum += marks[i];
        }
    }

    void putdata() override
    {
        Person::putdata();
        cout << sum << " " << cur_id << endl;
    }
};

int Professor::idp = 0;
int Student::ids = 0;

int main()
{
    int n, val;
    cin >> n;

    Person *per[n];

    for (int i = 0; i < n; i++)
    {
        cin >> val;

        if (val == 1)
        {
            per[i] = new Professor;
        }
        else
        {
            per[i] = new Student;
        }

        per[i]->getdata();
    }

    for (int i = 0; i < n; i++)
    {
        per[i]->putdata();
    }

    return 0;
}