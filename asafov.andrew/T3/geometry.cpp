#include "geometry.h"
#include <numeric>
#include <cmath>
#include <algorithm>

namespace asafov
{
  bool operator==(const Point& a, const Point& b)
  {
    return (a.x == b.x) && (a.y == b.y);
  }

  double computeArea(const Polygon& poly)
  {
    if (poly.points.size() < 3)
    {
      return 0.0;
    }

    auto area_op = [](const Point& p1, const Point& p2)
    {
      return (p1.x * p2.y) - (p2.x * p1.y);
    };

    const auto& pts = poly.points;
    double sum = std::transform_reduce(
        pts.begin(), pts.end() - 1,
        pts.begin() + 1,
        0.0,
        std::plus<>(),
        area_op
    );

    sum += area_op(pts.back(), pts.front());
    return std::abs(sum) / 2.0;
  }

  bool edgesIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2)
  {
    auto cross = [](const Point& p, const Point& q)
    {
      return p.x * q.y - p.y * q.x;
    };

    Point r = {a2.x - a1.x, a2.y - a1.y};
    Point s = {b2.x - b1.x, b2.y - b1.y};
    Point qp = {b1.x - a1.x, b1.y - a1.y};

    double rxs = cross(r, s);
    if (std::abs(rxs) < 1e-10)
    {
      return false;
    }

    double t = cross(qp, s) / rxs;
    double u = cross(qp, r) / rxs;

    return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
  }

  bool doPolygonsIntersect(const Polygon& a, const Polygon& b)
  {
    auto check_edge = [](const Point& p1, const Point& p2, const Polygon& poly)
    {
      return std::any_of(poly.points.begin(), poly.points.end() - 1,
        [&p1, &p2](const Point& p3)
        {
          const Point& p4 = *(&p3 + 1);
          return edgesIntersect(p1, p2, p3, p4);
        });
    };

    return std::any_of(a.points.begin(), a.points.end() - 1,
        [&b, &check_edge](const Point& p1) {
            const Point& p2 = *(&p1 + 1);
            return check_edge(p1, p2, b);
        }) ||
        std::any_of(b.points.begin(), b.points.end() - 1,
            [&a, &check_edge](const Point& p1) {
                const Point& p2 = *(&p1 + 1);
                return check_edge(p1, p2, a);
            });
  }

  bool arePolygonsSame(const Polygon& a, const Polygon& b)
  {
    if (a.points.size() != b.points.size())
    {
      return false;
    }

    auto rotated = [](const std::vector<Point>& v1, const std::vector<Point>& v2)
    {
      auto it = std::search(v1.begin(), v1.end(), v2.begin(), v2.end());
      return it != v1.end();
    };

    return rotated(a.points, b.points) || rotated(b.points, a.points);
  }
}