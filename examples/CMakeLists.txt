add_executable(ex01
  ex01.cpp)

add_dependencies(ex01 genalg)
target_include_directories(ex01 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

add_executable(ex02
  ex02.cpp)

add_dependencies(ex02 genalg)
target_include_directories(ex02 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)
