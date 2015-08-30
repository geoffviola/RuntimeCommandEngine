#ifndef ASI_GTEST_HPP
#define ASI_GTEST_HPP

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wconversion-null"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif

#include "gtest/gtest.h"

#endif //ASI_GTEST_HPP
