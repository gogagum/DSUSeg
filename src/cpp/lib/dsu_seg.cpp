//
// Created by gogagum on 07.07.22.
//

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace np = boost::python::numpy;

np::ndarray segment(const np::ndarray& segmented) {
    return segmented;
}

BOOST_PYTHON_MODULE(dsu_seg_bachend)
{
    Py_Initialize();
    np::initialize();
    boost::python::def("print_dims", segment);
}