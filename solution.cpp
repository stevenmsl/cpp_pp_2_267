#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>
using namespace sol267;
using namespace std;

/*takeaways
  - use aaaabb as an example
    - you group the same char together as a group and count how many
      of them in each group: a:4, b:2
    - here is the key, you only need to consider the permutations of
      "aab" - use half of the chars from each group
    - why is that?
      - given the permutation aab the corresponding palindrome is aabbaa.
      - once the permutation is determined as aab, the palindrome is determined
        as well as "aabbaa"
  - generate permutations
    - start with ("bba", start=0, i=0)
      - swap t[0] with t[0] so t is still "baa"
      - now we are looking at "aa" ("aa", start=1, i=1)
        - swap t[1] with t[1] so t is still "baa"
      - now we are looking at the very last "a" ("a", start=2, i=2)
        - swap t[2] with t[2] so t is still "baa"
      - now we are looking at the very last "a" ("a", start=2, i=3)
        - i exceeds the size of t, record the the palindrome "baa"-"aab"
      - swap t[2] with t[2] (restore) and then go back to ("aa", start=1, i=1)
      - swap t[1] with t[1] (restore) and we move on to ("aa", start=1, i=2)
        - we skip this as swapping t[1] and t[2] won't generate
          new permutation as they are the same char
    - now we are at ("baa", start=0, i=1)
      - swap t[0] with t[1] to generate new permutation: "aba"
        - so just like steps mentioned above, we will eventually record
          the palindrome "aba"-"aba" per this permutation "aba"
      - fast-forward we are now at ("ba", start=2)
        - swap t[1] with t[2] we generate "aba" -> "aab"
          - and we will eventually record the palindrome "aab-baa"
      - continue until we are done and then restore the permutation
        recursively all the way back to "baa"
    - now we are ready for ("baa", start=0, i=2)
      - swap t[0] with t[2] to generate permutation "aba"
      - this permutation is actually a duplicate from before
      - we don't just shut it down entirely as we might still be
        able to generate new permutations continuing the flow
      - so what do we do now? use unordered_set to avoid
        recording duplicates
*/

void Solution::permutate(
    string &t, int start, string mid, unordered_set<string> &result)
{
  if (start >= t.size())
    /* create palindrome
       - "abc" + mid + "cba"
    */
    result.insert(t + mid + string(t.rbegin(), t.rend()));

  for (auto i = start; i < t.size(); i++)
  {
    /* swapping the same char won't create new permutation */
    if (i != start && t[i] == t[start])
      continue;
    /* create a new permutation
       - i == start is a special case even though
         the swapping has no effect but it
         keeps the recursion going and eventually
         can record the permutation in the result
    */
    swap(t[i], t[start]);
    permutate(t, start + 1, mid, result);
    /*restore it to get ready for the next round */
    swap(t[i], t[start]);
  }
}

vector<string> Solution::find(string s)
{
  /*avoid recording duplicates */
  auto result = unordered_set<string>();
  /*group the same char as a group */
  auto m = unordered_map<char, int>();
  for (auto c : s)
    m[c]++;

  string t = "", mid = "";

  /*
    - compose the first permutation where
      same chars are grouped together.
    - the first permutation will include
      half of the number of chars from
      each group
    - s = aaaabb => t = aab or baa doesn't
      really matter
  */
  for (auto i : m)
  {
    auto &[c, count] = i;
    if (count % 2 == 1)
      mid += c;
    t += string(count / 2, c);
    /*more than one group have odd number of chars
      - you can't form a palindrome
      - aaabbb is one of them
    */
    if (mid.size() > 1)
      return {};
  }
  permutate(t, 0, mid, result);

  return vector<string>(result.begin(), result.end());
}