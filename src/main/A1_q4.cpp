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

// Assessment 01 Q4; see 题面.pdf.
namespace aim::q4 {
struct CommandResult { long long value; int accepted; int rejected; };

// BEGIN IMPLEMENTATION
CommandResult execute(const std::vector<std::string>& lines) {
    CommandResult res = {0, 0, 0};
    
    for (const std::string& line : lines) {
        std::istringstream iss(line);
        std::string cmd;
        
        // 尝试读取命令名
        if (!(iss >> cmd)) {
            res.rejected++;
            continue;
        }
        
        // 处理 ADD 和 SET
        if (cmd == "ADD" || cmd == "SET") {
            long long x;
            if (!(iss >> x)) {
                res.rejected++;
                continue;
            }
            
            if (x < -1000000 || x > 1000000) {
                res.rejected++;
                continue;
            }
            
            std::string extra;
            if (iss >> extra) {
                res.rejected++;
                continue;
            }
            
            long long candidate = (cmd == "ADD") ? (res.value + x) : x;
            
            if (candidate < -1000000 || candidate > 1000000) {
                res.rejected++;
            } else {
                res.value = candidate;
                res.accepted++;
            }
        }
        // 处理 RESET
        else if (cmd == "RESET") {
            std::string extra;
            if (iss >> extra) {
                res.rejected++;
            } else {
                res.value = 0;
                res.accepted++;
            }
        }
        // 未知命令
        else {
            res.rejected++;
        }
    }
    
    return res;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q4;
int main() {
    try {
        { aim::q4::CommandResult r=execute({"ADD 5","SET 8 x","RESET","ADD -2"}); CHECK(r.value==-2 && r.accepted==3 && r.rejected==1); }
        { aim::q4::CommandResult r=execute({}); CHECK(r.value==0 && r.accepted==0 && r.rejected==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
