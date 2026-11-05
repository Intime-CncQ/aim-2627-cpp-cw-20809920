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

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    for (const auto& edit : edits) {
        // from 为空，to 非空
        if (edit.from.empty() && !edit.to.empty()) {
            if (!labels.empty()) {
                labels += ",";
            }
            labels += edit.to;
        }
        // from 和 to 都为空
        else if (edit.from.empty() && edit.to.empty()) {
            continue;
        }
        // from 非空
        else {
            size_t pos = 0;
            bool found = false;
            
            while ((pos = labels.find(edit.from, pos)) != std::string::npos) {
                bool left_ok = (pos == 0 || labels[pos - 1] == ',');
                bool right_ok = (pos + edit.from.length() == labels.length() || 
                                 labels[pos + edit.from.length()] == ',');
                
                if (left_ok && right_ok) {
                    found = true;
                    break; 
                }
                pos++; 
            }
            
            if (found) {
                if (!edit.to.empty()) {
                    labels.replace(pos, edit.from.length(), edit.to);
                } else {
                    if (labels == edit.from) {
                        labels.clear();
                    } else if (pos + edit.from.length() == labels.length()) {
                        labels.erase(pos - 1); 
                    } else {
                        labels.erase(pos, edit.from.length() + 1);
                    }
                }
            }
        }
    }
    return labels;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
