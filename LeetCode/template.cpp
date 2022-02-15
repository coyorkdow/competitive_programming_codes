#include <bits/stdc++.h>

std::vector<std::string> Split(const std::string& s,
                               const std::string& delimiters) {
  std::vector<std::string> tokens;
  auto lastPos = s.find_first_not_of(delimiters, 0);
  auto pos = s.find_first_of(delimiters, lastPos);
  while (std::string::npos != pos || std::string::npos != lastPos) {
    tokens.emplace_back(s.substr(lastPos, pos - lastPos));
    lastPos = s.find_first_not_of(delimiters, pos);
    pos = s.find_first_of(delimiters, lastPos);
  }
  return tokens;
}

std::string LStrip(const std::string& s, const std::string& chs) {
  std::string::size_type pos = 0;
  while (pos < s.size() && chs.find(s[pos]) != std::string::npos) pos++;
  return s.substr(pos);
}

std::string RStrip(const std::string& s, const std::string& chs) {
  std::string::size_type pos = s.size();
  if (pos == 0) return "";
  pos--;
  while (pos && chs.find(s[pos]) != std::string::npos) pos--;
  return s.substr(0, pos + 1);
}

std::string Strip(const std::string& s, const std::string& chs) {
  return RStrip(LStrip(s, chs), chs);
}

template <typename Func, typename T>
std::vector<typename std::result_of<Func(T)>::type> Map(
    Func&& f, const std::vector<T>& list) {
  using rT = typename std::result_of<Func(T)>::type;
  std::vector<rT> ret;
  ret.reserve(list.size());
  for (auto& each : list) ret.emplace_back(f(each));
  return ret;
}

int main() {
  std::string str = "[1, 2, 3, 654, 23, -17]";
  auto ret = Map([](const std::string& s) { return atoi(s.c_str()); },
                 Split(Strip(str, "[]"), ","));
  for (auto i : ret) std::cout << i << ' ';
}