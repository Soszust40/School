/**
 * @file Letter.h
 * @author Jackson White
 *
 * The class for letters.
 */
 
#ifndef LETTER_H
#define LETTER_H
#include "Item.h"

/**
 * Letter class
 *
 * Letters will be picked up by the player class and moved around.
 */
class Letter : public Item {
private:
    /// The value of the letter
    int mValue;

    /// the x value of the letter in the tray
    double mTrayX;
    /// the y value of the letter in the tray
    double mTrayY;

    /// The underlying image
    std::shared_ptr<wxImage> mItemImage = nullptr;

    /// The bitmap we can display for this item
    std::shared_ptr<wxBitmap> mItemBitmap = nullptr;

public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitLetter(this); }

    /// Default constructor (disabled)
    Letter() = delete;

    /// Copy constructor (disabled)
    Letter(const Letter &) = delete;

    Letter(Game* game, const std::wstring& imageName);

    /// Assignment operator
    void operator=(const Letter &) = delete;

    void XmlLoad(wxXmlNode *node, wxXmlNode *declaration) override;

    /**
     * Get the value of the letter block.
     *
     * @return Int for the value of the letter.
     */
    int GetValue() const { return mValue; }

    /**
     * Set the letters tray coordinates
     *
     * @param trayX the trayX coord for letter
     * @param trayY the trayY coord for letter
     */
    void SetTrayCoordinate(double trayX, double trayY) {mTrayX = trayX; mTrayY = trayY;}

    void DrawInTray(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Get the x location of the letter in the tray
     *
     * @return double x coord
     */
    double GetTrayX() const { return mTrayX; }

    /**
     * Get the y location of the letter in the tray
     *
     * @return double of y coord
     */
    double GetTrayY() const { return mTrayY; }


};

#endif //LETTER_H
