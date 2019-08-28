SET (MAIN_SRC "../src")

INCLUDE_DIRECTORIES (${MAIN_SRC})


SET (MONOM_TESTS "monom_tests")

SET (MONOM_TESTS_HEADERS
    "${MAIN_SRC}/fast_allocator.h"
    "${MAIN_SRC}/monom.h"
    "${MAIN_SRC}/monomDL.h"
    "${MAIN_SRC}/monomDRL.h"
    "${MAIN_SRC}/monomLex.h"
    "${MAIN_SRC}/variables.h"
)

SET (MONOM_TESTS_SOURCES
    "${MAIN_SRC}/fast_allocator.cpp"
    "${MAIN_SRC}/monom.cpp"
    "${MAIN_SRC}/monomDL.cpp"
    "${MAIN_SRC}/monomDRL.cpp"
    "${MAIN_SRC}/monomLex.cpp"
    "${MAIN_SRC}/variables.cpp"
    monom_tests.cpp
)

ADD_EXECUTABLE (${MONOM_TESTS}
    ${MONOM_TESTS_HEADERS}
    ${MONOM_TESTS_SOURCES}
)
