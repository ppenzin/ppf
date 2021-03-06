//===--- DriverOptions.cpp - Driver Options Table -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ppf/Driver/Options.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Option/Option.h"
#include <cassert>

using namespace ppf::driver;
using namespace ppf::driver::options;
using namespace llvm::opt;

#define PREFIX(NAME, VALUE) static const char *const NAME[] = VALUE;
#include "ppf/Driver/Options.inc"
#undef PREFIX

static const OptTable::Info InfoTable[] = {
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, PARAM,  \
               HELPTEXT, METAVAR, VALUES)                                      \
  {PREFIX, NAME,  HELPTEXT,    METAVAR,     OPT_##ID,  Option::KIND##Class,    \
   PARAM,  FLAGS, OPT_##GROUP, OPT_##ALIAS, ALIASARGS, VALUES},
#include "ppf/Driver/Options.inc"
#undef OPTION
};

namespace {

class CmdOptTable : public OptTable {
public:
  CmdOptTable()
    : OptTable(InfoTable) {}
};

}

std::unique_ptr<OptTable> ppf::driver::createCmdOptTable() {
  auto Result = llvm::make_unique<CmdOptTable>();
  // Options.inc is included in DriverOptions.cpp, and calls OptTable's
  // addValues function.
  // Opt is a variable used in the code fragment in Options.inc.
  OptTable &Opt = *Result;
#define OPTTABLE_ARG_INIT
#include "ppf/Driver/Options.inc"
#undef OPTTABLE_ARG_INIT
  return std::move(Result);
}

