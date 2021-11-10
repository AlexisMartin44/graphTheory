//
//  Constants.h
//  PiscineING2
//
//  Created by Titouan Lermite on 27/04/2020.
//  Copyright © 2020 Titouan Lermite. All rights reserved.
//

#include <limits>

#ifndef Constants_h
#define Constants_h

/**
 * @brief This file contains all the constants used in our code
 */

#define DELTA_LAMBDA 1e-2
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define MARGE 50
#define DEC 15
#define DEGREE      0b0001
#define VECT_PROPRE 0b0010
#define PROXIMITY   0b0100
#define BETWEENNESS 0b1000
#define MIN_RADIUS 10.0
#define MIN_RADIUS_MULT 1.0
#define MAX_RADIUS_MULT 1.5
#define INFINI std::numeric_limits<int>::max()


#define MIN(x,y) (x < y ? x : y)

#endif /* Constants_h */
