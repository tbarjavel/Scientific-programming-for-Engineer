#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
/* -------------------------------------------------------------------------- */


std::string printPoint(std::array<double, 3> p) {
    char buffer[256];
    std::snprintf(buffer, sizeof(buffer), "(%.1f, %.1f, %.1f)", p[0], p[1], p[2]);
    std::string s(buffer);
    return s;
}

void addToMap(std::map<std::string, std::array<double, 3>> &map,
              std::string key, std::array<double, 3> p) {
    std::map<std::string, std::array<double, 3>>::iterator it = map.find(key);
    if (it != map.end()) {
        std::cout << "Warning: " << it->first << " already in the map" << std::endl;
    } else {
        std::cout << "Adding " << key << ": " << printPoint(p) << " to map" << std::endl;
        map[key] = p;
    }
}

void printMap(std::map<std::string, std::array<double, 3>> map) {
    for (auto const &e : map) {
        std::cout << e.first << ": " << printPoint(e.second) << std::endl;
    }
}

std::set<std::string> map2Set(std::map<std::string, std::array<double, 3>> map) {
    std::set<std::string> set;
    for (auto const &e : map) {
        set.insert(e.first);
    }
    return set;
}

std::set<std::string> intersectSets(std::set<std::string> set1, std::set<std::string> set2) {
    std::set<std::string> set3;
    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::inserter(set3, set3.begin()));
    return set3;
}

std::map<std::string, std::array<double, 3>> intersectMaps(
    std::map<std::string, std::array<double, 3>> map1,
    std::map<std::string, std::array<double, 3>> map2) {
    std::set<std::string> set = intersectSets(map2Set(map1), map2Set(map2));
    std::map<std::string, std::array<double, 3>> map;
    for (auto const &e : set) {
        map[e] = map1[e];
    }
    return map;
}

int main(int argc, char ** argv){

    using Point = std::array<double, 3>;

    // Map 1 creation
    std::map<std::string, Point> map1;
    map1["earth"] = Point {1., 0., 0.};
    std::cout << "map1 created:" << std::endl;
    printMap(map1);

    // Bad practice: Overwrite
    map1["earth"] = Point {3., 3., 3.};  // --> overwrite!
    std::cout << "map1 after earth overwrite:" << std::endl;
    printMap(map1);
    std::cout << std::endl;

    // Better practice: with key check
    addToMap(map1, "earth", Point {4., 4., 4.});
    printMap(map1);
    std::cout << std::endl;
    addToMap(map1, "pluton", Point {4., 4., 4.});
    printMap(map1);
    std::cout << std::endl;

    // Map 2 creation
    std::map<std::string, Point> map2;
    map2["mercury"] = Point {0.25, 0., 0.};
    map2["earth"] = Point {1.0, 0., 0.};
    map2["jupiter"] = Point {5.0, 0., 0.};
    map2["sun"] = Point {0., 0., 0.};
    std::cout << "map2 created:" << std::endl;
    printMap(map2);
    std::cout << std::endl;

    // Intersection map
    std::map<std::string, Point> map3 = intersectMaps(map1, map2);
    std::cout << "intersection of maps 1 and 2:" << std::endl;
    printMap(map3);
    std::cout << std::endl;

    return EXIT_SUCCESS;
}



