/**
 * @file TrayDropOneLetterVisitor.h
 * @author Myles Walker
 */
 
#pragma once
#include "ItemVisitor.h"

class Tray;
class Item;

/**
 * Visitor that tells tray to drop one letter.
 */
class TrayDropOneLetterVisitor : public ItemVisitor {
private:
    /// The letter dropped from the tray.
    std::shared_ptr<Item> mDroppedLetter = nullptr;

public:
    /**
     * Visit a tray and instruct it to drop a single letter.
     * @param tray The tray we are visiting.
     */
    void VisitTray(Tray* tray) override;

    /**
     * Get the letter that was dropped by the tray.
     * @return A ptr to the dropped letter.
     */
    std::shared_ptr<Item> GetDroppedLetter() const { return mDroppedLetter; }
};



