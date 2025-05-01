/**
 * @file ContainerOpenVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "ContainerOpenVisitor.h"
#include "Container.h"

/**
 * Override function that checks if the container is open.
 *
 * @param container The container we are visiting.
 */
void ContainerOpenVisitor::VisitContainer(Container* container)
{
    mOpen = container->IsOpened();
}
