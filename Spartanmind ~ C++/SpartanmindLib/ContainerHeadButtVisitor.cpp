/**
 * @file ContainerHeadButtVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "ContainerHeadButtVisitor.h"
#include "Container.h"

/**
 * Override visitContainer function that calls handle headbutt on the container item.
 * @param container The container we are visiting.
 */
void ContainerHeadButtVisitor::VisitContainer(Container* container)
{
    container->HandleHeadbutt();
}
