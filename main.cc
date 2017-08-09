#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

inline double calc_series(const std::vector<std::string> &nums) {
  return std::accumulate(
      nums.begin(), nums.end(), 0.0,
      [](double a, const std::string &s) { return a + atof(s.c_str()); });
}

inline double cal_parallel(const std::vector<std::string> &nums) {
  double val = std::accumulate(
      nums.begin(), nums.end(), 0.0,
      [](double a, const std::string &s) { return a + 1 / (atof(s.c_str())); });
  return 1 / val;
}

int main(int argc, char *argv[]) {

  std::string str(argv[1]);

  if (str.empty()) {
    return EXIT_SUCCESS;
  }

  if (str == "-h" || str == "--help") {
    std::cout << "calculate total resistance in circuits\n"
              << "() - series, [] - parallel circuits\n"
              << "for example: \"([1 2] 3)\"" << std::endl;
    return EXIT_SUCCESS;
  }

  std::stack<std::string> stack;
  const std::size_t n = str.size();
  std::size_t i = 0;

  while (i < n) {
    std::string c(1, str[i]);

    if (c == "[" || c == "(") {
      stack.push(c);
    } else if (c == "]" || c == ")") {
      std::vector<std::string> nums;

      while (!stack.empty()) {
        std::string p = stack.top();
        stack.pop();

        if ((p == "[" && c == "]") || (p == "(" && c == ")")) {
          break;
        }

        nums.push_back(p);
      }

      double val = c == "]" ? cal_parallel(nums) : calc_series(nums);
      stack.push(std::to_string(val));
    } else if (isdigit(c[0])) {
      std::ostringstream digs;
      while (i < n) {
        if (isdigit(str[i]) || str[i] == '.') {
          digs << str[i];
          ++i;
        } else {
          stack.push(digs.str());
          --i;
          break;
        }
      }
    }

    ++i;
  }

  if (stack.size() == 1) {
    std::cout << stack.top() << std::endl;
  } else {
    std::cerr << "cannot parse string: " << str << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
