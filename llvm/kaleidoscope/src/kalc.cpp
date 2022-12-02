#include <parser.h>

#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_os_ostream.h>

#include <boost/exception/all.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("LLVM Kaleidoscope tutorial implementation");
  desc.add_options()("help", "produce help message")(
      "emit-ir", po::value<std::string>(), "emit LLVM IR")("dump-ast",
                                                           "print ast info");
  po::options_description hidden("Hidden");
  hidden.add_options()("input-file", "input file");
  po::positional_options_description pos;
  pos.add("input-file", 1);
  po::variables_map vmap;
  po::options_description cmdline_options;
  cmdline_options.add(desc).add(hidden);
  try {
    po::store(po::command_line_parser(argc, argv)
                  .options(cmdline_options)
                  .positional(pos)
                  .run(),
              vmap);
  } catch (boost::exception const &err) {
    std::cerr << boost::diagnostic_information(err, true) << std::endl;
    return 1;
  }
  po::notify(vmap);

  if (vmap.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  if (!vmap.count("input-file")) {
    std::cerr << "No input specified" << std::endl;
    return 1;
  }

  std::ifstream infile(vmap["input-file"].as<std::string>());
  std::stringstream buf;
  buf << infile.rdbuf();
  auto parser = Parser(buf.str());
  auto ast = parser.parse_all();

  if (vmap.count("dump-ast"))
    for (auto &root : ast)
      std::cout << root->to_string() << std::endl;
  if (!vmap.count("emit-ir"))
    return 0;

  auto context = std::make_unique<llvm::LLVMContext>();
  auto module = std::make_unique<llvm::Module>("Kaleidoscope", *context);
  auto builder = std::make_unique<llvm::IRBuilder<>>(*context);
  std::map<std::string, llvm::Value *> named_values;
  for (auto &subtree_root : ast)
    subtree_root->codegen(context, module, builder, named_values);
  std::ofstream outfile(vmap["emit-ir"].as<std::string>());
  llvm::raw_os_ostream outstream(outfile);
  module->print(outstream, nullptr);

  return 0;
}
