#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

class PersonFactory : public AbstractItemFactory {
public:
    Person* createPerson() override;
    Person* createPersonWithId(int id);
    void setId(int id);
    PersonItem* createPersonItem(Person* person) override;
    RelationItem* createRelationItem(PersonItem* from, PersonItem* to) override;
private:
    int personNextId = 0;
};

#endif
