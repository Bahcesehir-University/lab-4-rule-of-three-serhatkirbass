```cpp
// ============================================================================
// Lab: Destructors, Copy Constructors, and Default Memberwise Assignment
// Course: Object-Oriented Programming for Engineers
// File: MainProgram.cpp (Student Version)
// ============================================================================
// INSTRUCTIONS:
//   - Implement all functions marked with TODO
//   - Do NOT change function signatures
//   - Do NOT add extra #include directives
//   - All code must remain in this single file
// ============================================================================

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// ============================================================================
// GLOBAL TRACKING VARIABLES
// ============================================================================

int g_constructorCount     = 0;
int g_destructorCount      = 0;
int g_copyConstructorCount = 0;
int g_assignmentCount      = 0;

// Helper functions to read/reset counters (DO NOT MODIFY)
int getConstructorCount()     { return g_constructorCount; }
int getDestructorCount()      { return g_destructorCount; }
int getCopyConstructorCount() { return g_copyConstructorCount; }
int getAssignmentCount()      { return g_assignmentCount; }

void resetAllCounters() {
    g_constructorCount     = 0;
    g_destructorCount      = 0;
    g_copyConstructorCount = 0;
    g_assignmentCount      = 0;
}

// ============================================================================
// CLASS DEFINITION: DynamicBuffer
// ============================================================================

class DynamicBuffer {
private:
    char* m_data;
    int   m_length;

public:

    // --------------------------------------------------
    // Parameterized Constructor
    // --------------------------------------------------
    DynamicBuffer(const char* input) {

        // 1. Increment constructor counter
        g_constructorCount++;

        // 2. Calculate string length
        m_length = strlen(input);

        // 3. Allocate memory
        m_data = new char[m_length + 1];

        // 4. Copy string
        strcpy(m_data, input);
    }

    // --------------------------------------------------
    // Destructor
    // --------------------------------------------------
    ~DynamicBuffer() {

        // 1. Increment destructor counter
        g_destructorCount++;

        // 2. Free memory
        delete[] m_data;
    }

    // --------------------------------------------------
    // Copy Constructor
    // --------------------------------------------------
    DynamicBuffer(const DynamicBuffer& other) {

        // 1. Increment copy constructor counter
        g_copyConstructorCount++;

        // 2. Copy length
        m_length = other.m_length;

        // 3. Allocate new memory
        m_data = new char[m_length + 1];

        // 4. Copy string data
        strcpy(m_data, other.m_data);
    }

    // --------------------------------------------------
    // Copy Assignment Operator
    // --------------------------------------------------
    DynamicBuffer& operator=(const DynamicBuffer& other) {

        // 1. Increment assignment counter
        g_assignmentCount++;

        // 2. Check self-assignment
        if (this == &other) {
            return *this;
        }

        // 3. Delete old memory
        delete[] m_data;

        // 4. Copy length
        m_length = other.m_length;

        // 5. Allocate new memory
        m_data = new char[m_length + 1];

        // 6. Copy string data
        strcpy(m_data, other.m_data);

        // 7. Return current object
        return *this;
    }

    // --------------------------------------------------
    // Accessors
    // --------------------------------------------------
    const char* getData() const { return m_data; }
    int getLength() const { return m_length; }

    // --------------------------------------------------
    // setData
    // --------------------------------------------------
    void setData(const char* newData) {

        // 1. Delete old memory
        delete[] m_data;

        // 2. Calculate new length
        m_length = strlen(newData);

        // 3. Allocate new memory
        m_data = new char[m_length + 1];

        // 4. Copy new string
        strcpy(m_data, newData);
    }

    // --------------------------------------------------
    // print
    // --------------------------------------------------
    void print() const {
        cout << "DynamicBuffer[\"" << m_data
             << "\", length=" << m_length << "]" << endl;
    }
};

// ============================================================================
// FREE FUNCTION: createBufferCopy
// ============================================================================

DynamicBuffer createBufferCopy(DynamicBuffer buf) {
    return buf;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {

    cout << "=== Destructors, Copy Constructors & Assignment Lab ===" << endl;
    cout << endl;

    // --------------------------------------------------
    // Part 1
    // --------------------------------------------------
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

    // --------------------------------------------------
    // Part 2
    // --------------------------------------------------
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

        // Deep copy test
        original.setData("Modified Original");

        cout << "After modifying original:" << endl;

        cout << "Original: ";
        original.print();

        cout << "Copied:   ";
        copied.print();
    }

    cout << endl;

    resetAllCounters();

    // --------------------------------------------------
    // Part 3
    // --------------------------------------------------
    cout << "--- Part 3: Assignment Operator ---" << endl;

    {
        DynamicBuffer a("Alpha");
        DynamicBuffer b("Beta");

        cout << "Before assignment:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();

        // Assignment operator
        b = a;

        cout << "After b = a:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();

        cout << "Assignment count: "
             << getAssignmentCount() << endl;

        // Deep copy test
        a.setData("Changed A");

        cout << "After modifying a:" << endl;

        cout << "a: ";
        a.print();

        cout << "b: ";
        b.print();
    }

    cout << endl;

    // --------------------------------------------------
    // Part 4
    // --------------------------------------------------
    cout << "--- Part 4: Self-Assignment ---" << endl;

    {
        DynamicBuffer s("SelfTest");

        // Self-assignment
        s = s;

        cout << "After self-assignment: ";
        s.print();
    }

    cout << endl;

    cout << "=== Lab Complete ===" << endl;

    return 0;
}
```
