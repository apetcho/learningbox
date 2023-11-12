add_library(swzrandom swzrandom.c swzrandom.h)
add_executable(Account account.c)
target_link_libraries(Account PRIVATE swzrandom)
