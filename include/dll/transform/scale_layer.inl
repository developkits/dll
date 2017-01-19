//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include "transform_layer.hpp"

namespace dll {

//TODO This is not as generic as it should be
//It only supports fast_matrix input otherwise the size of input and
//output will be different and it will throw an assert One easy
//solution would be to extend the support for empty matrix in ETL

/*!
 * \brief Simple scaling layer
 *
 * Note: This is only supported at the beginning of the network, no
 * backpropagation is possible for now.
 */
template <typename Desc>
struct scale_layer : transform_layer<scale_layer<Desc>> {
    using desc = Desc; ///< The descriptor type

    static constexpr const int A = desc::A; ///< The scale multiplier
    static constexpr const int B = desc::B; ///< The scale divisor

    /*!
     * \brief Returns a string representation of the layer
     */
    static std::string to_short_string() {
        return "scale";
    }

    /*!
     * \brief Apply the layer to the input
     * \param output The output
     * \param input The input to apply the layer to
     */
    template <typename Input, typename Output>
    static void activate_hidden(Output& output, const Input& input) {
        output = input * (double(A) / double(B));
    }

    /*!
     * \brief Apply the layer to the batch of input
     * \param output The batch of output
     * \param input The batch of input to apply the layer to
     */
    template <typename Input, typename Output>
    static void batch_activate_hidden(Output& output, const Input& input) {
        output = input * (double(A) / double(B));
    }

    template<typename C>
    void adapt_errors(C& context) const {
        cpp_unused(context);
    }

    template<typename H, typename C>
    void backward_batch(H&& output, C& context) const {
        cpp_unused(output);
        cpp_unused(context);
    }

    template<typename C>
    void compute_gradients(C& context) const {
        cpp_unused(context);
    }
};

} //end of dll namespace
