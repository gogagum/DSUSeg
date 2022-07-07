//
// Created by gogagum on 07.07.22.
//

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include "include/dsu_seg_impl.h"

BOOST_PYTHON_MODULE(dsu_seg_bachend)
{
    Py_Initialize();
    boost::python::numpy::initialize();
    boost::python::def("print_dims", gseg::segment);
}