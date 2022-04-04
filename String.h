// Тестовое задание на должность "Программист С++" для компании TargemGames выполненное Иваном Бабановым

#pragma once

#include <iostream>
#include <cstring>


class String
{
public:
	// Default constructor
	String();

	String(const char* string);
	String(const String& other);
	String(String&& other) noexcept;

	String& operator= (const String& other);
	String& operator= (String&& other) noexcept;

	// Returns a reference to the char at specified index. 
	// No bounds checking is performed. If pos > size(), the behavior is undefined.
	char& operator[] (int index) const;

	~String();

	friend bool operator== (const String& firstString, const String& secondString) noexcept;
	friend bool operator== (const String& firstString, const char* secondString);
	friend bool operator!= (const String& firstString, const String& secondString) noexcept;
	friend bool operator!= (const String& firstString, const char* secondString);

	friend bool operator< (const String& firstString, const String& secondString) noexcept;
	friend bool operator<= (const String& firstString, const String& secondString) noexcept;
	friend bool operator> (const String& firstString, const String& secondString) noexcept;
	friend bool operator>= (const String& firstString, const String& secondString) noexcept;

	friend String operator+(const String& firstString, const String& secondString);
	friend std::istream& operator>>(std::istream& is, String& string);
	friend std::ostream& operator<<(std::ostream& os, const String& string);

	// Changes max capacity of the string to specified value.
	// If new capacity < capacity, do nothing
	void Reserve(size_t newCapacity);

	void PushBack(const char* string);
	void PushBack(char character);

	// Clears all elements of a string.
	// Does not change capacity.
	void Clear() noexcept;
	bool CheckEmpty() const;

	size_t GetSize() const;
	size_t GetCapacity() const;
	const char* GetData() const;

private:
	size_t m_size;
	size_t m_capacity;
	char* m_data;

	size_t CalcUnusedCapacity() const;
	size_t GetLastIndex() const;

	// Returns copy of specified char transformed to lower case.
	// Does nothing if specified char already in lower case of not a letter.
	static char CharToLowerCase(const char character);
	
	static bool CheckIsLetter(const char character);

	// Creates new string without any non-letter char
	static String ClearNonLetters(const String& string);
};
