/**
 * @file TraysLettersVisitor.h
 * @author Jackson White
 *
 * Visitor for tray that gets the letters of tray.
 */
 
#ifndef TRAYSLETTERSVISITOR_H
#define TRAYSLETTERSVISITOR_H

#include "ItemVisitor.h"
class Item;

/**
 * Tray visitor class.
 * Is used to return the list of letters of tray.
 */
class TraysLettersVisitor : public ItemVisitor {
private:
    /// The letters currently in the tray.
    std::vector<std::shared_ptr<Item>> mLetters;
public:
    void VisitTray(Tray* tray) override;

    /**
     * Returns the letters of a tray object.
     *
     * @return A list of all the letters in the tray.
     */
    std::vector<std::shared_ptr<Item>> GetLetters() {return mLetters;};

};



#endif //TRAYSLETTERSVISITOR_H
