//
// Created by Timmimin on 26.06.2025.
//

#ifndef VECTRIX_SOLVERS_H
#define VECTRIX_SOLVERS_H

#include "common.h"

namespace vtx {
    namespace solver {

        // Square equation ( Ax^2 + Bx + C = 0 ) solver
        // Value is std::pair<array of answers, number of answers>
        template<typename T>
        constexpr std::pair<std::array<T, 2>, size_t> Square( const T A, const T B, const T C ) noexcept
        {
            if (VTX_UNLIKELY(A == 0))
            {
                if (VTX_UNLIKELY(B == 0))
                    return {{}, 0};
                return {{-C / B}, 1};
            }

            const T
                D = B * B - A * C * 4,
                inv2A = 1 / (2 * A);

            if (VTX_LIKELY(D > 0))
            {
                const T SqrtD = vtx::math::sqrt(D);
                return {{(-B + SqrtD) * inv2A, (-B - SqrtD) * inv2A}, 2};
            }
            else if (VTX_UNLIKELY(D == 0))
                return {{-B * inv2A}, 1};
            return {{}, 0};
        }

        // Cubic equation ( Ax^3 + Bx^2 + Cx + D = 0 ) solver
        template<typename T>
        constexpr std::pair<std::array<T, 3>, size_t> Cubic( const T A, const T B, const T C, const T D ) noexcept
        {
            constexpr T Rev2 = T(0.5), Rev3 = T(1.0 / 3);
            if (VTX_UNLIKELY(A == 0))
                return Square(B, C, D);

            std::pair<std::array<T, 3>, size_t> ans;
            const T
                p = (3 * A * C - B * B) / (3 * A * A),
                q = (2 * B * B * B - 9 * A * B * C + 27 * A * A * D) / (27 * A * A * A),
                DNew = (p * Rev3) * (p * Rev3) * (p * Rev3) + (q * Rev2) * (q * Rev2);

            const T B3A = B / (3 * A);
            if (DNew > 0)
            {
                const T
                    gamma = vtx::math::sqrt(DNew),
                    alpha = vtx::math::cbrt(-q * Rev2 + gamma),
                    beta = vtx::math::cbrt(-q * Rev2 - gamma);
                ans = {{(alpha + beta) - B3A}, 1};
            }
            else if (DNew == 0)
            {
                const T alpha = vtx::math::cbrt(-q * Rev2);
                ans = {{2 * alpha - B3A, (-alpha) - B3A}, 2};
            }
            else if (DNew < 0)
            {
                const T
                    r = vtx::math::sqrt(-(p * p * p) / 27),
                    phi = vtx::math::acos(-q / (2 * r)),
                    sqrt2p3 = 2 * vtx::math::sqrt(-p * Rev3);

                ans = {{
                    sqrt2p3 * vtx::math::cos(phi * Rev3) - B3A,
                    sqrt2p3 * vtx::math::cos((phi + 2 * vtx::math::PI) * Rev3) - B3A,
                    sqrt2p3 * vtx::math::cos((phi + 4 * vtx::math::PI) * Rev3) - B3A
                }, 3};
            }

            return ans;
        }

    } // namespace solvers
} // namespace vtx

#endif //VECTRIX_SOLVERS_H
