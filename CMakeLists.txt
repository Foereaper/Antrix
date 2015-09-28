# MaNGOS is a full featured server for World of Warcraft, supporting
# the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
#
# Copyright (C) 2005-2015  MaNGOS project <http://getmangos.eu>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

project(Antrix)
set(ANTRIX_VERSION 0.1)

# CMake policies
cmake_minimum_required(VERSION 2.8)
# Until CMake 3.0 is the standard
# And a solution to set_directory_properties is found.
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 OLD)
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${LIBS_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set the correct macro directory path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Define available cmake options below
option(BUILD_TOOLS      "Build the map/vmap/mmap extractors"            OFF)
option(SCRIPT_LIB       "Compile with support for Gmemonkey scripts"    OFF)
option(CLUSTER          "Compile with cluster support"                  OFF)
# Hidden option to enable/disable PCH. DEV ONLY!
set(PCH ON)

# Print CLI helper message
#message("")
#message(
#  "This script builds the MaNGOS server.
#  Options that can be used in order to configure the process:
#   General:
#    CMAKE_INSTALL_PREFIX    Path where the server should be installed to
#    BUILD_TOOLS             Build the map/vmap/mmap extractors
#    CLUSTER                 Compile with cluster support
#   Scripting engines:
#    SCRIPT_LIB              Compile with support for  scripts
#  To set an option simply type -D<OPTION>=<VALUE> after 'cmake <srcs>'.
#  Also, you can specify the generator with -G. see 'cmake --help' for more details
#  For example: cmake .. -DDEBUG=1 -DCMAKE_INSTALL_PREFIX=/opt/mangos"
#  
#  Note: On UNIX systems, CONF_DIR is relative to the bin folder.
#)
#message("")

# Search for and set up the needed packages
set(OPENSSL_EXPECTED_VERSION 1.0.0)

find_package(Platform REQUIRED)
find_package(Git)
find_package(PCHSupport)
find_package(MySQL REQUIRED)
find_package(OpenSSL REQUIRED)

# For Unix systems set the rpath so that libraries are found
set(CMAKE_INSTALL_RPATH "${LIBS_DIR}")
set(CMAKE_INSTALL_NAME_DIR "${LIBS_DIR}")
# Run out of build tree
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

if(UNIX)
    find_package(ZLIB)
endif()

#Include platform/compiler-specific definitions
include(${CMAKE_SOURCE_DIR}/cmake/SetDefinitions.cmake)

# Find core revision
if(GIT_EXECUTABLE)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_REVISION
        RESULT_VARIABLE GIT_RESULT
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(GIT_RESULT)
        set(GIT_REVISION "Git repository not found")
    endif()
else()
    set(GIT_REVISION "Git not found")
endif()

message(STATUS "Antrix Reloaded revision  : ${GIT_REVISION}")

if(SCRIPT_LIB)
    message(STATUS "Script engine         : Yes (default)")
    add_definitions(-DENABLE_SCRIPTS)
else()
    message(STATUS "Script engine         : No")
endif()

if(BUILD_TOOLS)
    message(STATUS "Build tools           : Yes (default)")
else()
    message(STATUS "Build tools           : No")
endif()

if(CLUSTER)
    message(STATUS "Clustering            : Yes")
    add_definitions(-DCLUSTERING)
else()
    message(STATUS "Clustering            : No (default)")
endif()

# Add dependency path
add_subdirectory(dep)

# Add source path
add_subdirectory(src)
