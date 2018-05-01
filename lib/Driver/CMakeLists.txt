set(LLVM_LINK_COMPONENTS
  Option
  Support
  )

add_ppf_library(ppfDriver
  CmdOptions.cpp
  DEPENDS
  PPFDriverOptions
  )

