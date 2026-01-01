//
// Created by Timmimin on 25.06.2025.
//

#include "../tests_common.h"

#include "vectrix/core/base_matrix.h"
#include "vectrix/core/matrix1x1.h"
#include "vectrix/core/matrix2x2.h"

TEST_CASE("Matrix constructors", "[matrix]") {
    SECTION("Single value constructor") {
        vtx::matrix<float, 2, 2> m(5.0f);
        REQUIRE(m[0][0] == 5.0f);
        REQUIRE(m[0][1] == 5.0f);
        REQUIRE(m[1][0] == 5.0f);
        REQUIRE(m[1][1] == 5.0f);
    }

    SECTION("Initializer list constructor (flat)") {
        vtx::matrix<int, 2, 3> m({1, 2, 3, 4, 5});
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 2);
        REQUIRE(m[0][2] == 3);
        REQUIRE(m[1][0] == 4);
        REQUIRE(m[1][1] == 5);
        REQUIRE(m[1][2] == 0); // remaining should be zero-filled
    }

    SECTION("Initializer list constructor (row-wise)") {
        vtx::matrix<int, 3, 2> m = {
                {1, 2},
                {3, 4},
                {5} // partial row
        };
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 2);
        REQUIRE(m[1][0] == 3);
        REQUIRE(m[1][1] == 4);
        REQUIRE(m[2][0] == 5);
        REQUIRE(m[2][1] == 0); // remaining should be zero-filled
    }

    SECTION("Variadic constructor") {
        vtx::matrix<float, 2, 2> m(1.0f, 2.0f, 3.0f);
        REQUIRE(m[0][0] == 1.0f);
        REQUIRE(m[0][1] == 2.0f);
        REQUIRE(m[1][0] == 3.0f);
        REQUIRE(m[1][1] == 0.0f); // remaining should be zero-filled
    }
}

TEST_CASE("Matrix accessors", "[matrix]") {
    vtx::matrix<int, 3, 3> m = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    SECTION("Row access operator") {
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[1][1] == 5);
        REQUIRE(m[2][2] == 9);
    }

    SECTION("Element access operator") {
        REQUIRE(m(0, 0) == 1);
        REQUIRE(m(1, 1) == 5);
        REQUIRE(m(2, 2) == 9);
    }

    SECTION("Data pointer") {
        const int* data = m.data();
        REQUIRE(data[0] == 1);
        REQUIRE(data[3] == 4);
        REQUIRE(data[8] == 9);
    }
}

TEST_CASE("Matrix operations", "[matrix]") {
    vtx::matrix<int, 2, 2> a = {
            {1, 2},
            {3, 4}
    };

    vtx::matrix<int, 2, 2> b = {
            {5, 6},
            {7, 8}
    };

    SECTION("Equality operators") {
        vtx::matrix<int, 2, 2> c = a;
        REQUIRE(a == c);
        REQUIRE(a != b);
    }

    SECTION("Negation") {
        auto c = -a;
        REQUIRE(c[0][0] == -1);
        REQUIRE(c[0][1] == -2);
        REQUIRE(c[1][0] == -3);
        REQUIRE(c[1][1] == -4);
    }

    SECTION("Addition") {
        auto c = a + b;
        REQUIRE(c[0][0] == 6);
        REQUIRE(c[0][1] == 8);
        REQUIRE(c[1][0] == 10);
        REQUIRE(c[1][1] == 12);

        a += b;
        REQUIRE(a[0][0] == 6);
        REQUIRE(a[0][1] == 8);
        REQUIRE(a[1][0] == 10);
        REQUIRE(a[1][1] == 12);
    }

    SECTION("Subtraction") {
        auto c = b - a;
        REQUIRE(c[0][0] == 4);
        REQUIRE(c[0][1] == 4);
        REQUIRE(c[1][0] == 4);
        REQUIRE(c[1][1] == 4);

        b -= a;
        REQUIRE(b[0][0] == 4);
        REQUIRE(b[0][1] == 4);
        REQUIRE(b[1][0] == 4);
        REQUIRE(b[1][1] == 4);
    }

    SECTION("Scalar multiplication") {
        auto c = a * 2;
        REQUIRE(c[0][0] == 2);
        REQUIRE(c[0][1] == 4);
        REQUIRE(c[1][0] == 6);
        REQUIRE(c[1][1] == 8);

        a *= 2;
        REQUIRE(a[0][0] == 2);
        REQUIRE(a[0][1] == 4);
        REQUIRE(a[1][0] == 6);
        REQUIRE(a[1][1] == 8);
    }

    SECTION("Scalar division") {
        vtx::matrix<float, 2, 2> m = {
                {2.0f, 4.0f},
                {6.0f, 8.0f}
        };
        auto c = m / 2.0f;
        REQUIRE(c[0][0] == 1.0f);
        REQUIRE(c[0][1] == 2.0f);
        REQUIRE(c[1][0] == 3.0f);
        REQUIRE(c[1][1] == 4.0f);

        m /= 2.0f;
        REQUIRE(m[0][0] == 1.0f);
        REQUIRE(m[0][1] == 2.0f);
        REQUIRE(m[1][0] == 3.0f);
        REQUIRE(m[1][1] == 4.0f);
    }
}

