//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_FIELDS_ELEMENT_FP6_2OVER3_HPP
#define CRYPTO3_ALGEBRA_FIELDS_ELEMENT_FP6_2OVER3_HPP

#include <nil/crypto3/algebra/fields/detail/exponentiation.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace fields {
                namespace detail {

                    template<typename FieldParams>
                    class element_fp6_2over3 {
                        typedef FieldParams policy_type;

                    public:
                        /*constexpr static*/ const typename policy_type::non_residue_type non_residue =
                            typename policy_type::non_residue_type(policy_type::non_residue);

                        using underlying_type = typename policy_type::underlying_type;

                        using value_type = std::array<underlying_type, 2>;

                        value_type data;

                        element_fp6_2over3() {
                            data = value_type({underlying_type::zero(), underlying_type::zero()});
                        }

                        element_fp6_2over3(underlying_type in_data0, underlying_type in_data1) {
                            data = value_type({in_data0, in_data1});
                        }

                        element_fp6_2over3(const element_fp6_2over3 &other) {
                            data[0] = underlying_type(other.data[0]);
                            data[1] = underlying_type(other.data[1]);
                        };

                        inline static element_fp6_2over3 zero() {
                            return element_fp6_2over3(underlying_type::zero(), underlying_type::zero());
                        }

                        inline static element_fp6_2over3 one() {
                            return element_fp6_2over3(underlying_type::one(), underlying_type::zero());
                        }

                        bool operator==(const element_fp6_2over3 &B) const {
                            return (data[0] == B.data[0]) && (data[1] == B.data[1]);
                        }

                        bool operator!=(const element_fp6_2over3 &B) const {
                            return (data[0] != B.data[0]) || (data[1] != B.data[1]);
                        }

                        element_fp6_2over3 &operator=(const element_fp6_2over3 &B) {
                            data[0] = B.data[0];
                            data[1] = B.data[1];

                            return *this;
                        }

                        element_fp6_2over3 operator+(const element_fp6_2over3 &B) const {
                            return element_fp6_2over3(data[0] + B.data[0], data[1] + B.data[1]);
                        }

                        element_fp6_2over3 doubled() const {
                            return element_fp6_2over3(data[0].doubled(), data[1].doubled());
                        }

                        element_fp6_2over3 operator-(const element_fp6_2over3 &B) const {
                            return element_fp6_2over3(data[0] - B.data[0], data[1] - B.data[1]);
                        }

                        element_fp6_2over3 &operator-=(const element_fp6_2over3 &B) {
                            data[0] -= B.data[0];
                            data[1] -= B.data[1];

                            return *this;
                        }

                        element_fp6_2over3 &operator+=(const element_fp6_2over3 &B) {
                            data[0] += B.data[0];
                            data[1] += B.data[1];

                            return *this;
                        }

                        element_fp6_2over3 operator-() const {
                            return zero() - *this;
                        }

                        element_fp6_2over3 operator*(const element_fp6_2over3 &B) const {
                            const underlying_type A0B0 = data[0] * B.data[0], A1B1 = data[1] * B.data[1];

                            return element_fp6_2over3(A0B0 + mul_by_non_residue(A1B1),
                                                      (data[0] + data[1]) * (B.data[0] + B.data[1]) - A0B0 - A1B1);
                        }

                        element_fp6_2over3 sqrt() const {

                            // compute squared root with Tonelli--Shanks
                        }

                        element_fp6_2over3 squared() const {
                            return (*this) * (*this);    // maybe can be done more effective
                        }

                        template<typename PowerType>
                        element_fp6_2over3 pow(const PowerType &pwr) const {
                            return element_fp6_2over3(power(*this, pwr));
                        }

                        element_fp6_2over3 inversed() const {

                            /* From "High-Speed Software Implementation of the Optimal Ate Pairing over Barreto-Naehrig
                             * Curves"; Algorithm 8 */

                            const underlying_type &A0 = data[0], &A1 = data[1];

                            const underlying_type t0 = A0.squared();
                            const underlying_type t1 = A1.squared();
                            const underlying_type t2 = t0 - mul_by_non_residue(t1);
                            const underlying_type t3 = t2.inversed();
                            const underlying_type c0 = A0 * t3;
                            const underlying_type c1 = -(A1 * t3);

                            return element_fp6_2over3(c0, c1);
                        }

                        template<typename PowerType>
                        element_fp6_2over3 Frobenius_map(const PowerType &pwr) const {
                            // return element_fp6_2over3(data[0].Frobenius_map(pwr),
                            //                           policy_type::Frobenius_coeffs_c1[pwr % 6] *
                            //                           data[1].Frobenius_map(pwr)});
                            return element_fp6_2over3(
                                data[0].Frobenius_map(pwr),
                                typename policy_type::non_residue_type(policy_type::Frobenius_coeffs_c1[pwr % 6]) *
                                    data[1].Frobenius_map(pwr));
                        }

                        element_fp6_2over3 unitary_inversed() const {
                            return element_fp6_2over3(data[0], -data[1]);
                        }

                        /*element_fp6_2over3 cyclotomic_squared() const {

                            //my_Fp a_a = c0.data[0]; // a = Fp2([c0[0],c1[1]])
                            //my_Fp a_b = c1.data[1];

                            element_fp2 b = element_fp2(c1.data[0], c0.data[2]);
                            //my_Fp b_a = c1.data[0]; // b = Fp2([c1[0],c0[2]])
                            //my_Fp b_b = c0.data[2];

                            element_fp2 c = element_fp2(c0.data[1], c1.data[2]);
                            //my_Fp c_a = c0.data[1]; // c = Fp2([c0[1],c1[2]])
                            //my_Fp c_b = c1.data[2];

                            element_fp2 asq = a.squared();
                            element_fp2 bsq = b.squared();
                            element_fp2 csq = c.squared();

                            // A = vector(3*a^2 - 2*Fp2([vector(a)[0],-vector(a)[1]]))
                            //my_Fp A_a = my_Fp(3l) * asq_a - my_Fp(2l) * a_a;
                            my_Fp A_a = asq.data[0] - a.data[0];
                            A_a = A_a + A_a + asq.data[0];
                            //my_Fp A_b = my_Fp(3l) * asq_b + my_Fp(2l) * a_b;
                            my_Fp A_b = asq.data[1] + a.data[1];
                            A_b = A_b + A_b + asq.data[1];

                            // B = vector(3*Fp2([non_residue*c2[1],c2[0]]) + 2*Fp2([vector(b)[0],-vector(b)[1]]))
                            //my_Fp B_a = my_Fp(3l) * underlying_type::non_residue * csq_b + my_Fp(2l) * b_a;
                            my_Fp B_tmp = underlying_type::non_residue * csq.data[1];
                            my_Fp B_a = B_tmp + b.data[0];
                            B_a = B_a + B_a + B_tmp;

                            //my_Fp B_b = my_Fp(3l) * csq_a - my_Fp(2l) * b_b;
                            my_Fp B_b = csq.data[0] - b.data[1];
                            B_b = B_b + B_b + csq.data[0];

                            // C = vector(3*b^2 - 2*Fp2([vector(c)[0],-vector(c)[1]]))
                            //my_Fp C_a = my_Fp(3l) * bsq_a - my_Fp(2l) * c_a;
                            my_Fp C_a = bsq.data[0] - c.data[0];
                            C_a = C_a + C_a + bsq.data[0];
                            // my_Fp C_b = my_Fp(3l) * bsq_b + my_Fp(2l) * c_b;
                            my_Fp C_b = bsq.data[1] + c.data[1];
                            C_b = C_b + C_b + bsq.data[1];

                            // e0 = Fp3([A[0],C[0],B[1]])
                            // e1 = Fp3([B[0],A[1],C[1]])
                            // fin = Fp6e([e0,e1])
                            // return fin

                            return element_fp6_2over3(underlying_type(A_a, C_a, B_b),
                                                                underlying_type(B_a, A_b, C_b));
                        }*/

                        template<typename PowerType>
                        element_fp6_2over3 cyclotomic_exp(const PowerType &exponent) const {
                            // naive implementation
                            return this->squared();

                            /*element_fp6_2over3 res = one();
                            element_fp6_2over3 this_inverse = this->unitary_inversed();

                            bool found_nonzero = false;
                            std::vector<long> NAF = find_wnaf(1, exponent);

                            for (long i = static_cast<long>(NAF.size() - 1); i >= 0; --i) {
                                if (found_nonzero) {
                                    res = res.cyclotomic_squared();
                                }

                                if (NAF[i] != 0) {
                                    found_nonzero = true;

                                    if (NAF[i] > 0) {
                                        res = res * (*this);
                                    }
                                    else {
                                        res = res * this_inverse;
                                    }
                                }
                            }

                            return res;*/
                        }

                        /*inline static*/ underlying_type mul_by_non_residue(const underlying_type &A) const {
                            return underlying_type(non_residue * A.data[2], A.data[1], A.data[0]);
                        }

                        element_fp6_2over3 mul_by_2345(const element_fp6_2over3 &other) const {
                            /* Devegili OhEig Scott Dahab --- Multiplication and Squaring on Pairing-Friendly
                             * Fields.pdf; Section 3 (Karatsuba) */

                            const underlying_type &B = other.data[1], &A = other.data[0], &b = this->data[1],
                                                  &a = this->data[0];
                            const underlying_type aA = underlying_type(a.data[1] * A.data[2] * non_residue,
                                                                       a.data[2] * A.data[2] * non_residue,
                                                                       a.data[0] * A.data[2]);
                            const underlying_type bB = b * B;
                            const underlying_type beta_bB = element_fp6_2over3::mul_by_non_residue(bB);

                            return element_fp6_2over3(aA + beta_bB, (a + b) * (A + B) - aA - bB);
                        }
                    };

                    template<typename FieldParams>
                    element_fp6_2over3<FieldParams>
                        operator*(const typename FieldParams::underlying_type::underlying_type &lhs,
                                  const element_fp6_2over3<FieldParams> &rhs) {

                        return element_fp6_2over3<FieldParams>(lhs * rhs.data[0], lhs * rhs.data[1]);
                    }

                    template<typename FieldParams>
                    element_fp6_2over3<FieldParams>
                        operator*(const element_fp6_2over3<FieldParams> &lhs,
                                  const typename FieldParams::underlying_type::underlying_type &rhs) {

                        return rhs * lhs;
                    }

                }    // namespace detail
            }        // namespace fields
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil

#endif    // ALGEBRA_FIELDS_ELEMENT_FP6_2OVER3_HPP
