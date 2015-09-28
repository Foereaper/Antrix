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

set(LIBRARY_NAME game)

add_definitions(-DDT_POLYREF64)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ScriptEngine
    ${CMAKE_CURRENT_SOURCE_DIR}/Cluster
    ${CMAKE_SOURCE_DIR}/dep/zlib
    ${CMAKE_SOURCE_DIR}/dep/GameMonkey
    ${CMAKE_SOURCE_DIR}/src/shared
    ${CMAKE_SOURCE_DIR}/src/shared/Auth
    ${CMAKE_SOURCE_DIR}/src/shared/Config
    ${CMAKE_SOURCE_DIR}/src/shared/Database
    ${CMAKE_SOURCE_DIR}/src/shared/Network
    ${CMAKE_SOURCE_DIR}/src/shared/Threading
    ${CMAKE_BINARY_DIR}/src/shared
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ACE_INCLUDE_DIR}
)

#Base file group
file(GLOB SRC_GRP_BASE *.cpp *.h)
source_group("Base Files" FILES ${SRC_GRP_BASE})

#ScriptEngine group
file(GLOB SRC_GRP_SCRIPTENGINE ScriptEngine/*.cpp ScriptEngine/*.h)
source_group("ScriptEngine" FILES ${SRC_GRP_SCRIPTENGINE})

set(LIBRARY_SRCS
    ${SRC_GRP_BASE}
    ${SRC_GRP_SCRIPTENGINE}
)

if(PCH)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SRCS})

if(WIN32)
    target_link_libraries(${LIBRARY_NAME} Dbghelp.lib Ws2_32.lib winmm.lib)
endif()

target_link_libraries(${LIBRARY_NAME} shared GameMonkey)

if(UNIX)
    # Both systems don't have libdl and don't need them
    if (NOT (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "NetBSD"))
        target_link_libraries(${LIBRARY_NAME} dl)
    endif()
endif()

# Generate precompiled header
if(PCH)
    ADD_CXX_PCH(${LIBRARY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.h ${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.cpp)
endif()