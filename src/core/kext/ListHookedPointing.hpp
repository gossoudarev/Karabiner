#ifndef LISTHOOKEDPOINTING_HPP
#define LISTHOOKEDPOINTING_HPP

#include "base.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  namespace ListHookedPointing {
    void terminate(void);

    class Item;
    bool append(IOHIKeyboard *kbd);
    Item *get(const IOHIKeyboard *kbd);
    Item *get(void);
    void refresh(void);

    // ----------------------------------------------------------------------
    class Item {
    public:
      Item(void) { pointing = NULL; }

      void initialize(IOHIPointing *_pointing);
      void refresh(void);
      void terminate(void);

      IOHIPointing *get(void) const { return pointing; }

    private:
      IOHIPointing *pointing;
      RelativePointerEventCallback orig_relativePointerEventAction;
      ScrollWheelEventCallback orig_scrollWheelEventAction;
      OSObject *orig_relativePointerEventTarget;
      OSObject *orig_scrollWheelEventTarget;

      RelativePointerEventCallback getCurrent_relativePointerEventAction(void) const {
        return reinterpret_cast<RelativePointerEventCallback>(pointing->_relativePointerEventAction);
      }
      ScrollWheelEventCallback getCurrent_scrollWheelEventAction(void) const {
        return reinterpret_cast<ScrollWheelEventCallback>(pointing->_scrollWheelEventAction);
      }
    };

    // ----------------------------------------------------------------------
    void hook_RelativePointerEventCallback(OSObject *target,
                                           int buttons,
                                           int dx,
                                           int dy,
                                           AbsoluteTime ts,
                                           OSObject *sender,
                                           void *refcon);
    void hook_ScrollWheelEventCallback(OSObject * target,
                                       short deltaAxis1,
                                       short deltaAxis2,
                                       short deltaAxis3,
                                       IOFixed fixedDelta1,
                                       IOFixed fixedDelta2,
                                       IOFixed fixedDelta3,
                                       SInt32 pointDelta1,
                                       SInt32 pointDelta2,
                                       SInt32 pointDelta3,
                                       SInt32 options,
                                       AbsoluteTime ts,
                                       OSObject *sender,
                                       void *refcon);
  }
}

#endif
