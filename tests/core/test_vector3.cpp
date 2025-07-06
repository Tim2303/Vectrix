//
// Created by Timmimin on 06.07.2025.
//

#include "../tests_common.h"
#include "vectrix/core/vector3.h"

TEST_CASE("Vector3 constructors and accessors", "[vector3]") {
    SECTION("Default constructor") {
        vtx::vec3<float> v{};
        REQUIRE(v.X == 0.0f);
        REQUIRE(v.Y == 0.0f);
        REQUIRE(v.Z == 0.0f);
    }

    SECTION("Single value constructor") {
        vtx::vec3<int> v(5);
        REQUIRE(v.X == 5);
        REQUIRE(v.Y == 5);
        REQUIRE(v.Z == 5);
    }

    SECTION("Three value constructor") {
        vtx::vec3<float> v(1.5f, 2.5f, 3.5f);
        REQUIRE(v.X == 1.5f);
        REQUIRE(v.Y == 2.5f);
        REQUIRE(v.Z == 3.5f);
    }

    SECTION("Initializer list constructor") {
        vtx::vec3<int> v = {1, 2, 3};
        REQUIRE(v.X == 1);
        REQUIRE(v.Y == 2);
        REQUIRE(v.Z == 3);
    }
}

TEST_CASE("Vector3 arithmetic operations", "[vector3]") {
    vtx::vec3<float> a(1.0f, 2.0f, 3.0f);
    vtx::vec3<float> b(4.0f, 5.0f, 6.0f);

    SECTION("Addition") {
        auto c = a + b;
        REQUIRE(c == vtx::vec3<float>(5.0f, 7.0f, 9.0f));

        a += b;
        REQUIRE(a == vtx::vec3<float>(5.0f, 7.0f, 9.0f));
    }

    SECTION("Subtraction") {
        auto c = b - a;
        REQUIRE(c == vtx::vec3<float>(3.0f, 3.0f, 3.0f));

        b -= a;
        REQUIRE(b == vtx::vec3<float>(3.0f, 3.0f, 3.0f));
    }

    SECTION("Multiplication") {
        auto c = a * b;
        REQUIRE(c == vtx::vec3<float>(4.0f, 10.0f, 18.0f));

        a *= b;
        REQUIRE(a == vtx::vec3<float>(4.0f, 10.0f, 18.0f));
    }

    SECTION("Scalar multiplication") {
        auto c = a * 2.0f;
        REQUIRE(c == vtx::vec3<float>(2.0f, 4.0f, 6.0f));

        a *= 2.0f;
        REQUIRE(a == vtx::vec3<float>(2.0f, 4.0f, 6.0f));
    }

    SECTION("Division") {
        vtx::vec3<float> c(8.0f, 10.0f, 12.0f);
        auto d = c / b;
        REQUIRE(d == vtx::vec3<float>(2.0f, 2.0f, 2.0f));

        c /= b;
        REQUIRE(c == vtx::vec3<float>(2.0f, 2.0f, 2.0f));
    }

    SECTION("Scalar division") {
        vtx::vec3<float> c(2.0f, 4.0f, 6.0f);
        auto d = c / 2.0f;
        REQUIRE(d == vtx::vec3<float>(1.0f, 2.0f, 3.0f));

        c /= 2.0f;
        REQUIRE(c == vtx::vec3<float>(1.0f, 2.0f, 3.0f));
    }

    SECTION("Negation") {
        auto c = -a;
        REQUIRE(c == vtx::vec3<float>(-1.0f, -2.0f, -3.0f));
    }
}

TEST_CASE("Vector3 vector operations", "[vector3]") {
    vtx::vec3<float> a(1.0f, 0.0f, 0.0f);
    vtx::vec3<float> b(0.0f, 1.0f, 0.0f);

    SECTION("Cross product") {
        auto c = a.cross(b);
        REQUIRE(c == vtx::vec3<float>(0.0f, 0.0f, 1.0f));

        a %= b;
        REQUIRE(a == vtx::vec3<float>(0.0f, 0.0f, 1.0f));
    }

    SECTION("Angle calculation") {
        REQUIRE(a.Angle(b) == Catch::Approx(90.0f));
        REQUIRE(a.Angle(a) == Catch::Approx(0.0f));
    }
}

TEST_CASE("Vector3 mathematical operations", "[vector3]") {
    vtx::vec3<float> a(1.0f, 2.0f, 3.0f);
    vtx::vec3<float> b(-1.0f, 2.0f, 0.5f);

    SECTION("Dot product") {
        REQUIRE(a.dot(b) == 4.5f);
        REQUIRE((a & b) == 4.5f);
    }

    SECTION("Length calculations") {
        REQUIRE(a.squaredLength() == 14.0f);
        REQUIRE(a.length() == Catch::Approx(3.741657f));
    }

    SECTION("Normalization") {
        auto c = a.normalized();
        REQUIRE(c.length() == Catch::Approx(1.0f));

        a.normalize();
        REQUIRE(a.length() == Catch::Approx(1.0f));
    }

    SECTION("Component operations") {
        REQUIRE(a.maxC() == 3.0f);
        REQUIRE(b.minC() == -1.0f);
        REQUIRE(a.sum() == 6.0f);
        REQUIRE(a.avg() == 2.0f);
        REQUIRE(a.volume() == 6.0f);
    }

    SECTION("Lerp") {
        auto c = a.lerp(b, 0.5f);
        REQUIRE(c == vtx::vec3<float>(0.0f, 2.0f, 1.75f));
    }

    SECTION("Component-wise min/max") {
        auto c = a.maxV(b);
        REQUIRE(c == vtx::vec3<float>(1.0f, 2.0f, 3.0f));

        auto d = a.minV(b);
        REQUIRE(d == vtx::vec3<float>(-1.0f, 2.0f, 0.5f));
    }

    SECTION("Rounding operations") {
        vtx::vec3<float> c(1.2f, -1.7f, 3.0f);
        auto ceil = c.ceil();
        REQUIRE(ceil == vtx::vec3<float>(2.0f, -1.0f, 3.0f));

        auto floor = c.floor();
        REQUIRE(floor == vtx::vec3<float>(1.0f, -2.0f, 3.0f));
    }

    SECTION("Special cases") {
        vtx::vec3<float> zero(0.0f, 0.0f, 0.0f);
        REQUIRE(zero.length() == 0.0f);
        REQUIRE(zero.cross(a) == vtx::vec3<float>(0.0f, 0.0f, 0.0f));
    }
}
