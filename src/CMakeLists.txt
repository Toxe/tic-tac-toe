add_subdirectory(tic_tac_toe)

add_executable(tic_tac_toe main.cpp)

set_target_properties(tic_tac_toe PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(tic_tac_toe PUBLIC cxx_std_20)
target_compile_options(tic_tac_toe PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(tic_tac_toe PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(tic_tac_toe PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tic_tac_toe)
