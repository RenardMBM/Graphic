#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

TEST(IdentifierTests, IdentifierStandardHex) {
    HexIdentifier hexId, hexId2;

    std::string id1 = hexId.get_value();
    std::string id2 = hexId2.get_value();


    ASSERT_NE(id1, id2);
}