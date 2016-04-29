function(c99 target)
  # CMake doesn't know how to set C99 mode for Intel or Sun.
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
    target_compile_options(${target} PUBLIC -std=c99)
  elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "SunPro")
    target_compile_options(${target} PUBLIC -xc99=all -Xc)
  else()
    if(${CMAKE_MINOR_VERSION} EQUAL 0)
      if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(${target} PUBLIC -std=c99)
      elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${target} PUBLIC -std=c99)
      endif()
    else()
      set_property(TARGET ${target} PROPERTY C_STANDARD 99)
      set_property(TARGET ${target} PROPERTY C_STANDARD_REQUIRED ON)
      set_property(TARGET ${target} PROPERTY C_EXTENSIONS OFF)
    endif()
  endif()
endfunction()

function(lto target)
  if("${CMAKE_BUILD_TYPE}" MATCHES "^Rel")
    if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      if(NOT CMAKE_C_COMPILER_VERSION VERSION_LESS "4.5")
        target_compile_options(${target} PUBLIC -flto)
        set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -flto")
      endif()
    elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
      if(NOT CMAKE_C_COMPILER_VERSION VERSION_LESS "3.2")
        target_compile_options(${target} PUBLIC -flto)
        set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -flto")
      endif()
    elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
      set_property(TARGET ${target} PROPERTY INTERPROCEDURAL_OPTIMIZATION 1)
    elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "SunPro")
      # Solaris Studio requires -xO4 or greater when using IPO, so set
      # here, cross fingers, and hope it overrides any other optimization
      # level (if -xO4 comes after others, it will).
      target_compile_options(${target} PUBLIC -xipo=2 -xO4)
      set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -xipo=2 -xO4")
    endif()
  endif()
endfunction()
