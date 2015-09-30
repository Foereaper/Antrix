set(LIBNAME "XML")
set(POCO_LIBNAME "Poco${LIBNAME}")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
POCO_HEADERS_AUTO( SRCS ${HDRS_G})

POCO_SOURCES( SRCS expat
    src/xmlparse.cpp
    src/xmlrole.c
    src/xmltok.c
    src/xmltok_impl.c
    src/xmltok_ns.c
)

if(WIN32)
#TODO: Is XML_STATIC only required with Windows? What does it do?
add_definitions(-DXML_STATIC -DXML_NS -DXML_DTD -DHAVE_EXPAT_CONFIG_H)
else()
add_definitions(-DXML_NS -DXML_DTD -DHAVE_EXPAT_CONFIG_H)
endif()

add_library( "${LIBNAME}" ${LIB_MODE} ${SRCS} )
add_library( "${POCO_LIBNAME}" ALIAS "${LIBNAME}")
set_target_properties( "${LIBNAME}"
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME ${POCO_LIBNAME}
    DEFINE_SYMBOL XML_EXPORTS
    )

target_link_libraries( "${LIBNAME}" ${SYSLIBS} Foundation)
target_include_directories( "${LIBNAME}"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

POCO_INSTALL("${LIBNAME}")
POCO_GENERATE_PACKAGE("${LIBNAME}")