#include "behaviors.h"


behaviors::behaviors()
{

}

void shoot(SSL_DetectionRobot robot, Actuator *actuator, SSL_DetectionBall ball, bool isYellow, int id, float targetX, float targetY, float kick) {
    bool hasB = hasBall(robot, ball);
    if (hasB && !isPointingTo(robot, targetX, targetY)) pointTo(robot, actuator, isYellow, id, targetX, targetY, true);
    else if (!hasB) goTo(robot, actuator, isYellow, id, ball.x(), ball.y());
    else actuator->sendCommand(isYellow, id, 0, 0, 0, false, kick);
}

void receiveBall(SSL_DetectionRobot robot, Actuator *actuator, SSL_DetectionBall ball, bool isYellow, int id) {
    pointTo(robot, actuator, isYellow, id, ball.x(), ball.y(), true);
}
