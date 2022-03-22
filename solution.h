#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;
namespace sol267
{

  class Solution
  {
  private:
    static void permutate(
        string &t, int start, string mid, unordered_set<string> &result);

  public:
    static vector<string> find(string s);
  };
}
#endif