add_executable(example01
  example01.cpp)

add_dependencies(example01 genalg)
target_include_directories(example01 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

add_executable(example02
  example02.cpp)

add_dependencies(example02 genalg)
target_include_directories(example02 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)
