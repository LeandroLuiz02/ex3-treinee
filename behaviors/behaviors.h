#ifndef BEHAVIORS_H
#define BEHAVIORS_H
#include <skills/skills.h>

class behaviors
{
public:
    behaviors();
};

void shoot(SSL_DetectionRobot robot, Actuator *actuator, SSL_DetectionBall ball, bool isYellow, int id, float targetX, float targetY, float kick);
void receiveBall(SSL_DetectionRobot robot, Actuator *actuator, SSL_DetectionBall ball, bool isYellow, int id);

#endif // BEHAVIORS_H
