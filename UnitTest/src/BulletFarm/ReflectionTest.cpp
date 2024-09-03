#include "utpch.h"

#include "ReflectionTest.h"

/*
 * ReflectionMetadataTest_01
 */
TEST(BulletFarmReflection, ReflectionMetadataTest_01)
{
    const auto& base1 = typeid(BaseClass);
    const auto& base2 = typeid(BaseClass::This);

    EXPECT_EQ(base1.name(), base2.name());
    EXPECT_EQ(BaseClass::StaticType().GetTypeHash(),
              BaseClass::This::StaticType().GetTypeHash());
}

/*
 * ReflectionMetadataTest_02
 */
TEST(BulletFarmReflection, ReflectionMetadataTest_02)
{
    const auto& derivedType = DerivedClass::StaticType();
    const auto& baseType = BaseClass::StaticType();

    EXPECT_EQ(derivedType.GetSuper().GetTypeHash(), baseType.GetTypeHash());
}