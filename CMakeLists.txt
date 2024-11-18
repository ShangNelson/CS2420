cmake_minimum_required(VERSION 3.27)
project(CS2420)

set(CMAKE_CXX_STANDARD 14)

include_directories("1.1 No Brainer")
include_directories("1.2 Try")
include_directories("1.4 Dates")
include_directories(2.1)
include_directories(2.2)
include_directories("2.4 Range")
include_directories(3.1)
include_directories("3.4 Collection Pointers")
include_directories(4.1)

add_executable(CS2420
        "1.1 No Brainer/Point.h"
        "1.1 No Brainer/PointOverloadedOperators.cpp"
        "1.2 Try/Distance.cpp"
        "1.2 Try/Distance.h"
        "1.4 Dates/Date.h"
        "1.4 Dates/DateTesting.cpp"
        "1.4 Dates/main.cpp"
        2.1/Point.h
        2.1/PointOverloadedOperators.cpp
        2.2/Dictionary.h
        2.2/main.cpp
        "2.4 Range/Range.h"
        "2.4 Range/RangeTesting.cpp"
        3.1/Collection.h
        3.1/CollectionTesting.cpp
        "3.4 Collection Pointers/Collection.h"
        "3.4 Collection Pointers/SortedCollection.h"
        "3.4 Collection Pointers/SortedCollectionTesting.cpp"
        4.1/Palindrome.h
        4.1/PalindromeTester.cpp
        testingTryItOuts.cpp)
