//===- Driver.h -------------------------------------------------*- C++ -*-===//
//
//                             The LLVM Linker
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLD_WASM_DRIVER_H
#define LLD_WASM_DRIVER_H

#include "InputFiles.h"
#include "lld/Core/LLVM.h"
#include "llvm/Option/ArgList.h"

namespace lld {
namespace wasm {

// Parses command line options.
class WasmOptTable : public llvm::opt::OptTable {
public:
  WasmOptTable();
  llvm::opt::InputArgList parse(ArrayRef<const char *> Argv);
};

// Create enum with OPT_xxx values for each option in Options.td
enum {
  OPT_INVALID = 0,
#define OPTION(_1, _2, ID, _4, _5, _6, _7, _8, _9, _10, _11, _12) OPT_##ID,
#include "Options.inc"
#undef OPTION
};

class LinkerDriver {
public:
  void link(ArrayRef<const char *> ArgsArr);

private:
  void createFiles(llvm::opt::InputArgList &Args);
  void addFile(StringRef Path);
  void addLibrary(StringRef Name);
  std::vector<InputFile *> Files;
};

extern LinkerDriver *Driver;

} // namespace wasm
} // namespace lld

#endif