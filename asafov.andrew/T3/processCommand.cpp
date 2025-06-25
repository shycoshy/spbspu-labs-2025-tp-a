#include "functions.h"
#include "geometry.h"
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <iostream>

namespace asafov
{
  void processCommand(const std::vector< Polygon >& polygons, const std::string& cmd)
  {
    auto printArea = [](double area)
    {
      std::cout << std::fixed << std::setprecision(1) << area << '\n';
    };

    auto printCount = [](size_t count)
    {
      std::cout << count << '\n';
    };

    try
    {
      if (cmd == "AREA MEAN")
      {
        if (polygons.empty())
        {
          printArea(0.0);
        }
        else
        {
          double total = 0.0;
          for (const auto& poly: polygons)
          {
            total += computeArea(poly);
          }
          printArea(total / polygons.size());
        }
      }
      else if (cmd == "AREA EVEN")
      {
        double sum = 0.0;
        for (const auto& poly: polygons)
        {
          if (poly.points.size() % 2 == 0)
          {
            sum += computeArea(poly);
          }
        }
        printArea(sum);
      }
      else if (cmd == "AREA ODD")
      {
        double sum = 0.0;
        for (const auto& poly: polygons)
        {
          if (poly.points.size() % 2 != 0)
          {
            sum += computeArea(poly);
          }
        }
        printArea(sum);
      }
      else if (cmd.find("AREA ") == 0)
      {
        std::string arg = cmd.substr(5);
        try
        {
          size_t num = std::stoul(arg);
          if (num < 3)
          {
            std::cout << "<INVALID COMMAND>\n";
            return;
          }
          double sum = 0.0;
          for (const auto& poly: polygons)
          {
            if (poly.points.size() == num)
            {
              sum += computeArea(poly);
            }
          }
          printArea(sum);
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (cmd == "COUNT EVEN")
      {
        size_t count = 0;
        for (const auto& poly: polygons)
        {
          if (poly.points.size() % 2 == 0)
          {
            count++;
          }
        }
        printCount(count);
      }
      else if (cmd == "COUNT ODD")
      {
        size_t count = 0;
        for (const auto& poly: polygons)
        {
          if (poly.points.size() % 2 != 0)
          {
            count++;
          }
        }
        printCount(count);
      }
      else if (cmd.find("COUNT ") == 0)
      {
        std::string arg = cmd.substr(6);
        try
        {
          size_t num = std::stoul(arg);
          if (num < 3)
          {
            std::cout << "<INVALID COMMAND>\n";
            return;
          }
          size_t count = 0;
          for (const auto& poly: polygons)
          {
            if (poly.points.size() == num)
            {
              count++;
            }
          }
          printCount(count);
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (cmd == "MAX AREA")
      {
        if (polygons.empty())
        {
          printArea(0.0);
        }
        else
        {
          double max_area = computeArea(polygons[0]);
          for (const auto& poly: polygons)
          {
            double area = computeArea(poly);
            if (area > max_area) max_area = area;
          }
          printArea(max_area);
        }
      }
      else if (cmd == "MAX VERTEXES")
      {
        if (polygons.empty())
        {
          printCount(0);
        }
        else
        {
          size_t max_vert = polygons[0].points.size();
          for (const auto& poly: polygons)
          {
            if (poly.points.size() > max_vert)
            {
              max_vert = poly.points.size();
            }
          }
          printCount(max_vert);
        }
      }
      else if (cmd == "MIN AREA")
      {
        if (polygons.empty())
        {
          printArea(0.0);
        }
        else
        {
          double min_area = computeArea(polygons[0]);
          for (const auto& poly: polygons)
          {
            double area = computeArea(poly);
            if (area < min_area) min_area = area;
          }
          printArea(min_area);
        }
      }
      else if (cmd == "MIN VERTEXES")
      {
        if (polygons.empty())
        {
          printCount(0);
        }
        else
        {
          size_t min_vert = polygons[0].points.size();
          for (const auto& poly: polygons)
          {
            if (poly.points.size() < min_vert)
            {
              min_vert = poly.points.size();
            }
          }
          printCount(min_vert);
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
