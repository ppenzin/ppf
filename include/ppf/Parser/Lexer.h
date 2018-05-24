//===- Lexer.h - PPF Lexer class --------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Lexer class for PPF.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_PPF_PARSER_LEXER_H
#define LLVM_PPF_PARSER_LEXER_H

namespace llvm {
class SourceMgr;
} // end namespace llvm

namespace ppf {

class Lexer {
private:
  llvm::SourceMgr &SrcMgr;

public:
  Lexer(llvm::SourceMgr &SM) : SrcMgr(SM) {};
};

} // end namespace ppf

#endif // LLVM_PPF_PARSER_LEXER_H
