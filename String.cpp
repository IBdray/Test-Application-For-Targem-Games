// Тестовое задание на должность "Программист С++" для компании TargemGames выполненное Иваном Бабановым

#include "String.h"

String::String()
	: m_size(0), m_capacity(0), m_data(nullptr) {}

String::String(const char* string)
{
	// Count size of string with '\0'
	m_size = std::strlen(string) + 1;
	m_capacity = m_size;
	m_data = new char[m_size];
	memcpy(m_data, string, m_size);
}

String::String(const String& other)
	: m_size(other.m_size), m_capacity(other.m_capacity)
{
	m_data = new char[m_size];
	memcpy(m_data, other.m_data, m_size);
}

String::String(String&& other) noexcept
	: m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data)
{
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new char[m_size];
		memcpy(m_data, other.m_data, m_size);
	}
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}
	return *this;
}

char& String::operator[](int index) const
{
	return m_data[index];
}

String::~String()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_data;
}

size_t String::GetSize() const
{
	return m_size;
}
size_t String::GetCapacity() const
{
	return m_capacity;
}
const char* String::GetData() const
{
	return m_data;
}

bool String::CheckEmpty() const
{
	return m_size <= 0;
}

size_t String::CalcUnusedCapacity() const
{
	return m_capacity - m_size;
}

size_t String::GetLastIndex() const
{
	return (m_size > 1 ? m_size - 1 : 0);
}

void String::Reserve(size_t newCapacity)
{
	if (newCapacity > m_capacity)
	{
		m_capacity = newCapacity;
		char* newArray = new char[m_capacity];

		// Copy data only if string initialized
		if (m_data != nullptr) 
		{
			for (int i = 0; i < m_size; ++i)
				newArray[i] = m_data[i];
			delete[] m_data;
		}

		m_data = newArray;
		newArray = nullptr;
	}
}

void String::PushBack(const char* string)
{
	size_t stringSize = strlen(string) + 1;

	// Reserve more space for data array if needed
	if (stringSize > CalcUnusedCapacity()) 
		Reserve((m_capacity * 2 > stringSize + m_capacity) ? m_capacity * 2 : stringSize + m_capacity);

	// Copy string to data array starting at index of '\0' or at index 0 if empty
	for (int i = 0; i < stringSize; ++i)
		m_data[i + GetLastIndex()] = string[i];

	// Check if '\0' already been counted in size
	m_size += (m_size == 0 ? stringSize : stringSize - 1);
}

void String::PushBack(char character)
{
	// Reserve more space for data array if needed
	if (CalcUnusedCapacity() < 1)
		Reserve((m_capacity * 2) >= 2 ? m_capacity * 2 : 2);

	// Add char to data array at index of '\0' or at index 0 if empty
	m_data[GetLastIndex()] = character;
	m_data[GetLastIndex() + 1] = 0;

	// Check if '\0' already been counted in size
	m_size += (m_size == 0 ? 2 : 1);
}

void String::Clear() noexcept
{
	for (int i = 0; i < m_size; ++i)
		m_data[i] = 0;
	m_size = 0;
}


bool operator==(const String& firstString, const String& secondString) noexcept
{
	if (firstString.GetSize() != secondString.GetSize())
		return false;

	for (int i = 0; i < firstString.GetSize(); ++i)
		if (firstString[i] != secondString[i]) return false;
	return true;
}

bool operator==(const String& firstString, const char* secondString)
{
	size_t secondStringSize = (secondString == "" || secondString == nullptr) ? 0 : strlen(secondString) + 1;
	if (firstString.GetSize() != secondStringSize)
		return false;

	if (secondString != NULL)
	{
		for (int i = 0; i < firstString.GetSize(); ++i)
			if (firstString[i] != secondString[i]) return false;
	}
	
	return true;
}

bool operator!=(const String& firstString, const String& secondString) noexcept
{
	return !(firstString == secondString);
}

bool operator!=(const String& firstString, const char* secondString)
{
	return !(firstString == secondString);
}

