
- [目录结构](#目录结构)
- [工程介绍](#工程介绍)
- [如何运行本工程](#如何运行本工程)
- [lib 目录下的静态库是怎么来的](#lib-目录下的静态库是怎么来的)
- [CMakeLists 如何写](#cmakelists-如何写)
- [为什么没有 main 函数程序也可以执行测试](#为什么没有-main-函数程序也可以执行测试)
- [测试方法介绍](#测试方法介绍)
- [为什么使用 Google Test 框架进行测试，自己写 main 函数不可以吗](#为什么使用-google-test-框架进行测试自己写-main-函数不可以吗)
- [如何写测试用例及用例的范式命名法](#如何写测试用例及用例的范式命名法)

## 目录结构
```
CAL_TEST
│  CMakeLists.txt                               // 主 CMakeLists
│  README.md                                    // 说明文档
│
├─build                                         // 进入 build 目录编译构建
├─include                                       // 项目头文件目录
│      calculator.hpp
│
├─lib                                           // Google Test 框架静态库
│  │  libgtest.a
│  │  libgtest_main.a
│  │
│  └─gtest                                      // Google Test 静态库依赖的头文件目录（文件太多此处省略）
│
├─src                                           // 项目源文件目录
│      calculator.cpp
│
└─test                                          // 测试文件路径
        test_by_independently.cpp
        test_by_sameInit.cpp
        test_by_sameLogic.cpp
```

## 工程介绍

类 Calculator 中有三个 public 方法：add、sub 和 div，分别实现加减和除法的功能，并为每个方法配套写了相关的单元测试用例，覆盖了正负数加减和正常除、除数为 0 时的场景。

主要目的是介绍一下如何基于 Google Test 框架，为 src 源码写相应的单元测试用例，并介绍规范的用例命名，以及三种类型的测试策略。

## 如何运行本工程

1. Windows 环境、vscode
2. 下载 vscode: https://code.visualstudio.com/Download
3. 根据 https://code.visualstudio.com/docs/cpp/config-mingw 步骤配置开发环境，配置完成后编译器为 MinGW
4. 进入项目根目录 cal_test/, 创建 build 目录并进入
5. vscode 终端使用命令 `cmake -G "MinGW Makefiles" ..` 为 MinGW 环境生成构建文件 Makefile
```
(base) PS D:\cal_test\build> cmake -G "MinGW Makefiles" ..
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/msys64/ucrt64/bin/cc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/msys64/ucrt64/bin/c++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (4.5s)
-- Generating done (0.0s)
-- Build files have been written to: D:/cal_test/build
```
6. 使用命令 `mingw32-make` 解析和执行上一步骤生成的 Makefile 文件，编译并链接项目
```
(base) PS D:\cal_test\build> mingw32-make
[ 20%] Building CXX object CMakeFiles/calculator_tests.dir/test/test_by_independently.cpp.obj
[ 40%] Building CXX object CMakeFiles/calculator_tests.dir/test/test_by_sameInit.cpp.obj
[ 60%] Building CXX object CMakeFiles/calculator_tests.dir/test/test_by_sameLogic.cpp.obj
[ 80%] Building CXX object CMakeFiles/calculator_tests.dir/src/calculator.cpp.obj
[100%] Linking CXX executable calculator_tests.exe
[100%] Built target calculator_tests
```
7. 使用命令 `.\calculator_tests.exe` 执行当前 build 目录下生成的可执行的测试文件并成功运行
```
(base) PS D:\cal_test\build> .\calculator_tests.exe
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[==========] Running 32 tests from 8 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from CalculatorTestBySameInit
[ RUN      ] CalculatorTestBySameInit.GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum
[       OK ] CalculatorTestBySameInit.GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum (0 ms)
[ RUN      ] CalculatorTestBySameInit.GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference
[       OK ] CalculatorTestBySameInit.GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference (0 ms)
[ RUN      ] CalculatorTestBySameInit.GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] CalculatorTestBySameInit.GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient (177 ms)
[ RUN      ] CalculatorTestBySameInit.GivenDivisorZero_WhenDivCalled_ThenProgramTerminates
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] CalculatorTestBySameInit.GivenDivisorZero_WhenDivCalled_ThenProgramTerminates (146 ms)
[----------] 4 tests from CalculatorTestBySameInit (335 ms total)

[----------] 1 test from AdditionTestByIndependently
[ RUN      ] AdditionTestByIndependently.GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum
[       OK ] AdditionTestByIndependently.GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum (0 ms)
[----------] 1 test from AdditionTestByIndependently (2 ms total)

[----------] 1 test from SubtractTestByIndependently
[ RUN      ] SubtractTestByIndependently.GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference
[       OK ] SubtractTestByIndependently.GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference (0 ms)
[----------] 1 test from SubtractTestByIndependently (2 ms total)

[----------] 2 tests from DivisionTestByIndependently
[ RUN      ] DivisionTestByIndependently.GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient
[       OK ] DivisionTestByIndependently.GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient (0 ms)
[ RUN      ] DivisionTestByIndependently.GivenDivisorZero_WhenDivCalled_ThenProgramTerminates
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionTestByIndependently.GivenDivisorZero_WhenDivCalled_ThenProgramTerminates (145 ms)
[----------] 2 tests from DivisionTestByIndependently (151 ms total)

[----------] 6 tests from AdditionTests/AdditionParamTestBySameLogic
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/0
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/0 (0 ms)
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/1
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/1 (0 ms)
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/2
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/2 (0 ms)
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/3
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/3 (0 ms)
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/4
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/4 (0 ms)
[ RUN      ] AdditionTests/AdditionParamTestBySameLogic.AddTest/5
[       OK ] AdditionTests/AdditionParamTestBySameLogic.AddTest/5 (0 ms)
[----------] 6 tests from AdditionTests/AdditionParamTestBySameLogic (11 ms total)

[----------] 6 tests from SubtractTests/SubtractParamTestBySameLogic
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/0
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/0 (0 ms)
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/1
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/1 (0 ms)
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/2
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/2 (0 ms)
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/3
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/3 (0 ms)
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/4
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/4 (0 ms)
[ RUN      ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/5
[       OK ] SubtractTests/SubtractParamTestBySameLogic.SubtractTest/5 (0 ms)
[----------] 6 tests from SubtractTests/SubtractParamTestBySameLogic (13 ms total)

[----------] 6 tests from DivisionTests/DivisionParamTestBySameLogic
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/0
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/0 (0 ms)
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/1
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/1 (0 ms)
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/2
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/2 (0 ms)
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/3
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/3 (0 ms)
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/4
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/4 (0 ms)
[ RUN      ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/5
[       OK ] DivisionTests/DivisionParamTestBySameLogic.DivisionTest/5 (0 ms)
[----------] 6 tests from DivisionTests/DivisionParamTestBySameLogic (14 ms total)

[----------] 6 tests from DivisionByZeroTests/DivisionByZeroParamTestBySameLogic
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/0
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/0 (146 ms)
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/1
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/1 (144 ms)
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/2
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/2 (147 ms)
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/3
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/3 (146 ms)
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/4
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/4 (149 ms)
[ RUN      ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/5
Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc
[       OK ] DivisionByZeroTests/DivisionByZeroParamTestBySameLogic.DivisionByZeroTest/5 (152 ms)
[----------] 6 tests from DivisionByZeroTests/DivisionByZeroParamTestBySameLogic (901 ms total)

[----------] Global test environment tear-down
[==========] 32 tests from 8 test suites ran. (1452 ms total)
[  PASSED  ] 32 tests.
```

## lib 目录下的静态库是怎么来的
1. GitHub，https://github.com/google/googletest, 右上角 Code->Download ZIP 下载 Google Test 框架源码
2. 打开 Google Test 项目，根目录应该是 googletest-main，mkdir 创建 build 目录并进入
3. vscode 终端使用命令 `cmake -G "MinGW Makefiles" ..` 为 MinGW 环境生成构建文件 Makefila
4. 使用命令 `mingw32-make` 解析和执行上一步骤生成的 Makefile 文件，编译并链接项目
5. 会发现在 build/lib 路径下存在五个 .a 文件，表示将 Google Test 源码编译为了静态库
6. 将 libgtest.a 和 libgtest_main.a 拷贝到需要使用 Google Test 框架进行单元测试的项目目录的 lib/ 下
7. 同时将 googletest-main/googletest/include/gtest 目录及其子目录/文件拷贝到自己项目的 lib/ 下，与两个 .a 文件同级

## CMakeLists 如何写
CMake 很重要，尤其是 CMakeLists 文件要能看懂，写的话建议交给 AI，不必花太多时间学习它，如果想系统学习可以看看罗里吧嗦的官方文档 https://cmake.org/cmake/help/latest/guide/tutorial/index.html 

当前根目录下的 CMakeLists 是 AI 写的，基本上能看懂这个其它的也大差不差都是类似的步骤，关注一下如何将项目可执行文件与 Google Test 静态库链接。

另外进阶版，在大型项目中一般都会分层构建，根目录下一个 CMakeLists，src 和 test 下又有各自的 CMakeLists，方便梳理项目架构，后续工作中看代码的时候可以研究一下。

## 为什么没有 main 函数程序也可以执行测试
因为 Google Test 提供了默认的 main 函数，在下载的 Google Test 源码 googletest/src/gtest_main.cc 文件中。如果用户没有主动提供 main 函数，就会默认使用 Google Test 提供。如果你需要在启动所有测试用例之前做一些事情，可以自己实现一个 main 函数。下面给出官方的 main:
```cpp
GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

## 测试方法介绍
在 test/ 路径下，基于 Google Test 框架，利用三种不同的测试套件对 src/calculator.cpp 进行了测试，分别是：：
    - TEST   最基本的，孤立的测试用例
    - TEST_F 共享状态的测试，支持不同测试用例使用同一初始状态，比如 add、sub 和 测试共享同一个 calculator 对象
    - TEST_P 参数化测试，支持不同参数使用同一测试逻辑，比如共享 add、sub 和 div 测试
具体介绍写在了每个测试文件的开头

## 为什么使用 Google Test 框架进行测试，自己写 main 函数不可以吗
当然可以，但是 Google Test 提供了更方便的工具，比如 EXPECT_EQ，比较两个结果是否一致，EXPECT_TRUE，测试某个方法的调用或结果是否为 TRUE，EXPECT_DEATH，捕获程序中因触发 assert 导致的失败（用于确定某些逻辑是否被覆盖到，比如目前项目中的 div 方法，除数不能为 0，若传入 0 就会触发 assert，正常情况下程序会 abort，但是通过 Google Test 框架，程序可以不中断地继续执行，但会捕获该错误，并打印出错误日志。

比如上面输出结果中的 `Running main() from D:\DownLoad\Compress\googletest-main\googletest-main\googletest\src\gtest_main.cc` 就是因为关于捕获 assert 的程序，Google Test 是另启了一个子进程运行的，当程序如期崩溃之后，主进程就会捕获该错误。

更详细地用法可以参考 Google Test 官方手册：https://google.github.io/googletest/
还有其他的 EXPECT_FAILED、ASSERT_DEATH 等等，用法很多。

## 如何写测试用例及用例的范式命名法
最佳实践是一个场景一个用例，并且用例名称就是围绕当前用例是在测试什么场景的，比如对于测试两个 double 类型做除法的测试用例，输入是两个 double 数据，执行的操作是调用 div 方法，预期结果是返回正确的值，那么用例命名就可以写为：`GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient`，非常清晰。

这是正常做除法的场景，但是当除数为 0 时又是另一个处理，因此可以单独写一个用例，命名为 `GivenDivisorZero_WhenDivCalled_ThenProgramTerminates`，根据用例命名就可以知道输入是除数为 0，执行的操作是调用 div，预期的返回应该是程序嘎掉。相当清晰。

相反，如果你将正常场景的除法和程序异常终止的情况都写在同一个用例中，你不仅需要考虑如何命名该用例，而且多年以后来看你的用例时，你需要肉眼一点点阅读用例的内部逻辑才能知道具体里面干了什么，好的命名可以让你无论过多久回过头来看时，都只需要看一眼用例名就能快速知道当初设计该用例的时候是为了测试什么场景。（这点深有体会，非常好的习惯）
https://x1.344222.cc/api/v1/client/subscribe?token=d33e6dff4910360923fafb953f701466
这还只是 div 一个方法就会遇到这个问题，如果将当前工程的 add，sub 和 div 方法全部写在一个用例中，那实在是相当精彩了。