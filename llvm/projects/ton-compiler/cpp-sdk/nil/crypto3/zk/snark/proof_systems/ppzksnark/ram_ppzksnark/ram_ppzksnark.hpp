//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//
// @file Declaration of interfaces for a ppzkSNARK for RAM.
//
// This includes:
// - the class for a proving key;
// - the class for a verification key;
// - the class for a key pair (proving key & verification key);
// - the class for a proof;
// - the generator algorithm;
// - the prover algorithm;
// - the verifier algorithm.
//
// The implementation follows, extends, and optimizes the approach described
// in \[BCTV14] (itself building on \[BCGTV13]). In particular, the ppzkSNARK
// for RAM is constructed from a ppzkSNARK for R1CS.
//
//
// Acronyms:
//
// "R1CS" = "Rank-1 Constraint Systems"
// "RAM" = "Random-Access Machines"
// "ppzkSNARK" = "Pre-Processing Zero-Knowledge Succinct Non-interactive ARgument of Knowledge"
//
// References:
//
// \[BCGTV13]:
// "SNARKs for C: verifying program executions succinctly and in zero knowledge",
// Eli Ben-Sasson, Alessandro Chiesa, Daniel Genkin, Eran Tromer, Madars Virza,
// CRYPTO 2014,
// <http://eprint.iacr.org/2013/507>
//
// \[BCTV14]:
// "Succinct Non-Interactive Zero Knowledge for a von Neumann Architecture",
// Eli Ben-Sasson, Alessandro Chiesa, Eran Tromer, Madars Virza,
// USENIX Security 2014,
// <http://eprint.iacr.org/2013/879>
//---------------------------------------------------------------------------///** @file

#ifndef CRYPTO3_ZK_RAM_PPZKSNARK_HPP
#define CRYPTO3_ZK_RAM_PPZKSNARK_HPP

#include <memory>

#include <nil/crypto3/zk/snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <nil/crypto3/zk/snark/proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include <nil/crypto3/zk/snark/proof_systems/ppzksnark/ram_ppzksnark/ram_ppzksnark_params.hpp>

namespace nil {
    namespace crypto3 {
        namespace zk {
            namespace snark {

                /******************************** Proving key ********************************/

                /**
                 * A proving key for the RAM ppzkSNARK.
                 */
                template<typename ram_ppzksnark_ppT>
                class ram_ppzksnark_proving_key {
                public:
                    typedef ram_ppzksnark_snark_pp<ram_ppzksnark_ppT> snark_ppT;

                    r1cs_ppzksnark_proving_key<snark_ppT> r1cs_pk;
                    ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> ap;
                    std::size_t primary_input_size_bound;
                    std::size_t time_bound;

                    ram_ppzksnark_proving_key() {
                    }
                    ram_ppzksnark_proving_key(const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &other) = default;
                    ram_ppzksnark_proving_key(ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &&other) = default;
                    ram_ppzksnark_proving_key(r1cs_ppzksnark_proving_key<snark_ppT> &&r1cs_pk,
                                              const ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> &ap,
                                              const std::size_t primary_input_size_bound,
                                              const std::size_t time_bound) :
                        r1cs_pk(std::move(r1cs_pk)),
                        ap(ap), primary_input_size_bound(primary_input_size_bound), time_bound(time_bound) {
                    }

                    ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &
                        operator=(const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &other) = default;

                    bool operator==(const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &other) const;
                };

                /******************************* Verification key ****************************/

                /**
                 * A verification key for the RAM ppzkSNARK.
                 */
                template<typename ram_ppzksnark_ppT>
                class ram_ppzksnark_verification_key {
                public:
                    typedef ram_ppzksnark_snark_pp<ram_ppzksnark_ppT> snark_ppT;

                    r1cs_ppzksnark_verification_key<snark_ppT> r1cs_vk;
                    ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> ap;
                    std::size_t primary_input_size_bound;
                    std::size_t time_bound;

                    std::set<std::size_t> bound_primary_input_locations;

                    ram_ppzksnark_verification_key() = default;
                    ram_ppzksnark_verification_key(const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &other) =
                        default;
                    ram_ppzksnark_verification_key(ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &&other) = default;
                    ram_ppzksnark_verification_key(const r1cs_ppzksnark_verification_key<snark_ppT> &r1cs_vk,
                                                   const ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> &ap,
                                                   const std::size_t primary_input_size_bound,
                                                   const std::size_t time_bound) :
                        r1cs_vk(r1cs_vk),
                        ap(ap), primary_input_size_bound(primary_input_size_bound), time_bound(time_bound) {
                    }

                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &
                        operator=(const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &other) = default;

                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT>
                        bind_primary_input(const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input) const;

