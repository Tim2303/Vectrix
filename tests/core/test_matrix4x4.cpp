//
// Created by Timmimin on 07.07.2025.
//

//
// Created based on vector tests
//

#include "../tests_common.h"

#include "vectrix/core/base_matrix.h"
#include "vectrix/core/matrix4x4.h"

TEST_CASE("Initializer list constructor", "[matrix3x3]") {
    vtx::mat4x4<int> a({1, 2, 3, 4, 5, 6});
    REQUIRE(a[0][0] == 1);
    REQUIRE(a[0][1] == 2);
    REQUIRE(a[0][2] == 3);
    REQUIRE(a[0][3] == 4);
    REQUIRE(a[1][0] == 5);
    REQUIRE(a[1][1] == 6);
    REQUIRE(a[1][2] == 0);
    REQUIRE(a[1][3] == 0);
    REQUIRE(a[2][0] == 0);
    REQUIRE(a[2][1] == 0);
    REQUIRE(a[2][2] == 0);
    REQUIRE(a[2][3] == 0);
    REQUIRE(a[3][0] == 0);
    REQUIRE(a[3][1] == 0);
    REQUIRE(a[3][2] == 0);
    REQUIRE(a[3][3] == 0);
}

TEST_CASE("Row initializer list constructor", "[matrix3x3]") {
    vtx::mat4x4<int> a({{1, 2}, {3, 4, 5}, {6}, {7, 8, 9, 10}});
    REQUIRE(a[0][0] == 1);
    REQUIRE(a[0][1] == 2);
    REQUIRE(a[0][2] == 0);
    REQUIRE(a[0][3] == 0);
    REQUIRE(a[1][0] == 3);
    REQUIRE(a[1][1] == 4);
    REQUIRE(a[1][2] == 5);
    REQUIRE(a[1][3] == 0);
    REQUIRE(a[2][0] == 6);
    REQUIRE(a[2][1] == 0);
    REQUIRE(a[2][2] == 0);
    REQUIRE(a[2][3] == 0);
    REQUIRE(a[3][0] == 7);
    REQUIRE(a[3][1] == 8);
    REQUIRE(a[3][2] == 9);
    REQUIRE(a[3][3] == 10);
}

TEST_CASE("One parameter constructor", "[matrix3x3]") {
    vtx::mat4x4<int> a(5);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            REQUIRE(a[i][j] == 5);
        }
    }
}

TEST_CASE("Variadic constructor", "[matrix3x3]") {
    vtx::mat4x4<int> a(1, 2, 3, 4, 5, 6);
    REQUIRE(a[0][0] == 1);
    REQUIRE(a[0][1] == 2);
    REQUIRE(a[0][2] == 3);
    REQUIRE(a[0][3] == 4);
    REQUIRE(a[1][0] == 5);
    REQUIRE(a[1][1] == 6);
    REQUIRE(a[1][2] == 0);
    REQUIRE(a[1][3] == 0);
}

TEST_CASE("Equality operator", "[matrix3x3]") {
    vtx::mat4x4<int> a({{1, 2}, {3, 4}});
    vtx::mat4x4<int> b({{1, 2}, {3, 4}});
    REQUIRE(a == b);
}

TEST_CASE("Inequality operator", "[matrix3x3]") {
    vtx::mat4x4<int> a({{1, 2}, {3, 4}});
    vtx::mat4x4<int> b({{5, 6}, {7, 8}});
    REQUIRE(a != b);
}

TEST_CASE("Data pointer getter", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, 2.0f}, {3.0f, 4.0f}});
    auto* ptr = a.data();
    REQUIRE(ptr[0] == 1.0f);
    REQUIRE(ptr[1] == 2.0f);
    REQUIRE(ptr[4] == 3.0f);
    REQUIRE(ptr[5] == 4.0f);
}

TEST_CASE("Element access operator", "[matrix3x3]") {
    vtx::mat4x4<float> a;
    a[1][2] = 3.5f;
    REQUIRE(a(1, 2) == 3.5f);
    a(2, 1) = 4.5f;
    REQUIRE(a[2][1] == 4.5f);
}

TEST_CASE("Negation", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, -2.0f}, {0.0f, 3.0f}});
    auto c = -a;
    REQUIRE(c[0][0] == -1.0f);
    REQUIRE(c[0][1] == 2.0f);
    REQUIRE(c[1][0] == 0.0f);
    REQUIRE(c[1][1] == -3.0f);
}

