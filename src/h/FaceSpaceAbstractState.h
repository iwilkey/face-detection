#ifndef _FACE_SPACE_ABSTRACT_STATE_H_
#define _FACE_SPACE_ABSTRACT_STATE_H_

#include "FaceSpaceCore.h"

class FaceSpaceAbstractState {
    public:
        FaceSpaceAbstractState(FaceSpaceCore *);
        ~FaceSpaceAbstractState();

        virtual void begin(void) = 0;
        virtual void end(void) = 0;
        virtual void tick(void) = 0;
        virtual void render(void) = 0;

    private:
        FaceSpaceCore * core;
};

#endif // _FACE_SPACE_ABSTRACT_STATE_H_
