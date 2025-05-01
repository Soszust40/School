/**
 * @file GivenValueVisitior.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "GivenValueVisitior.h"
#include "Given.h"

/**
 * Visit the given and get its value.
 *
 * @param given The given object.
 */
void GivenValueVisitior::VisitGiven(Given * given)
{
    mValue = given->GetValue();
}
