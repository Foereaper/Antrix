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

set(LIBRARY_NAME shared)

file(GLOB SRC_GRP_BASE *.cpp *.h)
source_group("Base" FILES ${SRC_GRP_BASE})

file(GLOB SRC_GRP_AUTH Auth/*.cpp Auth/*.h)
source_group("Auth" FILES ${SRC_GRP_AUTH})

file(GLOB SRC_GRP_CONFIG Config/*.cpp Config/*.h)
source_group("Config" FILES ${SRC_GRP_CONFIG})

file(GLOB_RECURSE SRC_GRP_DATABASE Database/*.cpp Database/*.h)
source_group("Database" FILES ${SRC_GRP_DATABASE})

file(GLOB SRC_GRP_THREAD Threading/*.cpp Threading/*.h)
source_group("Threading" FILES ${SRC_GRP_THREAD})

if(WIN32)
    set(SRC_GRP_NETWORK
        Network/Socket.cpp
        Network/SocketMgrWin32.cpp
        Network/SocketOpsWin32.cpp
        Network/SocketWin32.cpp
        Network/ListenSocketWin32.h
        Network/Network.h
        Network/Socket.h
        Network/SocketDefines.h
        Network/SocketMgrWin32.h
        Network/SocketOps.h
    )

    source_group("Network" FILES ${SRC_GRP_NETWORK})
endif()

set(LIBRARY_SRCS
    ${SRC_GRP_BASE}
    ${SRC_GRP_AUTH}
    ${SRC_GRP_CONFIG}
    ${SRC_GRP_DATABASE}
    ${SRC_GRP_THREAD}
    ${SRC_GRP_NETWORK}
    StackWalker.cpp
)

# OS specific files
#if(WIN32)
#    set(LIBRARY_SRCS ${LIBRARY_SRCS} Network/SocketMgrWin32.cpp  Network/SocketOpsWin32.cpp  Network/SocketWin32.cpp StackWalker.cpp)
#else()
#    file(GLOB SRC_GRP_LINUX Linux/*.cpp Linux/*.h)
#    LIST(APPEND LIBRARY_SRCS ${SRC_GRP_LINUX})
#endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Auth
    ${CMAKE_CURRENT_SOURCE_DIR}/Config
    ${CMAKE_CURRENT_SOURCE_DIR}/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/Network
    ${CMAKE_CURRENT_SOURCE_DIR}/Threading
    ${CMAKE_SOURCE_DIR}/dep
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_BINARY_DIR}
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/SystemConfig.h.in" "${CMAKE_CURRENT_BINARY_DIR}/SystemConfig.h")

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SRCS})

if(WIN32)
    target_link_libraries(${LIBRARY_NAME} Dbghelp.lib Ws2_32.lib winmm.lib)
endif()

target_link_libraries(${LIBRARY_NAME} ${MYSQL_LIBRARY})