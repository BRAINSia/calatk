project(ModuleDescriptionParserTesting)

cmake_minimum_required(VERSION 2.6)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)
mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)


set(PARSER1TEST_SOURCE Parser1Test )
add_executable(Parser1Test ${PARSER1TEST_SOURCE})
target_link_libraries(Parser1Test ModuleDescriptionParser )

set(ModuleFactoryTest_SOURCE ModuleFactoryTest )
add_executable(ModuleFactoryTest ${ModuleFactoryTest_SOURCE})
target_link_libraries(ModuleFactoryTest ModuleDescriptionParser )

include_directories(
  ${ModuleDescriptionParser_SOURCE_DIR}
  )

set(EXE_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
if(WIN32)
  set(EXE_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
endif(WIN32)

set(TEST_DATA ${ModuleDescriptionParserTesting_SOURCE_DIR}/TestData)
add_test(Parser1Test1 ${LAUNCH_EXE} ${EXE_PREFIX}/Parser1Test ${TEST_DATA}/ParserTest1.xml)

add_test(Parser1Test2 ${LAUNCH_EXE} ${EXE_PREFIX}/Parser1Test ${TEST_DATA}/ParserTest2.xml)

if(Slicer3_BINARY_DIR)
  add_test(ModuleFactoryTest ${LAUNCH_EXE} ${EXE_PREFIX}/ModuleFactoryTest ${Slicer3_BINARY_DIR}/${Slicer3_INSTALL_PLUGINS_BIN_DIR}/)
endif(Slicer3_BINARY_DIR)

