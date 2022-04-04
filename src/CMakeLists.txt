add_library(genalg INTERFACE)

target_include_directories(genalg INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(genalg INTERFACE /W4)
else()
    target_compile_options(genalg INTERFACE -Werror -Wpedantic -Wall -Wextra)
endif()
