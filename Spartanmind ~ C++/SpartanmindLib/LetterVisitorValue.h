/**
 * @file LetterVisitorValue.h
 * @author Jackson White
 *
 * Letter visitor used to return the value of letter.
 */

#ifndef LETTERVISITORVALUE_H
#define LETTERVISITORVALUE_H
#include "ItemVisitor.h"

/**
 * Letter visitor derived.
 */
class LetterVisitorValue : public ItemVisitor {

private:
    /// The value of the letter
    int mValue = 0;
public:
    void VisitLetter(Letter* letter) override;

    /**
     * Returns the value of the letter
     *
     * @return The value of the letter
     */
    int LetterValue() { return mValue; }
};

#endif //LETTERVISITORVALUE_H
