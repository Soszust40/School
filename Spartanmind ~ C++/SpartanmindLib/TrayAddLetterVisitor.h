/**
 * @file TrayAddLetterVisitor.h
 * @author Jackson White
 *
 * Tray visitor that checks if we have picked up the letter.
 */
 
#ifndef TRAYADDLETTERVISITOR_H
#define TRAYADDLETTERVISITOR_H

#include "ItemVisitor.h"
class Item;

/**
 * Tray visitor class derived from ItemVisitor.
 *
 * Returns a bool of we picked up the letter or not.
 */
class TrayAddLetterVisitor : public ItemVisitor {
private:
    /// Bool if we added the letter
    bool mAddedLetter = false;
    /// The letter to add
    std::shared_ptr<Item> mLetter = nullptr;
public:
    /**
     * Constructor to the TrayAddLetterVisitor.
     *
     * @param i a pointer to the letter.
     */
    TrayAddLetterVisitor(std::shared_ptr<Item> i ) : mLetter(i) {};

    void VisitTray(Tray * tray) override;

    /**
     * Returns a bool if we added the letter or not.
     *
     * @return Boolean of if we added the letter or not.
     */
    bool AddedLetter() {return mAddedLetter;};
};

#endif //TRAYADDLETTERVISITOR_H
