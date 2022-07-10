//
// Created by gogagum on 09.07.22.
//

#ifndef DSU_SEG_BACKEND_EDGE_H
#define DSU_SEG_BACKEND_EDGE_H

#include "pixel_view.h"

namespace gseg::impl {
    class Edge {
    public:
        /**
         * Edge constructor.
         * @param pixelView1 - first pixel.
         * @param pixelView2 - second pixel.
         */
        Edge(const PixelView& pixelView1, const PixelView& pixelView2);

        /**
         * Get pixel difference.
         * @return edge pixels distance.
         */
        [[nodiscard]] double getLength() const;
    private:
        double _length;
    };

} // impl

#endif //DSU_SEG_BACKEND_EDGE_H
