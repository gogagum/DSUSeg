#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include <iostream>

void print_dims(const boost::python::numpy::ndarray& x) {
    auto shape = x.get_shape();
    std::size_t dimNum = x.get_nd();
    for (std::size_t i = 0; i < dimNum; ++i) {
        std::cout << shape[i] << ", ";
    }
    std::cout << std::endl;
}

BOOST_PYTHON_MODULE(test_cpp_functions)
{
    Py_Initialize();
    boost::python::numpy::initialize();
    boost::python::def("print_dims", print_dims);
}

