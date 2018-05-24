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
#include "ppf/Parser/Parser.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/SourceMgr.h"

using namespace llvm;
using namespace llvm::opt;
using namespace ppf;
using namespace ppf::driver;

int
main(int argc_, const char **argv_) {
  const char *Input = nullptr;
  SmallVector<const char *, 256> argv(argv_, argv_ + argc_);

  std::unique_ptr<OptTable> Opts(createCmdOptTable());
  unsigned MissingArgIndex, MissingArgCount;
  ArrayRef<const char*> argvRef = argv;
  InputArgList Args =
      Opts->ParseArgs(argvRef.slice(1), MissingArgIndex, MissingArgCount);

  // Need help message?
  if (Args.hasArg(options::OPT_help)) {
    Opts->PrintHelp(llvm::outs(), "ppf", "P4 compiler for Berkeley Packet Filter", 0, 0, false);
    return 0;
  }

  bool HasErrors = false;

  // Report invalid arguments
  for (auto A : Args.filtered(options::OPT_UNKNOWN)) {
    llvm::errs() << "unknown argument '" << A->getAsString(Args) << "'\n";
    HasErrors = true;
  }

  // Find inputs
  for (auto A : Args) {
    if (A->getOption().getKind() == Option::InputClass) {
      // Can only have one input
      if (Input) {
        // FIXME Diagnostics
        llvm::errs() << "Can only have one input\n";
        return 1;
      }
      Input = A->getValue();
    }
  }

  ErrorOr<std::unique_ptr<MemoryBuffer>> MBOrErr =
      MemoryBuffer::getFileOrSTDIN(Input);
  if (std::error_code EC = MBOrErr.getError()) {
    llvm::errs() << "Could not open input file '" << Input
                 << "': " << EC.message() << "\n";
    HasErrors = true;
  }

  // Don't continue if there were any errors
  if (HasErrors)
    return 1;

  // Grab input memory buffer
  std::unique_ptr<llvm::MemoryBuffer> MB = std::move(MBOrErr.get());

  SourceMgr SrcMgr;
  // TODO SrcMgr.setIncludeDirs(IncludeDirs)

  // Tell SrcMgr about this buffer, which is what Parser will pick up.
  SrcMgr.AddNewSourceBuffer(std::move(MB), llvm::SMLoc());

  Parser P(SrcMgr);
  P.ParseProgramUnits();

  return 0;
}

