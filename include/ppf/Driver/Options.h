//===--- Options.h - Option info & table ------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_PPF_DRIVER_OPTIONS_H
#define LLVM_PPF_DRIVER_OPTIONS_H

#include <memory>

namespace llvm {
namespace opt {
class OptTable;
}
} // namespace llvm

namespace ppf {
namespace driver {

namespace options {
/// Flags specifically for ppf options.  Must not overlap with
/// llvm::opt::DriverFlag.
enum PPFFlags {
  DriverOption = (1 << 4),
  WorkflowOption = (1 << 5),
};

enum ID {
  OPT_INVALID = 0, // This is not an option ID.
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, PARAM,  \
               HELPTEXT, METAVAR, VALUES)                                      \
  OPT_##ID,
#include "ppf/Driver/Options.inc"
  LastOption
#undef OPTION
};
} // namespace options

std::unique_ptr<llvm::opt::OptTable> createCmdOptTable();
} // namespace driver
} // namespace ppf

#endif
