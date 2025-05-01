/**
 * @file LetterInTrayDrawer.h
 * @author Jackson White
 *
 * Visitor class for letters.
 */
 
#ifndef LETTERINTRAYDRAWER_H
#define LETTERINTRAYDRAWER_H
#include "Item.h"
#include "ItemVisitor.h"

/**
 * Letter visitor class, derived from ItemVisitor.
 *
 * Visits the letter in the tray and draws it.
 */
class LetterInTrayDrawer : public ItemVisitor{
private:
    /// The graphics we are drawing to
    std::shared_ptr<wxGraphicsContext> mGraphics = nullptr;
public:
    /**
     * Custom constructor that saves the graphics.
     *
     * @param graphics The graphics we will draw te letter to.
     */
    LetterInTrayDrawer(std::shared_ptr<wxGraphicsContext> graphics) : mGraphics(graphics){};
    void VisitLetter(Letter* letter) override;
};

#endif //LETTERINTRAYDRAWER_H
