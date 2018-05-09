//===--- Options.td - Options for ppf ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines the options accepted by ppf.
//
//===----------------------------------------------------------------------===//

// Include the common option parsing interfaces.
include "llvm/Option/OptParser.td"

/////////
// Flags

// WorkflowOption - Options affecting compiler's workflow
def WorkflowOption : OptionFlag;

// DriverOption - Command line parsing options and utility output
def DriverOption : OptionFlag;

// A short name to show in documentation. The name will be interpreted as rST.
class DocName<string name> { string DocName = name; }

// A brief description to show in documentation, interpreted as rST.
class DocBrief<code descr> { code DocBrief = descr; }

/////////
// Groups

def Action_Group : OptionGroup<"<action group>">, DocName<"Actions">,
                   DocBrief<[{The action to perform on the input.}]>;

def Help_Group : OptionGroup<"<help group>">, DocName<"Help">,
                 DocBrief<[{Help output.}]>;

/////////
// Options

def fsyntax_only : Flag<["-"], "fsyntax-only">,
  Flags<[WorkflowOption]>, Group<Action_Group>,
  HelpText<"Stop after checking syntax">;

def help : Flag<["-", "--"], "help">,
  Flags<[DriverOption, WorkflowOption]>, Group<Help_Group>,
  HelpText<"Print help message and exit">; 

