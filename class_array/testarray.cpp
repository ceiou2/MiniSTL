#include<gtest/gtest.h>
#include"MiniArray.h"

TEST(TestAccess,at){
    array<int,3> arr{1, 2, 3};

}

int main(int argc,char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
