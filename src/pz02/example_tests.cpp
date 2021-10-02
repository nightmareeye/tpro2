#include "iostream"
#include "cstdio"

#include "example.h"

// внимание! define CATCH_CONFIG_MAIN должен быть выше include  "../catch.hpp"
// иначе будет ошибка вида
// .../tests.cpp:23: undefined reference to Catch::StringRef::StringRef(char const*)
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("test1", "[testgroup1]")
{
	REQUIRE(sum(5, 10) == 15);
	REQUIRE(sum(5,5) != 15);
}
TEST_CASE("test2","[testgroup1]")
{
    REQUIRE_THROWS_AS(sum(0,0), std::runtime_error);
    REQUIRE_THROWS(sum(0,0));
    
}
