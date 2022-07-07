//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_DSU_SEG_IMPL_H
#define DSU_SEG_BACKEND_DSU_SEG_IMPL_H

#include <boost/python/numpy.hpp>

namespace gseg {
    boost::python::numpy::ndarray
    segment(const boost::python::numpy::ndarray &segmented);
}

#endif //DSU_SEG_BACKEND_DSU_SEG_IMPL_H
