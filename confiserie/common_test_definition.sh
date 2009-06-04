
if [ -z "${COMMON_TEST_DEFINITION_SOURCED}" ]; then
        export TEST_SEPARATOR="_______________________________________________________________________________"
        alias runtest=source
        COMMON_TEST_DEFINITION_SOURCED=true
fi
