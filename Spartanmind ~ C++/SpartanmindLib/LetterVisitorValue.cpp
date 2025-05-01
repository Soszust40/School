/**
 * @file LetterVisitorValue.cpp
 * @author Jackson White
 */

#include "pch.h"
#include "LetterVisitorValue.h"
#include "Letter.h"

/**
 * Visit the letter and assign mValue to letters value.
 * @param letter The letter to visit.
 */
void LetterVisitorValue::VisitLetter(Letter* letter)
{
    mValue = letter->GetValue();
}