//
// inlines.h
// Created by TheFatNinja 
// 16-04-2019
//

#ifndef GL_ENGINE_INLINES_H
#define GL_ENGINE_INLINES_H

template <class T>
inline T MAX(T a, T b) {
    if (a >= b) {
        return a;
    }
    else {
        return b;
    }
}

template <class T>
inline T MIN(T a, T b) {
    if (a <= b) {
        return a;
    }
    else {
        return b;
    }
}


#endif //GL_ENGINE_INLINES_H
