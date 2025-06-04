#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

class PersonFactory : public AbstractItemFactory {
public:
    IPerson* createPerson() override;
    IPerson* createPersonWithId(int id);
    void setId(int id);
    PersonItem* createPersonItem(IPerson* person) override;
    RelationItem* createRelationItem(PersonItem* from, PersonItem* to) override;
private:
    int personNextId = 0;
};

#endif
