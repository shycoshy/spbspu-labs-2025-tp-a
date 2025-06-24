#include "geometry.h"
#include <numeric>
#include <cmath>
#include <algorithm>

namespace asafov {

double computeArea(const Polygon& poly) {
    const auto& pts = poly.points;
    if (pts.size() < 3) return 0.0;

    auto area_op = [](const Point& p1, const Point& p2) {
        return (p1.x * p2.y) - (p2.x * p1.y);
    };

    double sum = std::inner_product(
        pts.begin(), pts.end() - 1,
        pts.begin() + 1,
        0.0,
        std::plus<>(),
        area_op
    );
    sum += area_op(pts.back(), pts.front());

    return std::abs(sum) / 2.0;
}

bool edgesIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    auto cross = [](const Point& p, const Point& q) { return p.x*q.y - p.y*q.x; };
    Point r = {a2.x-a1.x, a2.y-a1.y};
    Point s = {b2.x-b1.x, b2.y-b1.y};
    Point qp = {b1.x-a1.x, b1.y-a1.y};

    double rxs = cross(r, s);
    double qpxr = cross(qp, r);

    if (std::abs(rxs) < 1e-10) return false;

    double t = cross(qp, s)/rxs;
    double u = qpxr/rxs;

    return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b) {
    auto check_edges = [](const Polygon& p1, const Polygon& p2) {
        auto edge_intersect = [&p2](const Point& pt1) {
            const Point& pt2 = p1.points[(&pt1 - &p1.points[0] + 1) % p1.points.size()];
            return std::any_of(p2.points.begin(), p2.points.end(),
                [&pt1, &pt2](const Point& pt3) {
                    const Point& pt4 = p2.points[(&pt3 - &p2.points[0] + 1) % p2.points.size()];
                    return edgesIntersect(pt1, pt2, pt3, pt4);
                });
        };
        return std::any_of(p1.points.begin(), p1.points.end(), edge_intersect);
    };
    return check_edges(a, b) || check_edges(b, a);
}

bool arePolygonsSame(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) return false;

    auto points_equal = [](const Point& p1, const Point& p2) {
        return p1 == p2;
    };

    return std::search(
        a.points.begin(), a.points.end(),
        b.points.begin(), b.points.end(),
        points_equal
    ) != a.points.end() ||
    std::search(
        b.points.begin(), b.points.end(),
        a.points.begin(), a.points.end(),
        points_equal
    ) != b.points.end();
}

}
