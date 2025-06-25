//
// Created by Timmimin on 12.06.2025.
//

#include "../tests_common.h"

#include "vectrix/core/base_vector.h"

TEST_CASE("Initializer list constructor", "[vector]") {
    vtx::vector<int, 5> a({1, 2, 3});
    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 2);
    REQUIRE(a[2] == 3);
    REQUIRE(a[3] == 0);
    REQUIRE(a[4] == 0);
}

TEST_CASE("One parameter constructor", "[vector]") {
    vtx::vector<int, 5> a(1);
    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 1);
    REQUIRE(a[2] == 1);
    REQUIRE(a[3] == 1);
    REQUIRE(a[4] == 1);
}

TEST_CASE("Variadic constructor", "[vector]") {
    vtx::vector<int, 4> a(1, 2);
    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 2);
    REQUIRE(a[2] == 0);
    REQUIRE(a[3] == 0);
}

TEST_CASE("Equality operator", "[vector]") {
    vtx::vector<int, 5> a({1, 2, 3});
    vtx::vector<int, 5> b({1, 2, 3});
    REQUIRE(a == b);
}

TEST_CASE("Inequality operator", "[vector]") {
    vtx::vector<int, 5> a({1, 2, 3});
    vtx::vector<int, 5> b({4, 3, 4});
    REQUIRE(a != b);
}

TEST_CASE("Data pointer getter", "[vector]") {
    vtx::vector<float, 5> a({1, 2, 3});
    auto *ptr = a.data();
    REQUIRE(ptr[0] == 1.0f);
    REQUIRE(ptr[1] == 2.0f);
}

TEST_CASE("Range-for check", "[vector]") {
    vtx::vector<float, 5> a({1, 2, 3});
    float b = 0;

    for (auto i : a)
        if (i == 3.0f)
            b = i;

    REQUIRE(b == 3.0f);
}

TEST_CASE("Negation", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -2.0f, 0.0f);
    vtx::vector<float, 3> c = -a;
    REQUIRE(c[0] == -1.0f);
    REQUIRE(c[1] == 2.0f);
    REQUIRE(c[2] == 0.0f);
}

TEST_CASE("Addition", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(1.0f);
    auto c = a + b;
    REQUIRE(c[0] == 2.0f);
    REQUIRE(c[1] == 3.0f);
    REQUIRE(c[2] == 4.0f);
}

TEST_CASE("Addition-Eq", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(1.0f);
    b += a;

    REQUIRE(b[0] == 2.0f);
    REQUIRE(b[1] == 3.0f);
    REQUIRE(b[2] == 4.0f);
}

TEST_CASE("Subtraction", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(2.0f);
    auto c = a - b;

    REQUIRE(c[0] == -1.0f);
    REQUIRE(c[1] == 0.0f);
    REQUIRE(c[2] == 1.0f);
}

TEST_CASE("Subtraction-Eq", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(2.0f);
    b -= a;

    REQUIRE(b[0] == 1.0f);
    REQUIRE(b[1] == 0.0f);
    REQUIRE(b[2] == -1.0f);
}

TEST_CASE("Multiplication", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -2.0f, 0.0f);
    vtx::vector<float, 3> b(2.0f);
    auto c = b * a;

    REQUIRE(c[0] == 2.0f);
    REQUIRE(c[1] == -4.0f);
    REQUIRE(c[2] == 0.0f);
}

TEST_CASE("Multiplication-Eq", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -2.0f, 0.0f);
    vtx::vector<float, 3> b(2.0f);
    b *= a;

    REQUIRE(b[0] == 2.0f);
    REQUIRE(b[1] == -4.0f);
    REQUIRE(b[2] == 0.0f);
}

TEST_CASE("Scalar multiplication", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -2.0f, 3.0f);
    auto b = a * 2.0f;
    REQUIRE(b[0] == 2.0f);
    REQUIRE(b[1] == -4.0f);
    REQUIRE(b[2] == 6.0f);
}

TEST_CASE("Scalar multiplication-Eq", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -2.0f, 3.0f);
    a *= 2.0f;
    REQUIRE(a[0] == 2.0f);
    REQUIRE(a[1] == -4.0f);
    REQUIRE(a[2] == 6.0f);
}

TEST_CASE("Division", "[vector]") {
    vtx::vector<float, 3> a(4.0f, -6.0f, 2.0f);
    vtx::vector<float, 3> b(2.0f, 3.0f, 4.0f);
    auto c = a / b;
    REQUIRE(c[0] == 2.0f);
    REQUIRE(c[1] == -2.0f);
    REQUIRE(c[2] == 0.5f);
}

