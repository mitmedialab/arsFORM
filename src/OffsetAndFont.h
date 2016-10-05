//
//  OffsetAndFont.h
//  cooperFORM
//
//  Created by tmg2 on 11/16/14.
//
//

#ifndef __cooperFORM__OffsetAndFont__
#define __cooperFORM__OffsetAndFont__

#include <iostream>

struct OffsetAndFont {
    int offsetX;
    int offsetY;
    int fontSizeOffset;
    
    // default values:
    OffsetAndFont():offsetX(0),offsetY(0),fontSizeOffset(0) { }
};

#endif /* defined(__cooperFORM__OffsetAndFont__) */
