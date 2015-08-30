#ifndef ASI_GTEST_HPP
#define ASI_GTEST_HPP

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wconversion-null"
#elif __clang__
#pragma message "warning"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdeprecated"
#endif

#include "gtest/gtest.h"

#if __clang__
#pragma clang diagnostic pop
#endif

#endif //ASI_GTEST_HPP
