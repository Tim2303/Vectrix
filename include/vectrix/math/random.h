//
// Created by Timmimin on 14.06.2025.
//

#ifndef VECTRIX_RANDOM_H
#define VECTRIX_RANDOM_H

#include "vectrix/core/base_vector.h"
#include "vectrix/core/base_matrix.h"

namespace vtx {
    namespace random {

        // Set universal-limited random float-point vector
        template<typename T, size_t N>
        typename std::enable_if<std::is_floating_point<T>::value, vtx::vector<T, N>>::type
        vector( T min, T max ) {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic for random_vector!");
            static thread_local std::mt19937 gen(std::random_device{}());

            vtx::vector<T, N> result;
            std::uniform_real_distribution<T> dist(min, max);
            for (size_t i = 0; i < N; ++i)
                result[i] = dist(gen);

            return result;
        }

        // Set universal-limited random integer vector
        template<typename T, size_t N>
        typename std::enable_if<std::is_integral<T>::value, vtx::vector<T, N>>::type
        vector( T min, T max ) {
            static_assert(std::is_arithmetic_v<T>, "T must be arithmetic for random_vector!");
            static thread_local std::mt19937 gen(std::random_device{}());

            vtx::vector<T, N> result;
            std::uniform_int_distribution<T> dist(min, max);
            for (size_t i = 0; i < N; ++i)
                result[i] = dist(gen);

            return result;
        }

    } // namespace random
} // namespace vtx

#endif //VECTRIX_RANDOM_H
