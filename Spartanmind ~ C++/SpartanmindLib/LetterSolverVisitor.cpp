/**
 * @file LetterSolverVisitor.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterSolverVisitor.h"
#include "InvisibleAnswer.h"

/**
 * Overrides visitor function for visiting letters
 * checks if the letter is already in the solution.
 *
 * @param letter The letter we are visiting.
 */
void LetterSolverVisitor::VisitLetter(Letter* letter)
{
    if (!mAnswer->InSolution(letter))
    {
        mTryToMove = true;
    }
}