                    bool operator==(const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &other) const;
                };

                /********************************** Key pair *********************************/

                /**
                 * A key pair for the RAM ppzkSNARK, which consists of a proving key and a verification key.
                 */
                template<typename ram_ppzksnark_ppT>
                struct ram_ppzksnark_keypair {
                public:
                    ram_ppzksnark_proving_key<ram_ppzksnark_ppT> pk;
                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT> vk;

                    ram_ppzksnark_keypair() = default;
                    ram_ppzksnark_keypair(ram_ppzksnark_keypair<ram_ppzksnark_ppT> &&other) = default;
                    ram_ppzksnark_keypair(const ram_ppzksnark_keypair<ram_ppzksnark_ppT> &other) = default;
                    ram_ppzksnark_keypair(ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &&pk,
                                          ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &&vk) :
                        pk(std::move(pk)),
                        vk(std::move(vk)) {
                    }
                };

                /*********************************** Proof ***********************************/

                /**
                 * A proof for the RAM ppzkSNARK.
                 */
                template<typename ram_ppzksnark_ppT>
                using ram_ppzksnark_proof = r1cs_ppzksnark_proof<ram_ppzksnark_snark_pp<ram_ppzksnark_ppT>>;

                /***************************** Main algorithms *******************************/

                /**
                 * A generator algorithm for the RAM ppzkSNARK.
                 *
                 * Given a choice of architecture parameters and computation bounds, this algorithm
                 * produces proving and verification keys for all computations that respect these choices.
                 */
                template<typename ram_ppzksnark_ppT>
                ram_ppzksnark_keypair<ram_ppzksnark_ppT>
                    ram_ppzksnark_generator(const ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> &ap,
                                            const std::size_t primary_input_size_bound,
                                            const std::size_t time_bound);

                /**
                 * A prover algorithm for the RAM ppzkSNARK.
                 *
                 * Given a proving key, primary input X, and auxiliary input Y, this algorithm
                 * produces a proof (of knowledge) that attests to the following statement:
                 *               ``there exists Y such that X(Y) accepts''.
                 *
                 * Above, it has to be the case that the computation respects the bounds:
                 * - the size of X is at most primary_input_size_bound, and
                 * - the time to compute X(Y) is at most time_bound.
                 */
                template<typename ram_ppzksnark_ppT>
                ram_ppzksnark_proof<ram_ppzksnark_ppT>
                    ram_ppzksnark_prover(const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &pk,
                                         const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input,
                                         const ram_ppzksnark_auxiliary_input<ram_ppzksnark_ppT> &auxiliary_input);

                /**
                 * A verifier algorithm for the RAM ppzkSNARK.
                 *
                 * This algorithm is universal in the sense that the verification key
                 * supports proof verification for any choice of primary input
                 * provided that the computation respects the bounds.
                 */
                template<typename ram_ppzksnark_ppT>
                bool ram_ppzksnark_verifier(const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &vk,
                                            const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input,
                                            const ram_ppzksnark_proof<ram_ppzksnark_ppT> &proof);

                template<typename ram_ppzksnark_ppT>
                bool ram_ppzksnark_proving_key<ram_ppzksnark_ppT>::operator==(
                    const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &other) const {
                    return (this->r1cs_pk == other.r1cs_pk && this->ap == other.ap &&
                            this->primary_input_size_bound == other.primary_input_size_bound &&
                            this->time_bound == other.time_bound);
                }

                template<typename ram_ppzksnark_ppT>
                ram_ppzksnark_verification_key<ram_ppzksnark_ppT>
                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT>::bind_primary_input(
                        const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input) const {
                    typedef ram_ppzksnark_machine_pp<ram_ppzksnark_ppT> ram_ppT;
                    typedef ram_base_field<ram_ppT> FieldType;

                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT> result(*this);

                    const std::size_t packed_input_element_size =
                        ram_universal_component<ram_ppT>::packed_input_element_size(ap);

                    for (auto it : primary_input.get_all_trace_entries()) {
                        const std::size_t input_pos = it.first;
                        const address_and_value av = it.second;

                        assert(input_pos < primary_input_size_bound);
                        assert(result.bound_primary_input_locations.find(input_pos) ==
                               result.bound_primary_input_locations.end());

                        const std::vector<typename FieldType::value_type> packed_input_element =
                            ram_to_r1cs<ram_ppT>::pack_primary_input_address_and_value(ap, av);
                        result.r1cs_vk.encoded_IC_query =
                            result.r1cs_vk.encoded_IC_query.template accumulate_chunk<FieldType>(
                                packed_input_element.begin(),
                                packed_input_element.end(),
                                packed_input_element_size * (primary_input_size_bound - 1 - input_pos));

                        result.bound_primary_input_locations.insert(input_pos);
                    }

                    return result;
                }