TEST_CASE("Addition", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, 2.0f}, {3.0f, 4.0f}});
    vtx::mat4x4<float> b({{1.0f, 0.0f}, {0.0f, 1.0f}});
    auto c = a + b;
    REQUIRE(c[0][0] == 2.0f);
    REQUIRE(c[0][1] == 2.0f);
    REQUIRE(c[1][0] == 3.0f);
    REQUIRE(c[1][1] == 5.0f);
}

TEST_CASE("Addition-Eq", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, 2.0f}, {3.0f, 4.0f}});
    vtx::mat4x4<float> b({{1.0f, 0.0f}, {0.0f, 1.0f}});
    a += b;
    REQUIRE(a[0][0] == 2.0f);
    REQUIRE(a[0][1] == 2.0f);
    REQUIRE(a[1][0] == 3.0f);
    REQUIRE(a[1][1] == 5.0f);
}

TEST_CASE("Subtraction", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, 2.0f}, {3.0f, 4.0f}});
    vtx::mat4x4<float> b({{1.0f, 1.0f}, {1.0f, 1.0f}});
    auto c = a - b;
    REQUIRE(c[0][0] == 0.0f);
    REQUIRE(c[0][1] == 1.0f);
    REQUIRE(c[1][0] == 2.0f);
    REQUIRE(c[1][1] == 3.0f);
}

TEST_CASE("Subtraction-Eq", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, 2.0f}, {3.0f, 4.0f}});
    vtx::mat4x4<float> b({{1.0f, 1.0f}, {1.0f, 1.0f}});
    a -= b;
    REQUIRE(a[0][0] == 0.0f);
    REQUIRE(a[0][1] == 1.0f);
    REQUIRE(a[1][0] == 2.0f);
    REQUIRE(a[1][1] == 3.0f);
}

TEST_CASE("Scalar multiplication", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, -2.0f}, {3.0f, 4.0f}});
    auto b = a * 2.0f;
    REQUIRE(b[0][0] == 2.0f);
    REQUIRE(b[0][1] == -4.0f);
    REQUIRE(b[1][0] == 6.0f);
    REQUIRE(b[1][1] == 8.0f);
}

TEST_CASE("Scalar multiplication-Eq", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1.0f, -2.0f}, {3.0f, 4.0f}});
    a *= 2.0f;
    REQUIRE(a[0][0] == 2.0f);
    REQUIRE(a[0][1] == -4.0f);
    REQUIRE(a[1][0] == 6.0f);
    REQUIRE(a[1][1] == 8.0f);
}

TEST_CASE("Scalar division", "[matrix3x3]") {
    vtx::mat4x4<float> a({{4.0f, -6.0f}, {2.0f, 8.0f}});
    auto b = a / 2.0f;
    REQUIRE(b[0][0] == 2.0f);
    REQUIRE(b[0][1] == -3.0f);
    REQUIRE(b[1][0] == 1.0f);
    REQUIRE(b[1][1] == 4.0f);
}

TEST_CASE("Scalar division-Eq", "[matrix3x3]") {
    vtx::mat4x4<float> a({{4.0f, -6.0f}, {2.0f, 8.0f}});
    a /= 2.0f;
    REQUIRE(a[0][0] == 2.0f);
    REQUIRE(a[0][1] == -3.0f);
    REQUIRE(a[1][0] == 1.0f);
    REQUIRE(a[1][1] == 4.0f);
}

TEST_CASE("Matrix multiplication", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
    vtx::mat4x4<float> b({{16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}});
    auto c = a * b;

    REQUIRE(c[0][0] == 80.0f);
    REQUIRE(c[0][1] == 70.0f);
    REQUIRE(c[0][2] == 60.0f);
    REQUIRE(c[0][3] == 50.0f);
    REQUIRE(c[1][0] == 240.0f);
    REQUIRE(c[1][1] == 214.0f);
    REQUIRE(c[1][2] == 188.0f);
    REQUIRE(c[1][3] == 162.0f);
    REQUIRE(c[2][0] == 400.0f);
    REQUIRE(c[2][1] == 358.0f);
    REQUIRE(c[2][2] == 316.0f);
    REQUIRE(c[2][3] == 274.0f);
    REQUIRE(c[3][0] == 560.0f);
    REQUIRE(c[3][1] == 502.0f);
    REQUIRE(c[3][2] == 444.0f);
    REQUIRE(c[3][3] == 386.0f);
}

