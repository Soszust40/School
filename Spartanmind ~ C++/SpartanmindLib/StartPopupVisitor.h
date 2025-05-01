/**
 * @file StartPopupVisitor.h
 * @author Jackson White
 *
 * Visit the start popups.
 */
 
#ifndef STARTPOPUPVISITOR_H
#define STARTPOPUPVISITOR_H
#include "PopupVisitor.h"

/**
* start Popup visitor derived from PopupVisitor.
*/
class StartPopupVisitor : public PopupVisitor{
private:
    /// The number of start popups in the vector.
    int mNumStart = 0;
public:
    void VisitStartPopup(StartTextPopup* popup) override;

    /**
     * Return the number of start popups.
     * @return The number of start popups.
     */
    int NumStart() {return mNumStart;}

};

#endif //STARTPOPUPVISITOR_H
