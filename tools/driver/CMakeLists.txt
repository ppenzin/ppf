set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  asmparser
  bitreader
  bitwriter
  codegen
  ipo
  selectiondag
  interpreter
  linker
  )

add_ppf_executable(ppf
  main.cpp
  DEPENDS
  PPFDriverOptions
  )

set_target_properties(ppf PROPERTIES VERSION ${PPF_EXECUTABLE_VERSION})

if(UNIX)
  set(ppf_binary "ppf${CMAKE_EXECUTABLE_SUFFIX}")
else()
  set(ppf_binary "${LLVM_BINARY_DIR}/bin/${CMAKE_CFG_INTDIR}/ppf${CMAKE_EXECUTABLE_SUFFIX}")
endif()

install(TARGETS ppf
  RUNTIME DESTINATION bin)

