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

static void ProcessInput(const char *Input, InputArgList &Args);

int
main(int argc_, const char **argv_) {
  const char *Input = nullptr;
  SmallVector<const char *, 256> argv(argv_, argv_ + argc_);

  std::unique_ptr<OptTable> Opts(createCmdOptTable());
  unsigned MissingArgIndex, MissingArgCount;
  ArrayRef<const char*> argvRef = argv;
  InputArgList Args =
      Opts->ParseArgs(argvRef.slice(1), MissingArgIndex, MissingArgCount);

  // Find inputs
  for (auto A : Args) {
    if (A->getOption().getKind() == Option::InputClass) {
      // Can only have one input
      if (Input) {
        std::cerr << "#### Need an error: can only have one input\n";
        return 1;
      }
      Input = A->getValue();
    }
  }

  ProcessInput(Input, Args);

  return 0;
}

/// Compile a P4 file
static void ProcessInput(const char *Input, InputArgList &Args) {
  std::cout << "Work in progress\n";
}
