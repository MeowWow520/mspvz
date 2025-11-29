# Updata Log

## [2025/11/29] 更新编码字符集
为防止出现 [MSVC C4819](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4819?view=msvc-170) 乱码问题。

解决方案： 
在 CMakeLists.txt 中添加以下代码：
```cmake
if (MSVC)
   add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif()
```