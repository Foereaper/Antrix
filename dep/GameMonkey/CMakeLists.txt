file(GLOB SRC_GRP_BASE *.cpp *.h)
source_group("Base" FILES ${SRC_GRP_BASE})

set(gm_SRCS
    ${SRC_GRP_BASE}
)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(GameMonkey STATIC
  ${gm_SRCS}
)
