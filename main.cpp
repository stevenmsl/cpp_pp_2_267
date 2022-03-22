#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol267;

/* Example 1:
 Given s = "aabb", return ["abba", "baab"].
*/
tuple<string, vector<string>>
testFixture1()
{
  auto pp = vector<string>{"abba", "baab"};
  return make_tuple("aabb", pp);
}

/* Example 2:
 Given s = "abc", return [].
*/
tuple<string, vector<string>>
testFixture2()
{
  auto pp = vector<string>();
  return make_tuple("abc", pp);
}

/* Example 3:
 Given s = "aaaabb", return ["aabbaa", "abaaba", "baaaab"].
*/
tuple<string, vector<string>>
testFixture3()
{
  auto pp = vector<string>{"aabbaa", "abaaba", "baaaab"};
  return make_tuple("aaaabb", pp);
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << Util::toString(get<1>(f)) << endl;
  auto result = Solution::find(get<0>(f));
  cout << "result: " << Util::toString(result) << endl;
}
void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see " << Util::toString(get<1>(f)) << endl;
  auto result = Solution::find(get<0>(f));
  cout << "result: " << Util::toString(result) << endl;
}
void test3()
{
  auto f = testFixture3();
  cout << "Test 3 - exepct to see " << Util::toString(get<1>(f)) << endl;
  auto result = Solution::find(get<0>(f));
  cout << "result: " << Util::toString(result) << endl;
}

main()
{
  test1();
  test2();
  test3();
  return 0;
}