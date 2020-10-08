#ifndef CONSTANTS_H
#define CONSTANTS_H
	
// 32 - led in line
// 4 - bytes per led
// 100 - line in circle
#define SizeLine ((32 + 2) * 4)  // bytes
#define LineCount 100 // in one circle

#define LineUpdateTimerClockG (24000000) 
#define CirclePerSecond (25)
#define TimeForCircleUs (1000000 / CirclePerSecond)
#define TimeForLineUs (TimeForCircleUs / LineCount)

#endif //CONSTANTS_H