bool operator<(const String& firstString, const String& secondString) noexcept
{
	String str1 = String::ClearNonLetters(firstString);
	String str2 = String::ClearNonLetters(secondString);
	size_t minSize = (str1.GetSize() > str2.GetSize()) ? str2.GetSize() : str1.GetSize();

	for (int i = 0; i < minSize; ++i)
	{
		if (String::CharToLowerCase(str1[i]) < String::CharToLowerCase(str2[i])) return true;
		if (String::CharToLowerCase(str1[i]) > String::CharToLowerCase(str2[i])) return false;
	}
	return str1.GetSize() < str2.GetSize();
}

bool operator<=(const String& firstString, const String& secondString) noexcept
{
	String str1 = String::ClearNonLetters(firstString);
	String str2 = String::ClearNonLetters(secondString);
	size_t minSize = (str1.GetSize() > str2.GetSize()) ? str2.GetSize() : str1.GetSize();

	for (int i = 0; i < minSize; ++i)
	{
		if (String::CharToLowerCase(str1[i]) < String::CharToLowerCase(str2[i])) return true;
		if (String::CharToLowerCase(str1[i]) > String::CharToLowerCase(str2[i])) return false;
	}
	return str1.GetSize() <= str2.GetSize();
}

bool operator>(const String& firstString, const String& secondString) noexcept
{
	String str1 = String::ClearNonLetters(firstString);
	String str2 = String::ClearNonLetters(secondString);
	size_t minSize = (str1.GetSize() > str2.GetSize()) ? str2.GetSize() : str1.GetSize();

	for (int i = 0; i < minSize; ++i)
	{
		if (String::CharToLowerCase(str1[i]) > String::CharToLowerCase(str2[i])) return true;
		if (String::CharToLowerCase(str1[i]) < String::CharToLowerCase(str2[i])) return false;
	}
	return str1.GetSize() > str2.GetSize();
}

bool operator>=(const String& firstString, const String& secondString) noexcept
{
	String str1 = String::ClearNonLetters(firstString);
	String str2 = String::ClearNonLetters(secondString);
	size_t minSize = (str1.GetSize() > str2.GetSize()) ? str2.GetSize() : str1.GetSize();

	for (int i = 0; i < minSize; ++i)
	{
		if (String::CharToLowerCase(str1[i]) > String::CharToLowerCase(str2[i])) return true;
		if (String::CharToLowerCase(str1[i]) < String::CharToLowerCase(str2[i])) return false;
	}
	return str1.GetSize() >= str2.GetSize();
}

String operator+(const String& firstString, const String& secondString)
{
	// Size of two strings minus one of '\0'
	size_t newSize = firstString.GetSize() + secondString.GetSize() - 1;
	char* newString = new char[newSize];

	memcpy(newString, firstString.GetData(), firstString.GetSize());
	strcat_s(newString, newSize, secondString.GetData());

	String result(newString);
	delete[] newString;

	return result;
}

std::istream& operator>>(std::istream& is, String& string)
{
	char character;
	is.get(character);

	while (character != '\n')
	{
		string.PushBack(character);
		is.get(character);
	} 

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	for (int i = 0; i < string.GetSize(); ++i)
		os << string[i];
	return os;
}


char String::CharToLowerCase(const char character)
{
	const int askiiUpperA = 65;
	const int askiiUpperZ = 90;
	const int differenceBetweenCases = 32;

	if (character >= askiiUpperA && character <= askiiUpperZ)
		return character + differenceBetweenCases;
	return character;
}

bool String::CheckIsLetter(const char character)
{
	const int askiiUpperA = 65;
	const int askiiUpperZ = 90;
	const int askiiLowerA = 97;
	const int askiiLowerZ = 122;

	return character >= askiiUpperA && character <= askiiUpperZ || character >= askiiLowerA && character <= askiiLowerZ;
}

String String::ClearNonLetters(const String& string)
{
	String OnlyLettersString;
	OnlyLettersString.Reserve(string.GetSize());

	for (int i = 0; i < string.GetSize(); ++i)
	{
		if (CheckIsLetter(string[i])) OnlyLettersString.PushBack(string[i]);
	}

	return OnlyLettersString;
}
