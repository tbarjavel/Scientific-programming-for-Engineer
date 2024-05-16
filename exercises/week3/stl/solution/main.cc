#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <array>

/* -------------------------------------------------------------------------- */
using Triplet = std::array<double, 3>;

/* -------------------------------------------------------------------------- */
inline std::ostream & operator <<(std::ostream & stream, Triplet & _this)
{
  stream << _this[0] << " " << _this[1] << " " << _this[2];
  return stream;
}


/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv){


  /* 
     Exercice 1
  */

  if (argc != 2) {
    std::cerr << "missing argument: your name" << std::endl;
    return EXIT_FAILURE;
  }

  std::string myName = "Guillaume";
  std::string argument = std::string(argv[1]);
  if (myName == argument){
    std::cout << "You have a nive name" << std::endl;
  }

  
  /*
    Exercice 2
    
  */

  std::ofstream f("toto.txt");
  f << 1.5 << " " << 1.0 << " " << 2.0 << std::endl;

  std::ifstream is("toto.txt");
  std::string str;
  
  if (is.is_open() == false) {
    std::cerr << "cannot open file toto.txt" << std::endl;
    throw;
  }
  
  getline(is, str);
  std::stringstream sstr(str);

  double x, y, z;
  sstr >> x;
  sstr >> y;
  sstr >> z;

  std::cout << x << " " << y << " " << z << std::endl;

  
  /* 
     Exercice 3
  */

  std::array<double, 3> point = { x, y, z};
  for (auto & p: point) {
    std::cout << p << " ";
  }
  std::cout << "\n";
  
  std::vector<double> vect;
  int npoints = 100;

  for (int i = 0; i < npoints; ++i) {
    double step = 2.*M_PI / npoints;
    vect.push_back(step*i);
  }

  std::cout << vect.size() << std::endl;
  
  std::vector< std::pair<double, double> > sin_vect;
  for (auto & pi: vect) {
    sin_vect.push_back(std::make_pair(pi, sin(pi)) );
  }
  
  std::ofstream of("sin_pi.txt");
  for (auto & pairs: sin_vect){
    of << std::scientific << std::setprecision(20) 
       << pairs.first << " " << pairs.second << std::endl;
  }

  
  

  /* 
     Exercice 5
  */

  std::map<std::string,Triplet> map;
  Triplet origin_coordinates = {0., 0., 0.};

  //Triplet origin_coordinates(0.,0.,0.);
  map["sun"] = origin_coordinates;

  std::map<std::string,Triplet>::iterator end3 = map.end();

  //origin_coordinates.coords[0] = 1.;
  origin_coordinates[0] = 1.;
  std::map<std::string,Triplet>::iterator it3 = map.find("earth");
  if (it3 == end3) map["earth"] = origin_coordinates;

  std::set<std::string> keys;

  std::cout << std::endl << "The complete map content is:" << std::endl;   
  for (auto & planet: map ){
    auto & key    = planet.first;
    auto & values = planet.second;
    std::cout << key << std::endl;
    std::cout << values << std::endl;
    keys.insert(key);
  }

  std::map<std::string,Triplet> map2;

  Triplet mercury_coordinates = {0.25, 0., 0.};
  map2["mercury"] = mercury_coordinates;
  
  Triplet earth_coordinates = {1.25, 0., 0.};
  map2["earth"] = earth_coordinates;
  
  Triplet jupiter_coordinates = {5.25, 0., 0.};
  map2["jupiter"] = jupiter_coordinates;

  Triplet sun_coordinates = {0., 0., 0.};
  map2["sun"] = sun_coordinates;

  std::set<std::string> keys2;
  
  std::cout << std::endl << "The complete map 2 content is:" << std::endl;
  for (auto & planet: map2) {
    auto & key    = planet.first;
    auto & values = planet.second;
    std::cout << key << std::endl;
    std::cout << values << std::endl;
    keys2.insert(key);
  }

  
  std::set<std::string> intersect;
  std::set_intersection( keys.begin(), keys.end(), keys2.begin(), keys2.end(),
			 std::inserter( intersect, intersect.begin() ) );
   
  std::map<std::string, Triplet> map_intersect;
  for(auto & key: intersect) {
    map_intersect[key] = map2[key];   
  }

  std::cout << std::endl << "The complete intersected map content is:" << std::endl;
  for(auto & planet: map_intersect) {
    std::cout << planet.first << std::endl;
    std::cout << planet.second << std::endl;
  }

  

  return EXIT_SUCCESS;
}



