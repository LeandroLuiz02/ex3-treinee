#ifndef SKILLS_H
#define SKILLS_H
#include <actuator/actuator.h>
#include <vision/vision.h>

class skills
{
public:
    skills();
};

float distanceTo(SSL_DetectionRobot robot, float targetX, float targetY);
float angleTo(SSL_DetectionRobot robot, float x, float y);
bool isPointingTo(SSL_DetectionRobot robot, float x, float y);
bool shouldRotateLeft(SSL_DetectionRobot robot, float x, float y);
void goTo(SSL_DetectionRobot robot, Actuator *actuator, float isYellow, int id, float x, float y);
void pointTo(SSL_DetectionRobot robot, Actuator *actuator, float isYellow, int id, float x, float y, bool spin);
bool hasBall(SSL_DetectionRobot robot, SSL_DetectionBall ball);

#endif // SKILLS_H
