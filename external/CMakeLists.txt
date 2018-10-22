
  #编译gtest
  set(gtest_force_shared_crt ON)
  set(BUILD_GMOCK OFF)
  set(BUILD_GTEST ON)
  add_subdirectory(googletest)

  set(GTEST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest)


#暴露参数给父作用域
set(CompilerFlags  GTEST_INCLUDE_DIRS)
foreach(CompilerFlag ${CompilerFlags})
  set(${CompilerFlag} "${${CompilerFlag}}" PARENT_SCOPE)
endforeach()