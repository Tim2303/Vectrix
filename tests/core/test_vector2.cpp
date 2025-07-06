//
// Created by Timmimin on 06.07.2025.
//

#include "../tests_common.h"
#include "vectrix/core/vector2.h"

TEST_CASE("Vector2 constructors and accessors", "[vector2]") {
    SECTION("Default constructor") {
        vtx::vec2<float> v{};
        REQUIRE(v.X == 0.0f);
        REQUIRE(v.Y == 0.0f);
        REQUIRE(v[0] == 0.0f);
        REQUIRE(v[1] == 0.0f);
    }

    SECTION("Single value constructor") {
        vtx::vec2<int> v(5);
        REQUIRE(v.X == 5);
        REQUIRE(v.Y == 5);
    }

    SECTION("Two value constructor") {
        vtx::vec2<float> v(1.5f, 2.5f);
        REQUIRE(v.X == 1.5f);
        REQUIRE(v.Y == 2.5f);
    }

    SECTION("Initializer list constructor") {
        vtx::vec2<int> v = {1, 2};
        REQUIRE(v.X == 1);
        REQUIRE(v.Y == 2);
    }

    SECTION("Element access") {
        vtx::vec2<float> v;
        v[0] = 1.5f;
        v[1] = 2.5f;
        REQUIRE(v.X == 1.5f);
        REQUIRE(v.Y == 2.5f);
    }
}

TEST_CASE("Vector2 arithmetic operations", "[vector2]") {
    vtx::vec2<float> a(1.0f, 2.0f);
    vtx::vec2<float> b(3.0f, 4.0f);

    SECTION("Addition") {
        auto c = a + b;
        REQUIRE(c == vtx::vec2<float>(4.0f, 6.0f));

        a += b;
        REQUIRE(a == vtx::vec2<float>(4.0f, 6.0f));
    }

    SECTION("Subtraction") {
        auto c = b - a;
        REQUIRE(c == vtx::vec2<float>(2.0f, 2.0f));

        b -= a;
        REQUIRE(b == vtx::vec2<float>(2.0f, 2.0f));
    }

    SECTION("Multiplication") {
        auto c = a * b;
        REQUIRE(c == vtx::vec2<float>(3.0f, 8.0f));

        a *= b;
        REQUIRE(a == vtx::vec2<float>(3.0f, 8.0f));
    }

    SECTION("Scalar multiplication") {
        auto c = a * 2.0f;
        REQUIRE(c == vtx::vec2<float>(2.0f, 4.0f));

        a *= 2.0f;
        REQUIRE(a == vtx::vec2<float>(2.0f, 4.0f));
    }

    SECTION("Division") {
        vtx::vec2<float> c(6.0f, 8.0f);
        auto d = c / b;
        REQUIRE(d == vtx::vec2<float>(2.0f, 2.0f));

        c /= b;
        REQUIRE(c == vtx::vec2<float>(2.0f, 2.0f));
    }

    SECTION("Scalar division") {
        vtx::vec2<float> c(6.0f, 8.0f);
        auto d = c / 2.0f;
        REQUIRE(d == vtx::vec2<float>(3.0f, 4.0f));

        c /= 2.0f;
        REQUIRE(c == vtx::vec2<float>(3.0f, 4.0f));
    }

    SECTION("Negation") {
        auto c = -a;
        REQUIRE(c == vtx::vec2<float>(-1.0f, -2.0f));
    }
}

TEST_CASE("Vector2 mathematical operations", "[vector2]") {
    vtx::vec2<float> a(3.0f, 4.0f);
    vtx::vec2<float> b(-1.0f, 2.0f);

    SECTION("Dot product") {
        REQUIRE(a.dot(b) == 5.0f);
        REQUIRE((a & b) == 5.0f);
    }

    SECTION("Length calculations") {
        REQUIRE(a.squaredLength() == 25.0f);
        REQUIRE(a.length() == 5.0f);
    }

    SECTION("Normalization") {
        auto c = a.normalized();
        REQUIRE(c.length() == Catch::Approx(1.0f));
        REQUIRE(c.X == Catch::Approx(0.6f));
        REQUIRE(c.Y == Catch::Approx(0.8f));

        a.normalize();
        REQUIRE(a.length() == Catch::Approx(1.0f));
    }

    SECTION("Component operations") {
        REQUIRE(a.maxC() == 4.0f);
        REQUIRE(b.minC() == -1.0f);
        REQUIRE(a.sum() == 7.0f);
        REQUIRE(a.avg() == 3.5f);
        REQUIRE(a.volume() == 12.0f);
    }

    SECTION("Lerp") {
        auto c = a.lerp(b, 0.5f);
        REQUIRE(c.X == 1.0f);
        REQUIRE(c.Y == 3.0f);
    }

    SECTION("Component-wise min/max") {
        auto c = a.maxV(b);
        REQUIRE(c == vtx::vec2<float>(3.0f, 4.0f));

        auto d = a.minV(b);
        REQUIRE(d == vtx::vec2<float>(-1.0f, 2.0f));
    }

    SECTION("Rounding operations") {
        vtx::vec2<float> c(1.2f, -1.7f);
        auto ceil = c.ceil();
        REQUIRE(ceil == vtx::vec2<float>(2.0f, -1.0f));

        auto floor = c.floor();
        REQUIRE(floor == vtx::vec2<float>(1.0f, -2.0f));
    }

    SECTION("Special cases") {
        vtx::vec2<float> zero(0.0f, 0.0f);
        REQUIRE(zero.length() == 0.0f);
    }
}
