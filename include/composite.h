#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "json.hpp"

namespace composite
{
using JsonNode = nlohmann::json;

class IComponent
{
  public:
    virtual void Parse(const JsonNode &json_node) = 0;
    virtual void Decode() = 0;
};

class Composite : public IComponent
{
  public:
    void Add(const std::shared_ptr<IComponent> &component)
    {
        components_.push_back(component);
    }
    void Parse(const JsonNode &json_node) override
    {
        for (auto &component : components_)
        {
            component->Parse(json_node);
        }
    }
    void Decode() override
    {
        for (auto &component : components_)
        {
            component->Decode();
        }
    }

    std::int32_t id_;
    std::string name_;

  private:
    std::vector<std::shared_ptr<IComponent>> components_;
};

class Leaf : public IComponent
{
  public:
    void Parse(const JsonNode &json_node) {}
    void Decode() {}

    std::int32_t id_;
};

class SignalComponent : public Composite
{
  public:
    void Parse(const JsonNode &json_node)
    {
        std::cout << " ++ " << name_ << std::endl;
        Composite::Parse(json_node);
    }
    void Decode() override
    {
        std::cout << " -- " << name_ << std::endl;
        Composite::Decode();
    }

  private:
    const std::string name_{"Signal"};
};

class PduComponent : public Composite
{
  public:
    void Parse(const JsonNode &json_node)
    {
        std::cout << " ++ " << name_ << std::endl;
        Composite::Parse(json_node);
    }
    void Decode() override
    {
        std::cout << " -- " << name_ << std::endl;
        Composite::Decode();
    }

  private:
    const std::string name_{"Pdu"};
};

class FrameComponent : public Composite
{
  public:
    void Parse(const JsonNode &json_node)
    {
        std::cout << " ++ " << name_ << std::endl;
        Composite::Parse(json_node);
    }
    void Decode() override
    {
        std::cout << " -- " << name_ << std::endl;
        Composite::Decode();
    }

  private:
    const std::string name_{"Frame"};
};

class CodingComponent : public Leaf
{
  public:
    void Parse(const JsonNode &json_node)
    {
        std::cout << " ++ " << name_ << std::endl;
        Leaf::Parse(json_node);
    }
    void Decode() override
    {
        std::cout << " -- " << name_ << std::endl;
        Leaf::Decode();
    }

  private:
    const std::string name_{"Coding"};
};

} // namespace composite

#endif // COMPOSITE_H