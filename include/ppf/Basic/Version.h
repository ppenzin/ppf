//===- Version.h - PPF Version Number -------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines version macros and version-related utility functions
/// for PPF.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_PPF_BASIC_VERSION_H
#define LLVM_PPF_BASIC_VERSION_H

#include "ppf/Basic/Version.inc"
#include "llvm/ADT/StringRef.h"

namespace ppf {
/// \brief Retrieves the repository path (e.g., Subversion path) that
/// identifies the particular PPF branch, tag, or trunk from which this
/// PPF was built.
std::string getPPFRepositoryPath();

/// \brief Retrieves the repository path from which LLVM was built.
///
/// This supports LLVM residing in a separate repository from ppf.
std::string getLLVMRepositoryPath();

/// \brief Retrieves the repository revision number (or identifer) from which
/// this PPF was built.
std::string getPPFRevision();

/// \brief Retrieves the repository revision number (or identifer) from which
/// LLVM was built.
///
/// If PPF and LLVM are in the same repository, this returns the same
/// string as getPPFRevision.
std::string getLLVMRevision();

/// \brief Retrieves the full repository version that is an amalgamation of
/// the information in getPPFRepositoryPath() and getPPFRevision().
std::string getPPFFullRepositoryVersion();

/// \brief Retrieves a string representing the complete ppf version,
/// which includes the ppf version number, the repository version,
/// and the vendor tag.
std::string getPPFFullVersion();

/// \brief Like getPPFFullVersion(), but with a custom tool name.
std::string getPPFToolFullVersion(llvm::StringRef ToolName);

/// \brief Retrieves a string representing the complete ppf version suitable
/// for use in the CPP __VERSION__ macro, which includes the ppf version
/// number, the repository version, and the vendor tag.
std::string getPPFFullCPPVersion();
} // namespace ppf

#endif // LLVM_PPF_BASIC_VERSION_H
