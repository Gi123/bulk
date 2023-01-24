cmake_minimum_required(VERSION 3.2)

if ($ENV{GITHUB_RUN_NUMBER})
    project (bulk VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project (bulk VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

file(GLOB bulk_file_cpp
 "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(bulk 
${bulk_file_cpp}
)

set_target_properties(bulk PROPERTIES
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

target_include_directories(bulk
    PRIVATE 
    include
    "${CMAKE_BINARY_DIR}"
)

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)