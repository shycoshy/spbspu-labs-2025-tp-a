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
    auto safeStoul = [](const std::string& s) ->size_t
    {
      if (s.empty()) throw std::invalid_argument("Empty string");
      for (char c: s)
      {
        if (!isdigit(c)) throw std::invalid_argument("Not a number");
      }
      unsigned long num = std::stoul(s);
      if (num < 3) throw std::invalid_argument("Vertex count < 3");
      return num;
    };

    try
    {
      if (cmd == "AREA MEAN")
      {
        if (polygons.empty()) throw std::invalid_argument("No polygons");
        double total = 0.0;
        for (const auto& poly: polygons) total += computeArea(poly);
        std::cout << std::fixed << std::setprecision(1) << total / polygons.size() << '\n';
      }
      else if (cmd.find("COUNT ") == 0)
      {
        std::string arg = cmd.substr(6);
        if (arg == "EVEN")
        {
          size_t count = std::count_if(polygons.begin(), polygons.end(),
                                       [](const Polygon& p)
                                       {
                                         return p.points.size() % 2 == 0;
                                       });
          std::cout << count << '\n';
        }
        else if (arg == "ODD")
        {
          size_t count = std::count_if(polygons.begin(), polygons.end(),
                                       [](const Polygon& p)
                                       {
                                         return p.points.size() % 2 != 0;
                                       });
          std::cout << count << '\n';
        }
        else
        {
          size_t num = safeStoul(arg);
          size_t count = std::count_if(polygons.begin(), polygons.end(),
                                       [num](const Polygon& p)
                                       {
                                         return p.points.size() == num;
                                       });
          std::cout << count << '\n';
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
