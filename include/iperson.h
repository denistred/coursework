#ifndef IPERSON_H
#define IPERSON_H

#include "ibasicinfo.h"
#include "ifamilynode.h"
#include "ivisualinfo.h"

class IPerson : public IBasicInfo, IVisualInfo, IFamilyNode {
public:
    ~IPerson() override = default;
};

#endif //IPERSON_H
