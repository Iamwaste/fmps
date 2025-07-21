aux_source_directory(. SRCS)
add_executable(fmps ${SRCS})

add_dependencies(base jsoncpp)
target_link_libraries(fmps base jsoncpp_static.a)
install(TARGETS fmps RUNTIME DESTINATION sbin)