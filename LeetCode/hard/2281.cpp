#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int totalStrength(vector<int>& strength) {
    const int64_t mod = (int)1e9 + 7;
    size_t size = strength.size();
    vector<int64_t> lpref(size), rpref(size);
    lpref[0] = strength[0];
    for (int i = 1; i < size; i++) {
      lpref[i] = strength[i];
      lpref[i] += lpref[i - 1];
    }
    rpref.back() = strength.back();
    for (int i = (int)size - 2; i >= 0; i--) {
      rpref[i] = strength[i];
      rpref[i] += rpref[i + 1];
    }
    for (int i = 1; i < size; i++) {
      lpref[i] += lpref[i - 1];
      lpref[i] %= mod;
    }
    for (int i = (int)size - 2; i >= 0; i--) {
      rpref[i] += rpref[i + 1];
      rpref[i] %= mod;
    }
    stack<int> s;
    vector<int64_t> lbound(size), rbound(size);
    for (int i = 0; i < size; i++) {
      while (!s.empty() && strength[s.top()] >= strength[i]) {
        s.pop();
      }
      if (s.empty()) {
        lbound[i] = 0;
      } else {
        lbound[i] = s.top() + 1;
      }
      s.push(i);
    }
    stack<int>{}.swap(s);
    for (int i = size - 1; i >= 0; i--) {
      while (!s.empty() && strength[s.top()] > strength[i]) {
        s.pop();
      }
      if (s.empty()) {
        rbound[i] = size - 1;
      } else {
        rbound[i] = s.top() - 1;
      }
      s.push(i);
    }
    int64_t ans = 0;
    for (int i = 0; i < size; i++) {
      auto rseg = (lpref[rbound[i]] - (i ? lpref[i - 1] : 0)) % mod;
      if (i) {
        rseg = (rseg - (rbound[i] - i + 1) * (lpref[i - 1] - (i - 1 ? lpref[i - 2] : 0))) % mod;
      }
      auto lseg = (rpref[lbound[i]] - rpref[i]) % mod;
      lseg = (lseg - (i - lbound[i]) * (rpref[i] - (i + 1 < size ? rpref[i + 1] : 0))) % mod;

      auto tmp = ((rseg * (i - lbound[i] + 1)) % mod) * strength[i] % mod;
      tmp += ((lseg * (rbound[i] - i + 1)) % mod) * strength[i] % mod;
      ans += tmp % mod;
      ans %= mod;
    }
    return (ans + mod) % mod;
  }
};


std::vector<std::string> Split(const std::string& s, const std::string& delimiters) {
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

std::string Strip(const std::string& s, const std::string& chs) { return RStrip(LStrip(s, chs), chs); }

template <typename Func, typename T>
std::vector<typename std::result_of<Func(T)>::type> Map(Func&& f, const std::vector<T>& list) {
  using rT = typename std::result_of<Func(T)>::type;
  std::vector<rT> ret;
  ret.reserve(list.size());
  for (auto& each : list) ret.emplace_back(f(each));
  return ret;
}

int main() {
  std::string str = "[13,13,12,12,13,12]";
  auto ret = Map([](const std::string& s) { return atoi(s.c_str()); }, Split(Strip(str, "[]"), ","));
  std::cout << Solution{}.totalStrength(ret);
}