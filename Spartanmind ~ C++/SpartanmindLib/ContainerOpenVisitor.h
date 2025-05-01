/**
 * @file ContainerOpenVisitor.h
 * @author Jackson White
 *
 * Visitor for the container classs.
 */
 
#ifndef CONTAINEROPENVISITOR_H
#define CONTAINEROPENVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor for the container class. returns if the container is open.
 */
class ContainerOpenVisitor : public ItemVisitor {
private:
    /// if the container is not open yet, initially it is closed.
    bool mOpen = true;
public:
    void VisitContainer(Container* container) override;

    /**
     * Function that returns if the container is open.
     * @return Returns if the container is open or not.
     */
    bool IsOpen() {return mOpen;}
};

#endif //CONTAINEROPENVISITOR_H
