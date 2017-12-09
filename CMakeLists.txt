cmake_minimum_required(VERSION 3.9)
project(mspoof)

include(ExternalProject)

# ARGSX LIBRARY
set(DEP_ARGSX "argsx")
set(LIB_ARGSX "ArgsX.a")
# SPARK LIBRARY
set(DEP_SPARK "spark")
set(LIB_SPARK "Spark.a")

# ARGSX LIBRARY
ExternalProject_Add(${DEP_ARGSX} PREFIX "${PROJECT_SOURCE_DIR}/lib/argsx" SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/argsx" INSTALL_COMMAND "")
ExternalProject_Get_Property(${DEP_ARGSX} source_dir)
include_directories("${source_dir}/include/")
link_directories("${source_dir}/bin/")

# SPARK LIBRARY
ExternalProject_Add(${DEP_SPARK} PREFIX "${PROJECT_SOURCE_DIR}/lib/spark/" SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/spark/" INSTALL_COMMAND "")
ExternalProject_Get_Property(${DEP_SPARK} source_dir)
include_directories("${source_dir}/include/")
link_directories("${source_dir}/bin/")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

add_executable(mspoof src/mspoof.c)
add_dependencies(mspoof ${DEP_ARGSX})
add_dependencies(mspoof ${DEP_SPARK})
target_link_libraries(mspoof ${LIB_ARGSX})
target_link_libraries(mspoof ${LIB_SPARK})