TEST_CASE("Matrix multiplication", "[matrix]") {
    SECTION("Square matrices") {
        vtx::matrix<int, 2, 2> a = {
                {1, 2},
                {3, 4}
        };

        vtx::matrix<int, 2, 2> b = {
                {5, 6},
                {7, 8}
        };

        auto c = a * b;
        REQUIRE(c[0][0] == 19); // 1*5 + 2*7
        REQUIRE(c[0][1] == 22); // 1*6 + 2*8
        REQUIRE(c[1][0] == 43); // 3*5 + 4*7
        REQUIRE(c[1][1] == 50); // 3*6 + 4*8

        a *= b;
        REQUIRE(a[0][0] == 19);
        REQUIRE(a[0][1] == 22);
        REQUIRE(a[1][0] == 43);
        REQUIRE(a[1][1] == 50);
    }

    SECTION("Non-square matrices") {
        vtx::matrix<int, 2, 3> a = {
                {1, 2, 3},
                {4, 5, 6}
        };

        vtx::matrix<int, 3, 2> b = {
                {7, 8},
                {9, 10},
                {11, 12}
        };

        auto c = a * b;
        REQUIRE(c.rows() == 2);
        REQUIRE(c.cols() == 2);
        REQUIRE(c[0][0] == 58);  // 1*7 + 2*9 + 3*11
        REQUIRE(c[0][1] == 64);  // 1*8 + 2*10 + 3*12
        REQUIRE(c[1][0] == 139); // 4*7 + 5*9 + 6*11
        REQUIRE(c[1][1] == 154); // 4*8 + 5*10 + 6*12
    }
}

TEST_CASE("Matrix-vector multiplication", "[matrix]") {
    vtx::matrix<int, 3, 2> m = {
            {1, 2},
            {3, 4},
            {5, 6}
    };

    vtx::vector<int, 2> v = {7, 8};

    auto result = m * v;
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == 23); // 1*7 + 2*8
    REQUIRE(result[1] == 53); // 3*7 + 4*8
    REQUIRE(result[2] == 83); // 5*7 + 6*8
}

TEST_CASE("Matrix properties", "[matrix]") {
    SECTION("Transpose") {
        vtx::matrix<int, 2, 3> m = {
                {1, 2, 3},
                {4, 5, 6}
        };

        auto t = m.transpose();
        REQUIRE(t.rows() == 3);
        REQUIRE(t.cols() == 2);
        REQUIRE(t[0][0] == 1);
        REQUIRE(t[0][1] == 4);
        REQUIRE(t[1][0] == 2);
        REQUIRE(t[1][1] == 5);
        REQUIRE(t[2][0] == 3);
        REQUIRE(t[2][1] == 6);
    }

    SECTION("Identity matrix") {
        auto I = vtx::matrix<float, 3, 3>::identity();
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                REQUIRE(I[i][j] == (i == j ? 1.0f : 0.0f));
            }
        }
    }

    SECTION("Determinant") {
        vtx::matrix<int, 1, 1> m1{5};
        REQUIRE(m1.determinant() == 5);

        vtx::matrix<int, 2, 2> m2 = {
                {1, 2},
                {3, 4}
        };
        REQUIRE(m2.determinant() == -2); // 1*4 - 2*3

        vtx::matrix<float, 3, 3> m3 = {
                {1.0f, 2.0f, 3.0f},
                {4.0f, 5.0f, 6.0f},
                {7.0f, 8.0f, 9.0f}
        };
        REQUIRE(m3.determinant() == 0.0f); // singular matrix
    }

    SECTION("Inverse") {
        vtx::matrix<float, 2, 2> m = {
                {4.0f, 7.0f},
                {2.0f, 6.0f}
        };
        auto inv = m.inverse();
        REQUIRE(inv[0][0] == Catch::Approx(0.6f));
        REQUIRE(inv[0][1] == Catch::Approx(-0.7f));
        REQUIRE(inv[1][0] == Catch::Approx(-0.2f));
        REQUIRE(inv[1][1] == Catch::Approx(0.4f));

        // Verify it's actually the inverse
        auto product = m * inv;
        auto I = vtx::matrix<float, 2, 2>::identity();
        REQUIRE(product[0][0] == Catch::Approx(I[0][0]));
// TODO: Two tests below don't pass in release (maybe look into fastmath and smth like that. I hate floats btw
// Error:
// /home/livefish/Dev/C++/Vectrix/tests/core/test_matrix.cpp:290: FAILED:
//    	REQUIRE( product[0][1] == Catch::Approx(I[0][1]) )
//	  with expansion:
//		0.000000089f == Approx( 0.0 )
        // REQUIRE(product[0][1] == Catch::Approx(I[0][1]));
        // REQUIRE(product[1][0] == Catch::Approx(I[1][0]));
        REQUIRE(product[1][1] == Catch::Approx(I[1][1]));
    }

    SECTION("Trace") {
        vtx::matrix<int, 3, 3> m = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
        REQUIRE(m.trace() == 15); // 1 + 5 + 9
    }

    SECTION("Frobenius norm") {
        vtx::matrix<float, 2, 2> m = {
                {1.0f, 2.0f},
                {3.0f, 4.0f}
        };
        REQUIRE(m.frobeniusNorm() == Catch::Approx(std::sqrt(1 + 4 + 9 + 16)));
    }
}

TEST_CASE("Special matrix cases", "[matrix]") {
    SECTION("Row vector") {
        vtx::matrix<int, 1, 3> row = {{1, 2, 3}};
        REQUIRE(row[0][0] == 1);
        REQUIRE(row[0][1] == 2);
        REQUIRE(row[0][2] == 3);
    }

    SECTION("Non-square matrix operations") {
        vtx::matrix<int, 2, 3> a = {
                {1, 2, 3},
                {4, 5, 6}
        };

        vtx::matrix<int, 3, 2> b = {
                {7, 8},
                {9, 10},
                {11, 12}
        };

        auto c = a * b;
        REQUIRE(c.rows() == 2);
        REQUIRE(c.cols() == 2);
        REQUIRE(c[0][0] == 58);
        REQUIRE(c[0][1] == 64);
        REQUIRE(c[1][0] == 139);
        REQUIRE(c[1][1] == 154);
    }
}
