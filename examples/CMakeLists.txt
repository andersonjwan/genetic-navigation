add_executable(ex01
  ex01.cpp)

add_dependencies(ex01 genalg)
target_include_directories(ex01 PRIVATE
  ${PROJECT_SOURCE_DIR}/src/genalg)

if(MATPLOTPLUSPLUS)
  target_link_libraries(ex01 PUBLIC matplot)
endif()
