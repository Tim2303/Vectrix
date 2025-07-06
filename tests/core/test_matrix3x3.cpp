//
// Created by Timmimin on 06.07.2025.
//

#include "../tests_common.h"
#include "vectrix/core/matrix3x3.h"
#include "vectrix/core/vector3.h"

TEST_CASE("Matrix3x3 constructors and accessors", "[matrix3x3]") {
    SECTION("Single value constructor") {
        vtx::mat3x3<int> m(5);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                REQUIRE(m[i][j] == 5);
    }

    SECTION("Initializer list constructor") {
        vtx::mat3x3<int> m = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[1][1] == 5);
        REQUIRE(m[2][2] == 9);
    }

    SECTION("Element access") {
        vtx::mat3x3<float> m;
        m(0, 0) = 1.5f;
        m(1, 1) = 2.5f;
        m(2, 2) = 3.5f;
        REQUIRE(m[0][0] == 1.5f);
        REQUIRE(m[1][1] == 2.5f);
        REQUIRE(m[2][2] == 3.5f);
    }
}

TEST_CASE("Matrix3x3 arithmetic operations", "[matrix3x3]") {
    vtx::mat3x3<float> a = {
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f},
            {7.0f, 8.0f, 9.0f}
    };
    vtx::mat3x3<float> b = {
            {9.0f, 8.0f, 7.0f},
            {6.0f, 5.0f, 4.0f},
            {3.0f, 2.0f, 1.0f}
    };

    SECTION("Addition") {
        auto c = a + b;
        REQUIRE(c[0][0] == 10.0f);
        REQUIRE(c[1][1] == 10.0f);
        REQUIRE(c[2][2] == 10.0f);

        a += b;
        REQUIRE(a[0][0] == 10.0f);
    }

    SECTION("Subtraction") {
        auto c = b - a;
        REQUIRE(c[0][0] == 8.0f);
        REQUIRE(c[1][1] == 0.0f);
        REQUIRE(c[2][2] == -8.0f);

        b -= a;
        REQUIRE(b[0][0] == 8.0f);
    }

    SECTION("Scalar multiplication") {
        auto c = a * 2.0f;
        REQUIRE(c[0][0] == 2.0f);
        REQUIRE(c[1][1] == 10.0f);

        a *= 2.0f;
        REQUIRE(a[0][0] == 2.0f);
    }

    SECTION("Scalar division") {
        vtx::mat3x3<float> c = {
                {2.0f, 4.0f, 6.0f},
                {8.0f, 10.0f, 12.0f},
                {14.0f, 16.0f, 18.0f}
        };
        auto d = c / 2.0f;
        REQUIRE(d[0][0] == 1.0f);
        REQUIRE(d[1][1] == 5.0f);

        c /= 2.0f;
        REQUIRE(c[0][0] == 1.0f);
    }

    SECTION("Negation") {
        auto c = -a;
        REQUIRE(c[0][0] == -1.0f);
        REQUIRE(c[1][1] == -5.0f);
    }
}

TEST_CASE("Matrix3x3 matrix operations", "[matrix3x3]") {
    vtx::mat3x3<float> a = {
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f},
            {7.0f, 8.0f, 9.0f}
    };
    vtx::mat3x3<float> b = {
            {9.0f, 8.0f, 7.0f},
            {6.0f, 5.0f, 4.0f},
            {3.0f, 2.0f, 1.0f}
    };

    SECTION("Matrix multiplication") {
        auto c = a * b;
        REQUIRE(c[0][0] == 30.0f);
        REQUIRE(c[1][1] == 69.0f);
        REQUIRE(c[2][2] == 90.0f);

        a *= b;
        REQUIRE(a[0][0] == 30.0f);
    }

    SECTION("Transpose") {
        auto c = a.transpose();
        REQUIRE(c[0][0] == 1.0f);
        REQUIRE(c[0][1] == 4.0f);
        REQUIRE(c[1][0] == 2.0f);
    }

    SECTION("Determinant") {
        REQUIRE(a.determinant() == 0.0f);

        vtx::mat3x3<float> d = {
                {4.0f, 3.0f, 2.0f},
                {2.0f, 1.0f, 3.0f},
                {1.0f, 2.0f, 4.0f}
        };
        REQUIRE(d.determinant() == -17.0f);
    }

    SECTION("Inverse") {
        vtx::mat3x3<float> c = {
                {4.0f, 3.0f, 2.0f},
                {2.0f, 1.0f, 3.0f},
                {1.0f, 2.0f, 4.0f}
        };
        auto inv = c.inverse();
        auto identity = c * inv;
        REQUIRE(identity[0][0] == Catch::Approx(1.0f));
        REQUIRE(identity[1][1] == Catch::Approx(1.0f));
    }

    SECTION("Trace") {
        REQUIRE(a.trace() == 15.0f);
    }

    SECTION("Frobenius norm") {
        REQUIRE(a.frobeniusNorm() == Catch::Approx(16.881943f));
    }
}

TEST_CASE("Matrix3x3 vector operations", "[matrix3x3]") {
    vtx::mat3x3<float> m = {
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f},
            {7.0f, 8.0f, 9.0f}
    };
    vtx::vec3<float> v(1.0f, 2.0f, 3.0f);

    SECTION("Matrix-vector multiplication") {
        auto res = m * v;
        REQUIRE(res == vtx::vec3<float>(14.0f, 32.0f, 50.0f));
    }
}

TEST_CASE("Matrix3x3 special functions", "[matrix3x3]") {
    SECTION("Star tensor") {
        vtx::vec3<float> v(1.0f, 2.0f, 3.0f);
        auto m = vtx::tensor<float>::star(v);
        REQUIRE(m[0][0] == 0.0f);
        REQUIRE(m[0][1] == 3.0f);
        REQUIRE(m[0][2] == 2.0f);
        REQUIRE(m[1][0] == 3.0f);
        REQUIRE(m[1][1] == 0.0f);
        REQUIRE(m[1][2] == -1.0f);
    }

    SECTION("Identity matrix") {
        auto m = vtx::mat3x3<float>::identity();
        REQUIRE(m[0][0] == 1.0f);
        REQUIRE(m[1][1] == 1.0f);
        REQUIRE(m[2][2] == 1.0f);
        REQUIRE(m[0][1] == 0.0f);
    }
}
