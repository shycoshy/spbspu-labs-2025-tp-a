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
          throw std::invalid_argument("No polygons for MEAN");
        }
        double total = 0.0;
        for (const auto& poly: polygons)
        {
          total += computeArea(poly);
        }
        printArea(total / polygons.size());
      }
      else if (cmd == "MAX AREA")
      {
        if (polygons.empty())
        {
          throw std::invalid_argument("No polygons for MAX");
        }
        double max_area = computeArea(polygons[0]);
        for (const auto& poly: polygons)
        {
          double area = computeArea(poly);
          if (area > max_area) max_area = area;
        }
        printArea(max_area);
      }
      else if (cmd == "MAX VERTEXES")
      {
        if (polygons.empty())
        {
          throw std::invalid_argument("No polygons for MAX");
        }
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
      else if (cmd == "MIN AREA")
      {
        if (polygons.empty())
        {
          throw std::invalid_argument("No polygons for MIN");
        }
        double min_area = computeArea(polygons[0]);
        for (const auto& poly: polygons)
        {
          double area = computeArea(poly);
          if (area < min_area) min_area = area;
        }
        printArea(min_area);
      }
      else if (cmd == "MIN VERTEXES")
      {
        if (polygons.empty())
        {
          throw std::invalid_argument("No polygons for MIN");
        }
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
            throw std::invalid_argument("Invalid vertex count");
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
          throw std::invalid_argument("Invalid AREA argument");
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
            throw std::invalid_argument("Invalid vertex count");
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
          throw std::invalid_argument("Invalid COUNT argument");
        }
      }
      else
      {
        throw std::invalid_argument("Unknown command");
      }
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
