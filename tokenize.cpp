// Tokenizing a string using stringstream
#include <bits/stdc++.h>

std::vector<std::string> input_handler(std::string &output) {
  // Vector of string to save tokens
  std::vector<std::string> tokens;
  if (!output.empty()) {
    // stringstream class check1
    std::stringstream check1(output);
    std::string intermediate;
    while (getline(check1, intermediate, ' ')) {
      tokens.push_back(intermediate);
    }
  }
  return tokens;
}
