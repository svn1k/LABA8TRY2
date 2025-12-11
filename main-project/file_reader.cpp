#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

Date convertDate(char* str) {
    Date result;
    char* context = NULL;
    char* str_number = strtok_s(str, ".", &context);
    result.day = atoi(str_number);
    str_number = strtok_s(NULL, ".", &context);
    result.month = atoi(str_number);
    str_number = strtok_s(NULL, ".", &context);
    result.year = atoi(str_number);
    return result;
}

Time convertTime(char* str) {
    Time result;
    char* context = NULL;
    char* str_number = strtok_s(str, ":", &context);
    result.hours = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.minutes = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.seconds = atoi(str_number);
    return result;
}

void readPhoneCalls(const char* file_name, PhoneCall* array[], int& size) {
    ifstream file(file_name);
    if (file.is_open()) {
        size = 0;
        char tmp_buffer[MAX_STRING_SIZE];

        file.getline(tmp_buffer, MAX_STRING_SIZE);

        while (!file.eof()) {
            PhoneCall* item = new PhoneCall;

            file >> item->number;

            file >> tmp_buffer;
            item->callDate = convertDate(tmp_buffer);

            file >> tmp_buffer;
            item->startTime = convertTime(tmp_buffer);

            file >> tmp_buffer;
            item->duration = convertTime(tmp_buffer);

            file >> item->tariff;
            file >> item->costPerMinute;

            array[size++] = item;

            file.getline(tmp_buffer, MAX_STRING_SIZE);
        }
        file.close();
    }
    else {
        throw "  ";
    }
}
