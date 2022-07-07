//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_SEGMENT_H
#define DSU_SEG_BACKEND_SEGMENT_H

#include <boost/python/numpy.hpp>

namespace gseg::impl {
    boost::python::numpy::ndarray
    segment(const boost::python::numpy::ndarray &segmented, std::size_t pix_dim);
}

#endif //DSU_SEG_BACKEND_SEGMENT_H
