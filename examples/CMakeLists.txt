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

add_executable(ex03
  ex03.cpp)

add_dependencies(ex03 genalg)
target_include_directories(ex03 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

add_executable(ex04
  ex04.cpp)

add_dependencies(ex04 genalg)
target_include_directories(ex04 PRIVATE
  ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(ex04 PUBLIC matplot)
