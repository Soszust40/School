/**
 * @file PopupVisitor.h
 * @author Jackson White
 *
 * Popup visitor base class.
 */
 
#ifndef POPUPVISITOR_H
#define POPUPVISITOR_H


class StartTextPopup;
class EndTextPopup;
class WrongGuessTextPopup;
class ChestFullTextPopup;
class TextPopupObstacle;

/**
 * Popup visitor base class
 */
class PopupVisitor {
private:

public:
    /// Virtual destructor
    virtual ~PopupVisitor() {};

    /**
     * Visit the start text popup.
     * @param popup The start text popup to visit.
     */
    virtual void VisitStartPopup(StartTextPopup* popup) {}

    /**
     * Visit the end text popup.
     * @param popup The end text popup we are visiting.
     */
    virtual void VisitEndPopup(EndTextPopup* popup) {}

    /**
     * Visit a wrong text popup.
     * @param popup The wrong text popup we are visiting.
     */
    virtual void VisitWrongPopup(WrongGuessTextPopup* popup) {}

    /**
     * Visit a chest text popup.
     * @param popup The chest text popup we are visiting.
     */
    virtual void VisitChestPopup(ChestFullTextPopup* popup) {}

    /**
     * Visit an obstacle text popup.
     * @param popup The obstacle text popup we are visiting.
     */
    virtual void VisitObstaclePopup(TextPopupObstacle* popup) {}
protected:
    /**
     * Constructor for the Popup visitor.
     * Ensures this is an abstract class.
     */
    PopupVisitor() {}
};

#endif //POPUPVISITOR_H
