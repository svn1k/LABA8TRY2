#ifndef FILTER_H
#define FILTER_H

#include "book_subscription.h"

book_subscription** filter(book_subscription* array[], int size, bool (*check)(book_subscription* element), int& result_size);

/*
  <function_name>:
              ,
          true,
    ,

:
    array       -
    size        -
    check       -    .

                   ,
    result_data - ,    - ,



          ,
     (     true)
*/


bool check_book_subscription_by_author(book_subscription* element);

/*
  check_book_subscription_by_author:
      - ,

:
    element -   ,


    true,           ,  false
*/


bool check_book_subscription_by_date(book_subscription* element);

/*
  check_book_subscription_by_date:
      - ,           2021-

:
    element -   ,


    true,           2021- ,  false
*/

#endif
