/*
 * @file ContainerAddLetterVisitor.h
 * @author Jackson White
 *
 * Visits the container and adds a letter to it.
 */
 
#ifndef CONTAINERADDLETTERVISITOR_H
#define CONTAINERADDLETTERVISITOR_H
#include "ItemVisitor.h"

class Item;

/**
 * A visitor that visits a container and adds a letter to it.
 */
class ContainerAddLetterVisitor : public ItemVisitor {
private:
    /// The letter to add
    std::shared_ptr<Item> mLetter = nullptr;
public:

    /**
     * Constructor to the TrayAddLetterVisitor.
     *
     * @param i a pointer to the letter.
     */
    ContainerAddLetterVisitor(std::shared_ptr<Item> i ) : mLetter(i) {};

    void VisitContainer(Container* container) override;
};

#endif //CONTAINERADDLETTERVISITOR_H
