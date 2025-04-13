#include "datastruct.h"
#include <algorithm>
#include <vector>

int main()
{
  std::vector<asafov::DataStruct> data;
  asafov::DataStruct temp;

  while (std::cin >> temp) data.push_back(temp);
  std::sort(data.begin(), data.end(), asafov::cmpDataStruct);
  for (const auto& ds : data) std::cout << ds << "\n";

  return 0;
}
