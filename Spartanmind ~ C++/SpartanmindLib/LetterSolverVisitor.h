/**
 * @file LetterSolverVisitor.h
 * @author Jackson White
 */
 
#ifndef LETTERSOLVERVISITOR_H
#define LETTERSOLVERVISITOR_H
#include "ItemVisitor.h"

class InvisibleAnswer;

/**
 * letter solver visitor that is derived from item visitor
 * checks if the letter is allowed to be moved
 */
class LetterSolverVisitor : public ItemVisitor{
private:
    /// The answer to the game
    std::shared_ptr<InvisibleAnswer> mAnswer = nullptr;
    /// Can we move the letter?
    bool mTryToMove = false;
public:
    /**
     * Constructor for the letter solver visitor.
     * @param answer The answer to the game.
     */
    LetterSolverVisitor(std::shared_ptr<InvisibleAnswer> answer) : mAnswer(answer){};
    void VisitLetter(Letter* letter) override;

    /**
     * This function returns a bool if we are allowed to move the letter or not.
     * @return bool based on if the game is allowed to move a letter.
     */
    bool MoveLetter() {return mTryToMove;}
};



#endif //LETTERSOLVERVISITOR_H
