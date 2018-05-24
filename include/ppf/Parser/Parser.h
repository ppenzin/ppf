//===- Parser.h - PPF Parser Number -------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Parser class for PPF.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_PPF_PARSER_PARSER_H
#define LLVM_PPF_PARSER_PARSER_H

#include "ppf/Parser/Lexer.h"

namespace llvm {
class SourceMgr;
} // end namespace llvm

namespace ppf {

class Parser {
private:
  Lexer TheLexer;
  llvm::SourceMgr &SrcMgr;

public:
  enum RetTy {
    Success,        //< The construct was parsed successfully
    WrongConstruct, //< The construct we wanted to parse wasn't present
    Error           //< There was an error parsing
  };

  Parser(llvm::SourceMgr &SM) : TheLexer(SM), SrcMgr(SM) {}

  /// Parse all program units
  bool ParseProgramUnits();

};

} // end namespace ppf

#endif // LLVM_PPF_PARSER_PARSER_H
