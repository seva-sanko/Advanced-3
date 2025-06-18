#pragma once
#include <iostream>

class MyString
{
private:
    int size;
    char* m_pStr;
public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator= (const MyString& v);
    void Copy(char* s);
    const char* GetString() const;
    int GetLength();

    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        return os << str.GetString();
    }
};



