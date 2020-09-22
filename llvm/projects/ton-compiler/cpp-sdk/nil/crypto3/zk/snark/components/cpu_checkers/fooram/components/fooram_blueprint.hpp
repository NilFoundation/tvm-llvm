//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//
// @file Declaration of interfaces for a protoboard for the FOORAM CPU.
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ZK_FOORAM_PROTOBOARD_HPP
#define CRYPTO3_ZK_FOORAM_PROTOBOARD_HPP

#include <nil/crypto3/zk/snark/component.hpp>
#include <nil/crypto3/zk/snark/relations/ram_computations/rams/fooram/fooram_aux.hpp>

namespace nil {
    namespace crypto3 {
        namespace zk {
            namespace snark {

                template<typename FieldType>
                class fooram_protoboard : public blueprint<FieldType> {
                public:
                    const fooram_architecture_params ap;

                    fooram_protoboard(const fooram_architecture_params &ap);
                };

                template<typename FieldType>
                class fooram_component : public component<FieldType> {
                protected:
                    fooram_protoboard<FieldType> &pb;

                public:
                    fooram_component(fooram_protoboard<FieldType> &pb);
                };

                template<typename FieldType>
                fooram_protoboard<FieldType>::fooram_protoboard(const fooram_architecture_params &ap) :
                    blueprint<FieldType>(), ap(ap) {
                }

                template<typename FieldType>
                fooram_component<FieldType>::fooram_component(fooram_protoboard<FieldType> &pb) :
                    component<FieldType>(pb), pb(pb) {
                }

            }    // namespace snark
        }        // namespace zk
    }            // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_ZK_FOORAM_PROTOBOARD_HPP
