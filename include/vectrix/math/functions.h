//
// Created by Timmimin on 12.06.2025.
//

#ifndef VECTRIX_FUNCTIONS_H
#define VECTRIX_FUNCTIONS_H

#include "common.h"

namespace vtx::math {

#ifdef VTX_USE_CONSTEXPR_MATH

    template <typename T>
    constexpr T abs(T x) {
        return x < 0 ? -x : x;
    }

    template <typename T>
    constexpr T min(T a, T b) {
        return a < b ? a : b;
    }

    template <typename T>
    constexpr T max(T a, T b) {
        return a > b ? a : b;
    }

    template <typename T>
    constexpr T clamp(T val, T minVal, T maxVal) {
        return (val < minVal) ? minVal : (val > maxVal ? maxVal : val);
    }

    template <typename T>
    constexpr T lerp(T a, T b, T t) {
        return a + t * (b - a);
    }

    // Simple constexpr sqrt (Newton)
    template <typename T>
    constexpr T sqrt(T x) {
        if (x < 0)
            return T(-1); // Invalid, could be changed to static_assert
        T guess = x / 2;
        for (int i = 0; i < 10; ++i)
            guess = (guess + x / guess) / 2;
        return guess;
    }

#else

    // Wrappers for std-functions (if needed - or just use common.h) possibly
    template <typename T>
    inline T abs(T x) {
        return std::abs(x);
    }

    template <typename T>
    inline T min(T a, T b) {
        return std::min(a, b);
    }

    template <typename T>
    inline T max(T a, T b) {
        return std::max(a, b);
    }

    template <typename T>
    inline T clamp(T val, T minVal, T maxVal) {
        return std::clamp(val, minVal, maxVal);
    }

    template <typename T>
    inline T lerp(T a, T b, T t) {
        return a + t * (b - a);
    }

    template <typename T>
    inline T sqrt(T x) {
        return std::sqrt(x);
    }

#endif // VTX_USE_CONSTEXPR_MATH

} // namespace vtx::math

#endif //VECTRIX_FUNCTIONS_H
