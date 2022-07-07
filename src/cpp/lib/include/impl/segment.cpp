//
// Created by gogagum on 07.07.22.
//

#include "segment.h"
#include <boost/python/numpy.hpp>

namespace gseg::impl {

    namespace np = boost::python::numpy;

    np::ndarray segment(const np::ndarray &segmented, std::size_t pix_dim) {
        auto data = reinterpret_cast<double*>(segmented.get_data());

        return segmented;
    }
}