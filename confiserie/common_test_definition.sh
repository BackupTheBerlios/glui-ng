runtest() {
	printf "${TEST_SEPARATOR}${1##*/}${TEST_SEPARATOR}\n"
	. "$@"
}
if [ -z "${COMMON_TEST_DEFINITION_SOURCED}" ]; then
	export TEST_SEPARATOR="_________________________________"
	COMMON_TEST_DEFINITION_SOURCED=true
	. ${confiserie}/confiserie.cache.functions.sh
fi

