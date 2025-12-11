#ifndef SORT_H
#define SORT_H

#include "phone_call.h"

//   
void heapSort(PhoneCall* array[], int size, int (*compare)(PhoneCall*, PhoneCall*));
void quickSort(PhoneCall* array[], int size, int (*compare)(PhoneCall*, PhoneCall*));

//   
int compareByDurationDesc(PhoneCall* a, PhoneCall* b);    //   
int compareByNumberAndCost(PhoneCall* a, PhoneCall* b);   //   () +  ()

#endif
