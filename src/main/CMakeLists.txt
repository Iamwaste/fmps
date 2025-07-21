aux_source_directory(. SRCS)
add_executable(fmps ${SRCS})

install(TARGETS fmps RUNTIME DESTINATION sbin)