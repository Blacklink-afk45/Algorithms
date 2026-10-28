include_directories(..)

add_executable(testarray array.cpp)
target_link_libraries(testarray LibraryCPP)

add_executable(testlist list.cpp)
target_link_libraries(testlist LibraryCPP)

add_executable(testqueue queue.cpp)
target_link_libraries(testqueue LibraryCPP)

add_executable(teststack stack.cpp)
target_link_libraries(teststack LibraryCPP)

add_executable(testvector vector.cpp)
target_link_libraries(testvector LibraryCPP)
