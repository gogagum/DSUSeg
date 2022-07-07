//
// Created by gogagum on 07.07.22.
//

#include <exception>
#include <string>
#include <boost/python/numpy.hpp>
#include "dsu_seg_impl.h"
#include "impl/segment.h"

namespace gseg {

    namespace np = boost::python::numpy;

    np::ndarray segment(const np::ndarray &segmented) {
        if (std::size_t dim_num = segmented.get_nd(); dim_num != 2 &&
                                                      dim_num != 3) {
            throw std::invalid_argument(
                    "Wrong number of dimensions: " + std::to_string(dim_num));  // TODO: python exception directly
        } else if (auto dtype = segmented.get_dtype();
            dtype != np::dtype::get_builtin<double>() &&
            dtype != np::dtype::get_builtin<int>()) {
            throw std::invalid_argument("Wrong data type.");  // TODO: python exception directly
        } else {
            std::size_t last_dim = 1;
            if (dim_num == 3) {
                last_dim = segmented.get_shape()[2];
            }

            return impl::segment(segmented, last_dim);
        }
    }
}