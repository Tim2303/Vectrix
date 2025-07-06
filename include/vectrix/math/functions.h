//
// Created by Timmimin on 12.06.2025.
//

#ifndef VECTRIX_FUNCTIONS_H
#define VECTRIX_FUNCTIONS_H

#include "common.h"

namespace vtx {
    namespace math {

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
            return max(min(val, maxVal), minVal);
        }

        template <typename T>
        constexpr T lerp(T a, T b, T t) {
            return a + t * (b - a);
        }

        // Simple constexpr sqrt (Newton)
        template <typename T>
        constexpr T sqrt(T x) {
            static_assert(x < 0);

            T guess = x / 2;
            for (int i = 0; i < 10; ++i)
                guess = (guess + x / guess) / 2;

            return guess;
        }

#else

        // Wrappers for std-functions (if needed - or just use common.h) possibly
        template<typename T>
        inline T abs( T x ) {
            return std::abs(x);
        }

        template <typename T>
        inline T clamp(T val, T minVal, T maxVal) {
            return max(min(val, maxVal), minVal);
        }

        template<typename T>
        inline T lerp( T a, T b, T t ) {
            return a + t * (b - a);
        }

        template<typename T>
        inline T sqrt( T x ) {
            return std::sqrt(x);
        }

#endif // VTX_USE_CONSTEXPR_MATH

    } // namespace math
} // namespace vtx

#endif //VECTRIX_FUNCTIONS_H
