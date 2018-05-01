//===-- main.cpp - LLVM-based P4 compiler ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The P4 (eBPF) Compiler.
//
//===----------------------------------------------------------------------===//

#include "ppf/Basic/LLVM.h"
#include "ppf/Driver/Options.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Process.h"

#include<iostream>

using namespace ppf;
using namespace ppf::driver;
using namespace llvm::opt;

int
main(int argc_, const char **argv_) {
  SmallVector<const char *, 256> argv(argv_, argv_ + argc_);

  std::unique_ptr<OptTable> Opts(createCmdOptTable());
  unsigned MissingArgIndex, MissingArgCount;
  ArrayRef<const char*> argvRef = argv;
  InputArgList Args =
      Opts->ParseArgs(argvRef.slice(1), MissingArgIndex, MissingArgCount);

  std::cout << "Work in progress!" << std::endl;
  return 0;
}
