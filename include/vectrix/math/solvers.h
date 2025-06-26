//
// Created by Timmimin on 26.06.2025.
//

#ifndef VECTRIX_SOLVERS_H
#define VECTRIX_SOLVERS_H

#include "common.h"

namespace vtx {
    namespace solver {

        // Square equation ( Ax^2 + Bx + C = 0 ) solver
        template<typename T>
        constexpr std::initializer_list<T> Square( const T A, const T B, const T C ) noexcept
        {
            if (A == 0)
            {
                if (B == 0)
                    return {};
                return {-C / B};
            }

            const double D = B * B - A * C * 4;
            if (D > 0)
            {
                const double SqrtD = sqrt(D);
                return {(-B + SqrtD) / (2 * A), (-B - SqrtD) / (2 * A)};
            }
            else if (D == 0)
                return {-B / (2 * A)};
            return {};
        }

        // Cubic equation ( Ax^3 + Bx^2 + Cx + D = 0 ) solver
        template<typename T>
        constexpr std::initializer_list<T> Cubic( const T A, const T B, const T C, const T D ) noexcept
        {
            constexpr double Rev2 = 1.0f / 2, Rev3 = 1.0f / 3;
            if (A == 0)
                return Square(B, C, D);

            std::initializer_list<T> ans;
            const double
                p = (3 * A * C - B * B) / (3 * A * A),
                q = (2 * B * B * B - 9 * A * B * C + 27 * A * A * D) / (27 * A * A * A),
                DNew = (p * Rev3) * (p * Rev3) * (p * Rev3) + (q * Rev2) * (q * Rev2);

            if (DNew > 0)
            {
                const double
                    gamma = sqrt(DNew),
                    alpha = cbrt(-q * Rev2 + gamma),
                    beta = cbrt(-q * Rev2 - gamma);
                ans = (alpha + beta) - (B / (3 * A));
            }
            else if (DNew == 0)
            {
                const double alpha = cbrt(-q * Rev2);
                ans = {2 * alpha - (B / (3 * A)), (-alpha) - (B / (3 * A))};
            }
            else if (DNew < 0)
            {
                const double
                    r = sqrt(-(p * p * p) / 27),
                    phi = acos(-q / (2 * r));

                ans = {
                        2 * sqrt(-p * Rev3) * cos(phi * Rev3) - (B / (3 * A)),
                        2 * sqrt(-p * Rev3) * cos((phi + 2 * vtx::math::PI) * Rev3) - (B / (3 * A)),
                        2 * sqrt(-p * Rev3) * cos((phi + 4 * vtx::math::PI) * Rev3) - (B / (3 * A))
                };
            }

            return ans;
        }

    } // namespace solvers
} // namespace vtx

#endif //VECTRIX_SOLVERS_H
