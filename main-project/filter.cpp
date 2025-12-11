#include "filter.h"
#include <cstring>
#include <iostream>

book_subscription** filter(book_subscription* array[], int size, bool (*check)(book_subscription* element), int& result_size)
{
	book_subscription** result = new book_subscription * [size];
	result_size = 0;
	for (int i = 0; i < size; i++)
	{
		if (check(array[i]))
		{
			result[result_size++] = array[i];
		}
	}
	return result;
}

bool check_book_subscription_by_author(book_subscription* element)
{
	return strcmp(element->author.first_name, "") == 0 &&
		strcmp(element->author.middle_name, "") == 0 &&
		strcmp(element->author.last_name, "") == 0;
}

bool check_book_subscription_by_date(book_subscription* element)
{
	return element->start.month == 3 && element->start.year == 2015;
}
