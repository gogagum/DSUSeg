//
// Created by gogagum on 07.07.22.
//

#include <boost/python/numpy.hpp>
#include "segment.h"
#include "data_view.h"

namespace gseg::impl {

    namespace np = boost::python::numpy;

    np::ndarray segment(const np::ndarray &segmented, std::size_t lastDim) {
        auto data = reinterpret_cast<double*>(segmented.get_data());

        auto shape =
                reinterpret_cast<const std::size_t*>(segmented.get_shape());
        auto dataView =
                gdsu::impl::DataView(data, {shape[0], shape[1], lastDim});

        return segmented;
    }
}