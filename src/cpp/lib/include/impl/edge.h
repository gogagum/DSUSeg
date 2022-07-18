//
// Created by gogagum on 09.07.22.
//

#ifndef DSU_SEG_BACKEND_EDGE_H
#define DSU_SEG_BACKEND_EDGE_H

#include "pixel_view.h"

namespace gseg::impl {

    ////////////////////////////////////////////////////////////////////////////
    /**
     * class Edge
     */
    class Edge {
    public:
        /**
         * Edge constructor.
         * @param pixelView1 - first pixel.
         * @param pixelView2 - second pixel.
         */
        Edge(const PixelView& pixelView1, const PixelView& pixelView2);

        /**
         * Edge copy constructor.
         * @param other - edge to copy from.
         */
        Edge(const Edge& other) = default;

        /**
         * Edge move assignment.
         * @param other - edge to move from.
         * @return reference to itself.
         */
        Edge& operator=(Edge&& other) = default;

        /**
         * Get pixel difference.
         * @return edge pixels distance.
         */
        [[nodiscard]] double getLength() const;

        /**
         * Get a pair of pixel views of dots connected by edge.
         * @return two pixel views references.
         */
        [[nodiscard]] std::pair<PixelViewConstRef , PixelViewConstRef>
        getPixelViews() const;

    private:
        // Distance between two pixels
        double _pixelsDistance;
        // One pixel view
        PixelView _pv1;
        // Other pixel view
        PixelView _pv2;
    };

} // impl

#endif //DSU_SEG_BACKEND_EDGE_H
