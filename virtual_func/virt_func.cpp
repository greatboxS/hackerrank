#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Walter 56 99 1
// Jesse 18 403 1
// Pinkman 22 135 2
// White 58 87 2

class Person
{
protected:
    int age;
    std::string name;

    void getCommonData()
    {
        cin >> name >> age;
    }

    void putCommonData()
    {
        cout << name << " " << age << " ";
    }
public:
    virtual void getdata() = 0;
    virtual void putdata() = 0;
};

class Professor : public Person
{
private:
    int publications;
    static int id;
public:
    void getdata()
    {
        getCommonData();
        cin >> publications;
    }

    void putdata()
    {
        putCommonData();
        cout << publications << " " << ++id << std::endl;
    }
};
int Professor::id = 0;


class Student : public Person
{
private:
    int pointArr[6];
    static int id;
    int totalPoint()
    {
        int total = 0;
        for (size_t i = 0; i < 6; i++)
        {
            total += pointArr[i];
        }
        return total;
    }

public:
    void getdata()
    {
        getCommonData();
        for (size_t i = 0; i < 6; i++)
        {
            std::cin >> pointArr[i];
        }
    }

    void putdata()
    {
        putCommonData();
        cout << totalPoint() << " " << ++id << std::endl;
    }
};

int Student::id = 0;


int main()
{

    int n, val;
    cin >> n; //The number of objects that is going to be created.
    Person *per[n];

    for (int i = 0; i < n; i++)
    {

        cin >> val;
        if (val == 1)
        {
            // If val is 1 current object is of type Professor
            per[i] = new Professor;
        }
        else
            per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.
    }

    for (int i = 0; i < n; i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;
}
