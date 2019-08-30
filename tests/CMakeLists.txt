SET (MAIN_SRC "../src")

INCLUDE_DIRECTORIES (${MAIN_SRC})



SET (JANETTREE_TESTS "janettree_tests")

SET (JANETTREE_TESTS_HEADERS
    "${MAIN_SRC}/fast_allocator.h"
    "${MAIN_SRC}/janettree.h"
    "${MAIN_SRC}/monom.h"
    "${MAIN_SRC}/monomDRL.h"
    "${MAIN_SRC}/polynom.h"
    "${MAIN_SRC}/triple.h"
    "${MAIN_SRC}/variables.h"
)

SET (JANETTREE_TESTS_SOURCES
    "${MAIN_SRC}/fast_allocator.cpp"
    "${MAIN_SRC}/monom.cpp"
    "${MAIN_SRC}/monomDRL.cpp"
    "${MAIN_SRC}/variables.cpp"
    janettree_tests.cpp
)

ADD_EXECUTABLE (${JANETTREE_TESTS}
    ${JANETTREE_TESTS_HEADERS}
    ${JANETTREE_TESTS_SOURCES}
)



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



SET (POLYNOM_TESTS "polynom_tests")

SET (POLYNOM_TESTS_HEADERS
    "${MAIN_SRC}/fast_allocator.h"
    "${MAIN_SRC}/monom.h"
    "${MAIN_SRC}/monomDRL.h"
    "${MAIN_SRC}/polynom.h"
    "${MAIN_SRC}/variables.h"
)

SET (POLYNOM_TESTS_SOURCES
    "${MAIN_SRC}/fast_allocator.cpp"
    "${MAIN_SRC}/monom.cpp"
    "${MAIN_SRC}/monomDRL.cpp"
    "${MAIN_SRC}/variables.cpp"
    polynom_tests.cpp
)

ADD_EXECUTABLE (${POLYNOM_TESTS}
    ${POLYNOM_TESTS_HEADERS}
    ${POLYNOM_TESTS_SOURCES}
)
