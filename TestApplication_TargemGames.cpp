// Тестовое задание на должность "Программист С++" для компании TargemGames выполненное Иваном Бабановым

#include <iostream>
#include <utility>
#include <vector>

#include "String.h"


void SortArray(std::vector<String>& array)
{
    if (!array.empty())
    {
        for (int i = 0; i < array.size() - 1; ++i)
        {
            for (int j = 0; j < array.size() - i - 1; ++j)
            {
                if (array[j] < array[j + 1])
                {
                    String temp = std::move(array[j]);
                    array[j] = array[j + 1];
                    array[j + 1] = std::move(temp);
                }
            }
        }
    }
}

int main()
{
    std::vector<String> strings;
    String string;

    std::cout << "Programm was made as Test Application for Targem Games by Ivan Babanov." << std::endl << std::endl;

    std::cout << "Please enter list of strings." << std::endl
        << "Application will return your list sorted in reverse lexicographic order case-insensitive." << std::endl
        << "To finish input, enter empty string." << std::endl
        << "======================================================" << std::endl 
        << std::endl
        << "Your input:" << std::endl;

    while (true)
    {
        std::cin >> string;
        if (string == "") break;

        strings.emplace_back(string);
        string.Clear();
    }

    std::cout << "Sorted list:" << std::endl;

    SortArray(strings);
    for (const String& str : strings)
        std::cout << str << std::endl;
}