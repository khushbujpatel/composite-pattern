#include <fstream>
#include <gtest/gtest.h>

#define private public
#include "composite.h"

namespace composite
{

class CompositeSpec : public ::testing::Test
{
};

TEST_F(CompositeSpec, FrameComponent)
{
    std::shared_ptr<CodingComponent> coding = std::make_shared<CodingComponent>();
    std::shared_ptr<PduComponent> pdu = std::make_shared<PduComponent>();
    std::shared_ptr<SignalComponent> signals =
        std::make_shared<SignalComponent>();
    std::shared_ptr<FrameComponent> frames = std::make_shared<FrameComponent>();

    signals->Add(coding);
    pdu->Add(signals);
    frames->Add(pdu);

    std::ifstream input_json("test.json");
    JsonNode node;
    input_json >> node;

    frames->Parse(node);
    frames->Decode();
}

} // namespace composite

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}