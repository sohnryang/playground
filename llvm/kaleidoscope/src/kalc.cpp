#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include <iostream>
#include <string>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("LLVM Kaleidoscope tutorial implementation");
  desc.add_options()("help", "produce help message")(
      "emit-ir", po::value<std::string>(),
      "emit LLVM IR")("input,i", po::value<std::string>(), "input file");
  po::variables_map vmap;
  po::store(po::parse_command_line(argc, argv, desc), vmap);
  po::notify(vmap);

  if (vmap.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  if (vmap.count("input")) {
    return 0;
  }
  std::cout << "Running kalc in interpreter mode" << std::endl;
  return 0;
}