TEST_CASE("Division-Eq", "[vector]") {
    vtx::vector<float, 3> a(4.0f, -6.0f, 2.0f);
    vtx::vector<float, 3> b(2.0f, 3.0f, 4.0f);
    a /= b;
    REQUIRE(a[0] == 2.0f);
    REQUIRE(a[1] == -2.0f);
    REQUIRE(a[2] == 0.5f);
}

TEST_CASE("Scalar division", "[vector]") {
    vtx::vector<float, 3> a(4.0f, -6.0f, 2.0f);
    auto b = a / 2.0f;
    REQUIRE(b[0] == 2.0f);
    REQUIRE(b[1] == -3.0f);
    REQUIRE(b[2] == 1.0f);
}

TEST_CASE("Scalar division-Eq", "[vector]") {
    vtx::vector<float, 3> a(4.0f, -6.0f, 2.0f);
    a /= 2.0f;
    REQUIRE(a[0] == 2.0f);
    REQUIRE(a[1] == -3.0f);
    REQUIRE(a[2] == 1.0f);
}

TEST_CASE("Dot product", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    vtx::vector<float, 3> b(4.0f, 5.0f, 6.0f);
    REQUIRE(a.dot(b) == 32.0f);
    REQUIRE((a & b) == 32.0f);
}

TEST_CASE("Squared length", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    REQUIRE(a.squaredLength() == 14.0f);
}

TEST_CASE("Length", "[vector]") {
    vtx::vector<float, 2> a(3.0f, 4.0f);
    REQUIRE(a.length() == 5.0f);
}

TEST_CASE("Normalized vector", "[vector]") {
    vtx::vector<float, 2> a(3.0f, 4.0f);
    auto b = a.normalized();
    REQUIRE(b.length() == Catch::Approx(1.0f));
    REQUIRE(b[0] == Catch::Approx(0.6f));
    REQUIRE(b[1] == Catch::Approx(0.8f));
}

TEST_CASE("Normalize", "[vector]") {
    vtx::vector<float, 2> a(3.0f, 4.0f);
    a.normalize();
    REQUIRE(a.length() == Catch::Approx(1.0f));
    REQUIRE(a[0] == Catch::Approx(0.6f));
    REQUIRE(a[1] == Catch::Approx(0.8f));
}

TEST_CASE("Max component", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -5.0f, 3.0f);
    REQUIRE(a.maxC() == 3.0f);
}

TEST_CASE("Min component", "[vector]") {
    vtx::vector<float, 3> a(1.0f, -5.0f, 3.0f);
    REQUIRE(a.minC() == -5.0f);
}

TEST_CASE("Lerp", "[vector]") {
    vtx::vector<float, 2> a(1.0f, 2.0f);
    vtx::vector<float, 2> b(3.0f, 6.0f);
    auto c = a.lerp(b, 0.5f);
    REQUIRE(c[0] == 2.0f);
    REQUIRE(c[1] == 4.0f);
}

TEST_CASE("Max vector", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 5.0f, 3.0f);
    vtx::vector<float, 3> b(2.0f, 3.0f, 4.0f);
    auto c = a.maxV(b);
    REQUIRE(c[0] == 2.0f);
    REQUIRE(c[1] == 5.0f);
    REQUIRE(c[2] == 4.0f);
}

TEST_CASE("Min vector", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 5.0f, 3.0f);
    vtx::vector<float, 3> b(2.0f, 3.0f, 4.0f);
    auto c = a.minV(b);
    REQUIRE(c[0] == 1.0f);
    REQUIRE(c[1] == 3.0f);
    REQUIRE(c[2] == 3.0f);
}

TEST_CASE("Ceil", "[vector]") {
    vtx::vector<float, 3> a(1.2f, -1.7f, 3.0f);
    auto b = a.ceil();
    REQUIRE(b[0] == 2.0f);
    REQUIRE(b[1] == -1.0f);
    REQUIRE(b[2] == 3.0f);
}

TEST_CASE("Floor", "[vector]") {
    vtx::vector<float, 3> a(1.2f, -1.7f, 3.0f);
    auto b = a.floor();
    REQUIRE(b[0] == 1.0f);
    REQUIRE(b[1] == -2.0f);
    REQUIRE(b[2] == 3.0f);
}

TEST_CASE("Volume", "[vector]") {
    vtx::vector<float, 3> a(2.0f, 3.0f, 4.0f);
    REQUIRE(a.volume() == 24.0f);
}

TEST_CASE("Sum", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    REQUIRE(a.sum() == 6.0f);
}

TEST_CASE("Average", "[vector]") {
    vtx::vector<float, 3> a(1.0f, 2.0f, 3.0f);
    REQUIRE(a.avg() == Catch::Approx(2.0f));
}
