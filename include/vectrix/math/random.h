//
// Created by Timmimin on 14.06.2025.
//

#ifndef VECTRIX_RANDOM_H
#define VECTRIX_RANDOM_H

#include "vectrix/core/base_vector.h"

namespace vtx {
    namespace random {

        // Set universal-limited random vector
        template<typename T, size_t N>
        vtx::vector<T, N> vector( T min, T max ) {
            static thread_local std::mt19937 gen(std::random_device{}());

            vtx::vector<T, N> result;

            if constexpr (std::is_floating_point_v<T>) {
                std::uniform_real_distribution<T> dist(min, max);
                for (size_t i = 0; i < N; ++i)
                    result[i] = dist(gen);
            } else if constexpr (std::is_integral_v<T>) {
                std::uniform_int_distribution<T> dist(min, max);
                for (size_t i = 0; i < N; ++i)
                    result[i] = dist(gen);
            } else {
                static_assert(std::is_arithmetic_v<T>, "T must be arithmetic for random_vector!");
            }

            return result;
        }

    } // namespace random
} // namespace vtx

#endif //VECTRIX_RANDOM_H
