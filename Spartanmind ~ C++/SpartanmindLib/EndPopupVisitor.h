/**
 * @file EndPopupVisitor.h
 * @author Jackson White
 *
 * end popup visitor that counts how many end popups we have
 */
 
#ifndef ENDPOPUPVISITOR_H
#define ENDPOPUPVISITOR_H

#include "PopupVisitor.h"

/**
 * End popup visitor derived from popup visitor.
 *
 * Counts how many end popups we have.
 */
class EndPopupVisitor : public PopupVisitor {
private:
    /// The number of end game popups we have
    int mEndPopup = 0;
public:
    void VisitEndPopup(EndTextPopup* popup) override;

    /**
     * Function that returns the total amount of end text popups there are.
     *
     * @return The number of popups.
     */
    int NumEndPopup() {return mEndPopup; };
};

#endif //ENDPOPUPVISITOR_H