                template<typename ram_ppzksnark_ppT>
                bool ram_ppzksnark_verification_key<ram_ppzksnark_ppT>::operator==(
                    const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &other) const {
                    return (this->r1cs_vk == other.r1cs_vk && this->ap == other.ap &&
                            this->primary_input_size_bound == other.primary_input_size_bound &&
                            this->time_bound == other.time_bound);
                }

                template<typename ram_ppzksnark_ppT>
                ram_ppzksnark_keypair<ram_ppzksnark_ppT>
                    ram_ppzksnark_generator(const ram_ppzksnark_architecture_params<ram_ppzksnark_ppT> &ap,
                                            const std::size_t primary_input_size_bound,
                                            const std::size_t time_bound) {
                    typedef ram_ppzksnark_machine_pp<ram_ppzksnark_ppT> ram_ppT;
                    typedef ram_ppzksnark_snark_pp<ram_ppzksnark_ppT> snark_ppT;

                    ram_to_r1cs<ram_ppT> universal_r1cs(ap, primary_input_size_bound, time_bound);
                    universal_r1cs.instance_map();
                    r1cs_ppzksnark_keypair<snark_ppT> ppzksnark_keypair =
                        r1cs_ppzksnark_generator<snark_ppT>(universal_r1cs.get_constraint_system());

                    ram_ppzksnark_proving_key<ram_ppzksnark_ppT> pk = ram_ppzksnark_proving_key<ram_ppzksnark_ppT>(
                        std::move(ppzksnark_keypair.pk), ap, primary_input_size_bound, time_bound);
                    ram_ppzksnark_verification_key<ram_ppzksnark_ppT> vk =
                        ram_ppzksnark_verification_key<ram_ppzksnark_ppT>(
                            std::move(ppzksnark_keypair.vk), ap, primary_input_size_bound, time_bound);

                    return ram_ppzksnark_keypair<ram_ppzksnark_ppT>(std::move(pk), std::move(vk));
                }

                template<typename ram_ppzksnark_ppT>
                ram_ppzksnark_proof<ram_ppzksnark_ppT>
                    ram_ppzksnark_prover(const ram_ppzksnark_proving_key<ram_ppzksnark_ppT> &pk,
                                         const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input,
                                         const ram_ppzksnark_auxiliary_input<ram_ppzksnark_ppT> &auxiliary_input) {
                    typedef ram_ppzksnark_machine_pp<ram_ppzksnark_ppT> ram_ppT;
                    typedef ram_ppzksnark_snark_pp<ram_ppzksnark_ppT> snark_ppT;
                    typedef typename snark_ppT::scalar_field_type FieldType;

                    ram_to_r1cs<ram_ppT> universal_r1cs(pk.ap, pk.primary_input_size_bound, pk.time_bound);
                    const r1cs_primary_input<FieldType> r1cs_primary_input =
                        ram_to_r1cs<ram_ppT>::primary_input_map(pk.ap, pk.primary_input_size_bound, primary_input);

                    const r1cs_auxiliary_input<FieldType> r1cs_auxiliary_input =
                        universal_r1cs.auxiliary_input_map(primary_input, auxiliary_input);
                    const r1cs_ppzksnark_proof<snark_ppT> proof =
                        r1cs_ppzksnark_prover<snark_ppT>(pk.r1cs_pk, r1cs_primary_input, r1cs_auxiliary_input);

                    return proof;
                }

                template<typename ram_ppzksnark_ppT>
                bool ram_ppzksnark_verifier(const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> &vk,
                                            const ram_ppzksnark_primary_input<ram_ppzksnark_ppT> &primary_input,
                                            const ram_ppzksnark_proof<ram_ppzksnark_ppT> &proof) {
                    typedef ram_ppzksnark_snark_pp<ram_ppzksnark_ppT> snark_ppT;

                    const ram_ppzksnark_verification_key<ram_ppzksnark_ppT> input_specific_vk =
                        vk.bind_primary_input(primary_input);
                    const bool ans = r1cs_ppzksnark_verifier_weak_IC<snark_ppT>(
                        input_specific_vk.r1cs_vk, r1cs_primary_input<typename snark_ppT::scalar_field_type>(), proof);

                    return ans;
                }

            }    // namespace snark
        }        // namespace zk
    }            // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_ZK_RAM_PPZKSNARK_HPP
