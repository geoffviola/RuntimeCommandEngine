#ifndef ASI_GTEST_HPP
#define ASI_GTEST_HPP

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wconversion-null"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#endif

#include "gtest/gtest.h"

#endif // ASI_GTEST_HPP
