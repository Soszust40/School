/**
 * @file Given.h
 * @author Jackson White
 *
 * The givens class, very similar to letters, but does not get picked up and stored in tray
 */

#include "Item.h"

#ifndef GIVEN_H
#define GIVEN_H

/**
 * The given class. It is derived from Item and is very similar to Letters.
 */
class Given : public Item {
private:
    /// The value of the letter
    int mValue;

public:
    /**
     * Accept a visitor.
     * @param visitor The visitor we accept.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitGiven(this); }

    /// Default constructor (disabled)
    Given() = delete;

    /// Copy constructor (disabled)
    Given(const Given &) = delete;
    Given(Game* game, const std::wstring& imageName);

    /// Assignment operator
    void operator=(const Given &) = delete;

    void XmlLoad(wxXmlNode *node, wxXmlNode *declaration) override;

    /**
     * Get the value of the given block.
     *
     * @return Int for the value of the given.
     */
    int GetValue() const { return mValue; }
};

#endif //GIVEN_H
