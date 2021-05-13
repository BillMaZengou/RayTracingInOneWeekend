//
//  stb_image.h
//  RayTracingInOneWeekend
//
//  Created by Bill Ma on 2021/5/13.
//

#ifndef stb_image_h
#define stb_image_h

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
    #pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

// Restore warning levels.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
    #pragma warning (pop)
#endif

#endif /* stb_image_h */
