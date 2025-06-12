//
// Created by Timmimin on 12.06.2025.
//

#ifndef VECTRIX_COMMON_H
#define VECTRIX_COMMON_H

#include <cmath>
#include <algorithm> // std::min, std::max
#include <limits>    // std::numeric_limits

namespace vtx {
    namespace math {
        // Constants definition
        constexpr double PI = 3.14159265358979323846; // Pi constant
        constexpr double D2R = PI / 180.0; // Degrees to radians
        constexpr double R2D = 180.0 / PI; // Radians to degrees

        using std::abs;
        using std::sqrt;
        using std::pow;
        using std::sin;
        using std::cos;
        using std::tan;
        using std::asin;
        using std::acos;
        using std::atan;
        using std::atan2;
        using std::floor;
        using std::ceil;
        using std::fmod;
        using std::exp;
        using std::log;
        using std::log10;

        using std::min;
        using std::max;
    } // namespace math
} // namespace vtx

#endif //VECTRIX_COMMON_H
