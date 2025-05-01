/**
 * @file TrayRemoveLetterVisitor.h
 * @author Jackson White
 *
 * Tray visitor that removes a letter from the tray.
 */
 
#ifndef TRAYREMOVELETTERVISITOR_H
#define TRAYREMOVELETTERVISITOR_H
#include "ItemVisitor.h"
class Item;

/**
 * Tray visitor that removes the letter.
 */
class TrayRemoveLetterVisitor : public ItemVisitor{
private:
    /// Bool if we removed a letter.
    bool mRemovedLetter = false;

    /// The letter to subtract.
    std::shared_ptr<Item> mLetter = nullptr;
public:
    /**
     * Constructor for TrayRemoveLetterVisitor.
     *
     * @param letter The letter to remove.
     */
    TrayRemoveLetterVisitor(std::shared_ptr<Item> letter) : mLetter(letter){};

    void VisitTray(Tray* tray) override;

    /**
     * Check if we removed a letter from the tray.
     *
     * @return Bool if we removed a letter or not.
     */
    bool RemovedLetter() {return mRemovedLetter; }
};

#endif //TRAYREMOVELETTERVISITOR_H
