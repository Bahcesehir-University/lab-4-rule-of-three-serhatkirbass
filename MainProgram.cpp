#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int g_constructorCount = 0;
int g_destructorCount = 0;
int g_copyConstructorCount = 0;
int g_assignmentCount = 0;

int getConstructorCount() { return g_constructorCount; }
int getDestructorCount() { return g_destructorCount; }
int getCopyConstructorCount() { return g_copyConstructorCount; }
int getAssignmentCount() { return g_assignmentCount; }

void resetAllCounters() {
    g_constructorCount = 0;
    g_destructorCount = 0;
    g_copyConstructorCount = 0;
    g_assignmentCount = 0;
}

class DynamicBuffer {
private:
    char* m_data;
    int m_length;

public:
    DynamicBuffer(const char* input) {
        g_constructorCount++;
        m_length = strlen(input);
        m_data = new char[m_length + 1];
        strcpy(m_data, input);
    }

    ~DynamicBuffer() {
        g_destructorCount++;
        delete[] m_data;
    }

    DynamicBuffer(const DynamicBuffer& other) {
        g_copyConstructorCount++;
        m_length = other.m_length;
        m_data = new char[m_length + 1];
        strcpy(m_data, other.m_data);
    }

    DynamicBuffer& operator=(const DynamicBuffer& other) {
        g_assignmentCount++;

        if (this == &other) {
            return *this;
        }

        delete[] m_data;

        m_length = other.m_length;
        m_data = new char[m_length + 1];
        strcpy(m_data, other.m_data);

        return *this;
    }

    const char* getData() const { return m_data; }
    int getLength() const { return m_length; }

    void setData(const char* newData) {
        delete[] m_data;

        m_length = strlen(newData);
        m_data = new char[m_length + 1];
        strcpy(m_data, newData);
    }

    void print() const {
        cout << "DynamicBuffer[\"" << m_data
             << "\", length=" << m_length << "]" << endl;
    }
};

DynamicBuffer createBufferCopy(DynamicBuffer buf) {
    return buf;
}

int main() {
    cout << "=== Destructors, Copy Constructors & Assignment Lab ===" << endl;
    cout << endl;

    cout << "--- Part 1: Constructor & Destructor ---" << endl;

    {
        DynamicBuffer b1("Hello");

        b1.print();

        cout << "b1 created. Constructor count: "
             << getConstructorCount() << endl;
    }

    cout << "b1 destroyed. Destructor count: "
         << getDestructorCount() << endl;

    cout << endl;

    resetAllCounters();

    cout << "--- Part 2: Copy Constructor ---" << endl;

    {
        DynamicBuffer original("Deep Copy Test");

        DynamicBuffer copied(original);

        cout << "Original: ";
        original.print();

        cout << "Copied:   ";
        copied.print();

        cout << "Copy constructor count: "
             << getCopyConstructorCount() << endl;

        original.setData("Modified Original");

        cout << "After modifying original:" << endl;

        cout << "Original: ";
        original.print();

        cout << "Copied:   ";
        copied.print();
    }

    cout << endl;

    resetAllCounters();

    cout << "--- Part 3: Assignment Operator ---" << endl;

    {
        DynamicBuffer a("Alpha");
        DynamicBuffer b("Beta");

        cout << "Before assignment:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();

        b = a;

        cout << "After b = a:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();

        cout << "Assignment count: "
             << getAssignmentCount() << endl;

        a.setData("Changed A");

        cout << "After modifying a:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();
    }

    cout << endl;

    cout << "--- Part 4: Self-Assignment ---" << endl;

    {
        DynamicBuffer s("SelfTest");

        s = s;

        cout << "After self-assignment: ";
        s.print();
    }

    cout << endl;

    cout << "=== Lab Complete ===" << endl;

    return 0;
}
