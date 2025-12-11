#include "filter.h"
#include <cstring>

using namespace std;

PhoneCall** filterPhoneCalls(
    PhoneCall* array[],
    int size,
    bool (*check)(PhoneCall* element),
    int& result_size
) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (check(array[i])) {
            count++;
        }
    }

    PhoneCall** result = new PhoneCall * [count];
    result_size = 0;

    for (int i = 0; i < size; i++) {
        if (check(array[i])) {
            result[result_size] = array[i];
            result_size++;
        }
    }

    return result;
}

bool isMobileCall(PhoneCall* element) {
    return strcmp(element->tariff, "") == 0;
}

bool isNovember2021Call(PhoneCall* element) {
    return element->callDate.month == 11 && element->callDate.year == 2021;
}
