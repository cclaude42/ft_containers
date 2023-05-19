
INCLUDE_PATH := .. # Path to your headers

SRCS_DIR = srcs

FILES = $(wildcard ${SRCS_DIR}/*.cpp)

CONTAINERS = $(FILES:${SRCS_DIR}/%.cpp=%)

all: ${CONTAINERS}

${CONTAINERS}:
	clang++ -c ${CXXFLAGS} -o /dev/null -I ${INCLUDE_PATH} -D NAMESPACE=ft ${SRCS_DIR}/$@.cpp
