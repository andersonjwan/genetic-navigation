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

add_executable(example03
  example03.cpp)

add_dependencies(example03 genalg)
target_include_directories(example03 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

add_executable(example04
  example04.cpp)

add_dependencies(example04 genalg)
target_include_directories(example04 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

add_executable(example05
  example05.cpp)

add_dependencies(example05 genalg)
target_include_directories(example05 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)
