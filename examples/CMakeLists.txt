add_executable(example01
  example01.cpp)

add_dependencies(example01 genalg)
target_include_directories(example01 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)
