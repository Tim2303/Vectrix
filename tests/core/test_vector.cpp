//
// Created by Timmimin on 12.06.2025.
//

#include "vectrix/core/base_vector.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector addition", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(1.0f);
    auto c = a + b;
    REQUIRE(c[0] == 2.0f);
}
