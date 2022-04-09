add_executable(objective_fn
  objective_fn.cpp)

add_dependencies(objective_fn genalg)
target_include_directories(objective_fn PRIVATE
  ${PROJECT_SOURCE_DIR}/src)

if(MATPLOTPLUSPLUS)
  target_link_libraries(objective_fn PUBLIC matplot)
endif()
