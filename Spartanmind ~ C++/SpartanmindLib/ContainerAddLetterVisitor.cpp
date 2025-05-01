/**
 * @file ContainerAddLetterVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "ContainerAddLetterVisitor.h"
#include "Container.h"

/**
 * Visit the container and add the letter to it.
 * @param container The container we are visiting.
 */
void ContainerAddLetterVisitor::VisitContainer(Container* container)
{
    container->AddLetter(mLetter);
}