TEST_CASE("Matrix multiplication-Eq", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}});
    vtx::mat4x4<float> b({{2, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 2, 0}, {0, 0, 0, 2}});
    a *= b;

    REQUIRE(a[0][0] == 2.0f);
    REQUIRE(a[0][1] == 0.0f);
    REQUIRE(a[0][2] == 0.0f);
    REQUIRE(a[0][3] == 0.0f);
    REQUIRE(a[1][0] == 0.0f);
    REQUIRE(a[1][1] == 2.0f);
    REQUIRE(a[1][2] == 0.0f);
    REQUIRE(a[1][3] == 0.0f);
    REQUIRE(a[2][0] == 0.0f);
    REQUIRE(a[2][1] == 0.0f);
    REQUIRE(a[2][2] == 2.0f);
    REQUIRE(a[2][3] == 0.0f);
    REQUIRE(a[3][0] == 2.0f);
    REQUIRE(a[3][1] == 2.0f);
    REQUIRE(a[3][2] == 2.0f);
    REQUIRE(a[3][3] == 2.0f);
}

TEST_CASE("Matrix-vector multiplication", "[matrix3x3]") {
    vtx::mat4x4<float> m({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
    vtx::vector<float, 4> v(1.0f, 2.0f, 3.0f, 4.0f);
    auto result = m * v;

    REQUIRE(result[0] == 30.0f);
    REQUIRE(result[1] == 70.0f);
    REQUIRE(result[2] == 110.0f);
    REQUIRE(result[3] == 150.0f);
}

TEST_CASE("Transpose", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
    auto b = a.transpose();

    REQUIRE(b[0][0] == 1.0f);
    REQUIRE(b[0][1] == 5.0f);
    REQUIRE(b[0][2] == 9.0f);
    REQUIRE(b[0][3] == 13.0f);
    REQUIRE(b[1][0] == 2.0f);
    REQUIRE(b[1][1] == 6.0f);
    REQUIRE(b[1][2] == 10.0f);
    REQUIRE(b[1][3] == 14.0f);
    REQUIRE(b[2][0] == 3.0f);
    REQUIRE(b[2][1] == 7.0f);
    REQUIRE(b[2][2] == 11.0f);
    REQUIRE(b[2][3] == 15.0f);
    REQUIRE(b[3][0] == 4.0f);
    REQUIRE(b[3][1] == 8.0f);
    REQUIRE(b[3][2] == 12.0f);
    REQUIRE(b[3][3] == 16.0f);
}

TEST_CASE("Identity matrix", "[matrix3x3]") {
    auto a = vtx::mat4x4<float>::identity();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                REQUIRE(a[i][j] == 1.0f);
            } else {
                REQUIRE(a[i][j] == 0.0f);
            }
        }
    }
}

