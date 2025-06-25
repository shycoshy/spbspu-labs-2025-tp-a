#include "geometry.h"
#include "functions.h"
#include <string>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace asafov
{
  void processCommand(const std::vector< Polygon >& polygons, const std::string& cmd)
  {
    auto parseUInt = [](const std::string& s) ->size_t
    {
      if (s.empty()) throw std::invalid_argument("Empty string");
      for (char c: s)
      {
        if (!isdigit(c)) throw std::invalid_argument("Not a number");
      }
      return std::stoul(s);
    };

    auto printArea = [](double area)
    {
      std::cout << std::fixed << std::setprecision(1) << area << '\n';
    };

    try
    {
      if (cmd == "AREA MEAN")
      {
        if (polygons.empty()) throw std::invalid_argument("No polygons");
        double total = 0.0;
        for (const auto& poly: polygons)
        {
          total += computeArea(poly);
        }
        printArea(total / polygons.size());
      }
      else if (cmd.find("AREA ") == 0)
      {
        std::string arg = cmd.substr(5);
        if (arg == "EVEN")
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
        else if (arg == "ODD")
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
        else
        {
          size_t num = parseUInt(arg);
          if (num < 3) throw std::invalid_argument("Invalid vertex count");
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
      }
      else if (cmd.find("COUNT ") == 0)
      {
        std::string arg = cmd.substr(6);
        if (arg == "EVEN")
        {
          size_t count = 0;
          for (const auto& poly: polygons)
          {
            if (poly.points.size() % 2 == 0) count++;
          }
          std::cout << count << '\n';
        }
        else if (arg == "ODD")
        {
          size_t count = 0;
          for (const auto& poly: polygons)
          {
            if (poly.points.size() % 2 != 0) count++;
          }
          std::cout << count << '\n';
        }
        else
        {
          size_t num = parseUInt(arg);
          if (num < 3) throw std::invalid_argument("Invalid vertex count");
          size_t count = 0;
          for (const auto& poly: polygons)
          {
            if (poly.points.size() == num) count++;
          }
          std::cout << count << '\n';
        }
      }
      else if (cmd.find("MAX ") == 0)
      {
        std::string arg = cmd.substr(4);
        if (polygons.empty()) throw std::invalid_argument("No polygons");
        if (arg == "AREA")
        {
          double max_area = computeArea(polygons[0]);
          for (const auto& poly: polygons)
          {
            double area = computeArea(poly);
            if (area > max_area) max_area = area;
          }
          printArea(max_area);
        }
        else if (arg == "VERTEXES")
        {
          size_t max_vert = polygons[0].points.size();
          for (const auto& poly: polygons)
          {
            if (poly.points.size() > max_vert)
            {
              max_vert = poly.points.size();
            }
          }
          std::cout << max_vert << '\n';
        }
        else
        {
          throw std::invalid_argument("Invalid MAX argument");
        }
      }
      else if (cmd.find("MIN ") == 0)
      {
        std::string arg = cmd.substr(4);
        if (polygons.empty()) throw std::invalid_argument("No polygons");
        if (arg == "AREA")
        {
          double min_area = computeArea(polygons[0]);
          for (const auto& poly: polygons)
          {
            double area = computeArea(poly);
            if (area < min_area) min_area = area;
          }
          printArea(min_area);
        }
        else if (arg == "VERTEXES")
        {
          size_t min_vert = polygons[0].points.size();
          for (const auto& poly: polygons)
          {
            if (poly.points.size() < min_vert)
            {
              min_vert = poly.points.size();
            }
          }
          std::cout << min_vert << '\n';
        }
        else
        {
          throw std::invalid_argument("Invalid MIN argument");
        }
      }
      else
      {
        throw std::invalid_argument("Unknown command");
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
