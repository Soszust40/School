/**
 * @file ContainerHeadButtVisitor.h
 * @author Jackson White
 *
 * Container visitor to handle the headbutt.
 */

#ifndef CONTAIERHEADBUTTVISITOR_H
#define CONTAIERHEADBUTTVISITOR_H
#include "ItemVisitor.h"

/**
 * Visitor that visits containers only. Used for headbutt mechanic.
 */
class ContainerHeadButtVisitor : public ItemVisitor{
private:

public:
    void VisitContainer(Container* container) override;
};

#endif //CONTAIERHEADBUTTVISITOR_H
