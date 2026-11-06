#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
bool parse_i32(const std::string& text, int& output) {
    if (text.empty()) {
        return false;
    }
    
    std::size_t i = 0;
    bool is_negative = false;
    
    if (text[0] == '+' || text[0] == '-') {
        is_negative = (text[0] == '-');
        i++;
    }

    if (i == text.length()) {
        return false;
    }
    
    long long acc = 0;
    long long limit = is_negative ? 2147483648LL : 2147483647LL;

    for (; i < text.length(); ++i) {
        char c = text[i];
        if (c < '0' || c > '9') {
            return false; 
        }
        
        int digit = c - '0';
        
        if (acc > (limit - digit) / 10) {
            return false; 
        }
        
        acc = acc * 10 + digit;
    }
    
    if (is_negative) {
        output = static_cast<int>(-acc);
    } else {
        output = static_cast<int>(acc);
    }
    
    return true;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
