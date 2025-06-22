cmake_minimum_required(VERSION 3.10)
project(CalculatorTest)

# 1. 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 指定 Google Test 路径
set(GTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(GTEST_INCLUDE_DIR "${GTEST_DIR}/gtest/include")
set(GTEST_LIBRARY "${GTEST_DIR}/libgtest.a")
set(GTEST_MAIN_LIBRARY "${GTEST_DIR}/libgtest_main.a")

file(GLOB TEST_SOURCES "test/*.cpp")  # Collect all .cpp files in test/

# 3. 添加测试可执行文件
add_executable(calculator_tests
  ${TEST_SOURCES}      # All test files
  src/calculator.cpp
)

# 4. 包含目录
target_include_directories(calculator_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIR}
)

# 5. 统一使用 PRIVATE 关键字的链接命令
target_link_libraries(calculator_tests PRIVATE
  ${GTEST_MAIN_LIBRARY}
  ${GTEST_LIBRARY}
)

# # 6. MinGW 特殊处理（保持风格一致）
# if(MINGW)
#   target_link_options(calculator_tests PRIVATE -Wl,--whole-archive)
#   target_link_libraries(calculator_tests PRIVATE ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
#   target_link_options(calculator_tests PRIVATE -Wl,--no-whole-archive)
# endif()

# # 7. 启用测试
# enable_testing()
# add_test(NAME RunTests COMMAND calculator_tests)