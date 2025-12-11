#ifndef FILTER_H
#define FILTER_H

#include "phone_call.h"

PhoneCall** filterPhoneCalls(
    PhoneCall* array[],
    int size,
    bool (*check)(PhoneCall* element),
    int& result_size
);

bool isMobileCall(PhoneCall* element);
bool isNovember2021Call(PhoneCall* element);

#endif
