//
// Created by gogagum on 08.07.22.
//

#ifndef DSU_SEG_BACKEND_SEGMENTER_H
#define DSU_SEG_BACKEND_SEGMENTER_H

#include <boost/python/numpy.hpp>
#include <DSUWithData.hpp>
#include "component_data.h"
#include "data_view.h"
#include "edge.h"

namespace gseg::impl {

    namespace np = boost::python::numpy;
    namespace p = boost::python;

    ////////////////////////////////////////////////////////////////////////////
    // class Segmenter
    class Segmenter {
    public:
        /**
         * Segmenter constructor.
         * @param dataView - view to a file.
         */
        explicit Segmenter(DataView&& dataView);
    private:
        /**
         * Initialize DSU.
         */
        void _initDSU();

        /**
         * Generate graph edges.
         */
        void _generateEdges();

        /**
         * Sort edges by pixel distance.
         */
        void _sortEdges();

        /**
         * Process image by DSU segmentation algorithm.
         */
        void _process();

        /**
         * TODO
         * @return
         */
        [[nodiscard]] np::ndarray _getSegmentsMapImpl();

    private:
        // Edges list.
        std::vector<Edge> _edges;
        // View to an image data.
        DataView _dataView;
        // DSU of pixels.
        gdsu::DSUWithData<PixelView, ComponentData, PixelViewImplCmp> _dsu;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_SEGMENTER_H