TEST_CASE("Determinant", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 3, 0}, {0, 0, 0, 4}});
    REQUIRE(a.determinant() == 24.0f);

    vtx::mat4x4<float> b({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
    REQUIRE(b.determinant() == 0.0f);
}

TEST_CASE("Inverse matrix", "[matrix3x3]") {
    vtx::mat4x4<float> a({{2, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 2, 0}, {0, 0, 0, 2}});
    auto b = a.inverse();

    REQUIRE(b[0][0] == 0.5f);
    REQUIRE(b[0][1] == 0.0f);
    REQUIRE(b[0][2] == 0.0f);
    REQUIRE(b[0][3] == 0.0f);
    REQUIRE(b[1][0] == 0.0f);
    REQUIRE(b[1][1] == 0.5f);
    REQUIRE(b[1][2] == 0.0f);
    REQUIRE(b[1][3] == 0.0f);
    REQUIRE(b[2][0] == 0.0f);
    REQUIRE(b[2][1] == 0.0f);
    REQUIRE(b[2][2] == 0.5f);
    REQUIRE(b[2][3] == 0.0f);
    REQUIRE(b[3][0] == 0.0f);
    REQUIRE(b[3][1] == 0.0f);
    REQUIRE(b[3][2] == 0.0f);
    REQUIRE(b[3][3] == 0.5f);
}

TEST_CASE("Trace", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
    REQUIRE(a.trace() == 34.0f);
}

TEST_CASE("Frobenius norm", "[matrix3x3]") {
    vtx::mat4x4<float> a({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
    REQUIRE(a.frobeniusNorm() == Catch::Approx(2.0f));
}

TEST_CASE("Rotation matrices", "[matrix3x3]") {
    SECTION("X-axis rotation") {
        auto rot = vtx::mat4x4<float>::rotateX(90.0f);
        vtx::vector<float, 3> v(0.0f, 1.0f, 0.0f);
        auto rotated = rot.transformVector(v);

        REQUIRE(rotated[0] == Catch::Approx(0.0f));
        REQUIRE(rotated[1] == Catch::Approx(0.0f).margin(0.0001f));
        REQUIRE(rotated[2] == Catch::Approx(1.0f));
    }

    SECTION("Y-axis rotation") {
        auto rot = vtx::mat4x4<float>::rotateY(90.0f);
        vtx::vector<float, 3> v(0.0f, 0.0f, 1.0f);
        auto rotated = rot.transformVector(v);

        REQUIRE(rotated[0] == Catch::Approx(1.0f));
        REQUIRE(rotated[1] == Catch::Approx(0.0f));
        REQUIRE(rotated[2] == Catch::Approx(0.0f).margin(0.0001f));
    }

    SECTION("Z-axis rotation") {
        auto rot = vtx::mat4x4<float>::rotateZ(90.0f);
        vtx::vector<float, 3> v(1.0f, 0.0f, 0.0f);
        auto rotated = rot.transformVector(v);

        REQUIRE(rotated[0] == Catch::Approx(0.0f).margin(0.0001f));
        REQUIRE(rotated[1] == Catch::Approx(1.0f));
        REQUIRE(rotated[2] == Catch::Approx(0.0f));
    }

    SECTION("Arbitrary axis rotation") {
        vtx::vector<float, 3> axis(1.0f, 1.0f, 1.0f);
        auto rot = vtx::mat4x4<float>::rotate(axis.normalized(), 120.0f);
        vtx::vector<float, 3> v(1.0f, 0.0f, 0.0f);
        auto rotated = rot.transformVector(v);

        REQUIRE(rotated[0] == Catch::Approx(0.0f).margin(0.0001f));
        REQUIRE(rotated[1] == Catch::Approx(1.0f));
        REQUIRE(rotated[2] == Catch::Approx(0.0f));
    }
}

TEST_CASE("Translation matrix", "[matrix3x3]") {
    auto trans = vtx::mat4x4<float>::translate(vtx::vector<float, 3>(1.0f, 2.0f, 3.0f));
    vtx::vector<float, 3> point(0.0f, 0.0f, 0.0f);
    auto transformed = trans.transformPoint(point);

    REQUIRE(transformed[0] == 1.0f);
    REQUIRE(transformed[1] == 2.0f);
    REQUIRE(transformed[2] == 3.0f);
}

TEST_CASE("Scaling matrices", "[matrix3x3]") {
    SECTION("Uniform scaling") {
        auto scale = vtx::mat4x4<float>::scale(2.0f);
        vtx::vector<float, 3> v(1.0f, 2.0f, 3.0f);
        auto scaled = scale.transformVector(v);

        REQUIRE(scaled[0] == 2.0f);
        REQUIRE(scaled[1] == 4.0f);
        REQUIRE(scaled[2] == 6.0f);
    }

    SECTION("Non-uniform scaling") {
        auto scale = vtx::mat4x4<float>::scale(vtx::vector<float, 3>(1.0f, 2.0f, 3.0f));
        vtx::vector<float, 3> v(1.0f, 1.0f, 1.0f);
        auto scaled = scale.transformVector(v);

        REQUIRE(scaled[0] == 1.0f);
        REQUIRE(scaled[1] == 2.0f);
        REQUIRE(scaled[2] == 3.0f);
    }
}

TEST_CASE("View matrix", "[matrix3x3]") {
    auto view = vtx::mat4x4<float>::view(
            vtx::vector<float, 3>(0.0f, 0.0f, 5.0f),
            vtx::vector<float, 3>(0.0f, 0.0f, 0.0f),
            vtx::vector<float, 3>(0.0f, 1.0f, 0.0f)
    );

    vtx::vector<float, 3> point(0.0f, 0.0f, 0.0f);
    auto transformed = view.transformPoint(point);

    REQUIRE(transformed[0] == Catch::Approx(0.0f));
    REQUIRE(transformed[1] == Catch::Approx(0.0f));
    REQUIRE(transformed[2] == Catch::Approx(-5.0f));
}

TEST_CASE("Orthographic projection", "[matrix3x3]") {
    auto ortho = vtx::mat4x4<float>::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    vtx::vector<float, 3> point(0.5f, 0.5f, -50.0f);
    auto transformed = ortho.transform4x4(point);

    REQUIRE(transformed[0] == Catch::Approx(0.5f));
    REQUIRE(transformed[1] == Catch::Approx(0.5f));
    REQUIRE(transformed[2] == Catch::Approx(0.0f).margin(0.0011f));
}

TEST_CASE("Frustum projection", "[matrix3x3]") {
    auto frustum = vtx::mat4x4<float>::frustum(-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 100.0f);
    vtx::vector<float, 3> point(0.0f, 0.0f, -2.0f);
    auto transformed = frustum.transform4x4(point);

    REQUIRE(transformed[0] == Catch::Approx(0.0f));
    REQUIRE(transformed[1] == Catch::Approx(0.0f));
    REQUIRE(transformed[2] == Catch::Approx(0.0f).margin(0.011f));
}
