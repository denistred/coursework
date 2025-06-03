#ifndef IFAMILYNODE_H
#define IFAMILYNODE_H
#include <memory>
#include <vector>

class IFamilyNode {
public:
    virtual ~IFamilyNode() = default;

    virtual void addChild(std::shared_ptr<IFamilyNode> child) = 0;
    virtual void removeChild(const std::string& name) = 0;
    virtual const std::vector<std::shared_ptr<IFamilyNode>>& getChildren() const = 0;
};

#endif //IFAMILYNODE_H
