#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include "MyString.h"
#include <string>
#include <cstring>

//
//void MyString::Copy (char* s)
//{
//    delete [] m_pStr;
//    // Динамически выделяем требуемое количество памяти.
//    int len = strlen(s) + 1;
//    m_pStr = new char[len];
//    // + 1, так как нулевой байт тоже нужно скопировать
//    // Если память выделена, копируем строку-аргумент в строку-член класса
//    if (m_pStr)
//        strcpy(m_pStr,s);
//}
MyString::MyString() {
    this->size = 0;
    this->m_pStr = nullptr;
}

MyString::MyString(const char* other)
{
    if (other == nullptr) {
        m_pStr = nullptr;
        size = 0;
        return;
    }
    else {
        size = strlen(other) + 1;
        m_pStr = new char[size];
        strcpy(m_pStr, other);
    }
}

MyString::MyString(const MyString& other) {
    if (other.m_pStr == nullptr) {
        this->m_pStr = nullptr;
        this->size = 0;
        return;
    }
    else {
        this->size = other.size;
        this->m_pStr = new char[this->size];
        strcpy(m_pStr, other.m_pStr);
    }

}

MyString::~MyString()
{
    delete[] m_pStr;
}


const char* MyString::GetString() const
{
    return m_pStr;
}

int MyString::GetLength()
{
    return size;
}


MyString& MyString::operator= (const MyString& v) {
    if (v.m_pStr == nullptr) {
        this->m_pStr = nullptr;
        this->size = 0;
        return *this;
    }
    if (this == &v)
        return *this;
    delete[] this->m_pStr;
    m_pStr = new char[v.size];
    strcpy(m_pStr, v.m_pStr);
    this->size = v.size;
    return *this;
}
