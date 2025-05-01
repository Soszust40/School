/**
 * @file GivenValueVisitior.h
 * @author Jackson White
 *
 * Visitor for the givens class
 */
 
#ifndef GIVENVALUEVISITIOR_H
#define GIVENVALUEVISITIOR_H

#include "ItemVisitor.h"

/**
 * Visit the givens class and allows you to return the value.
 */
class GivenValueVisitior : public ItemVisitor {
private:
    /// Value of the given
    double mValue = -99;
public:
    void VisitGiven(Given* given) override;

    /**
     * Return the value of the given.
     *
     * @return Value of the given.
     */
    double GetValue() const { return mValue; }
};

#endif //GIVENVALUEVISITIOR_H
