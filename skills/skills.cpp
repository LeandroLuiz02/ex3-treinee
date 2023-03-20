#include "skills.h"
#include <math.h>

skills::skills()
{

}

float distanceTo(SSL_DetectionRobot robot, float targetX, float targetY) {

    // sqrt((r.x - t.x)² + (r.y - t.y)²)
    return sqrt( pow(robot.x() - targetX, 2) + pow(robot.y() - targetY, 2) );
}

float angleTo(SSL_DetectionRobot robot, float x, float y) {
    //orientation robot should have to be pointing to

    float signal = 1.0;
    if (robot.y() > y) signal = -1.0;

    // uses the formula that returns the angle between two vectors
    if (distanceTo(robot, x, y) != .0f)
    return signal * acos((x - robot.x()) / (distanceTo(robot, x, y)));

    else return .0f;
}

bool isPointingTo(SSL_DetectionRobot robot, float x, float y) {
    float angleRange = 0.1;
    float supLimit = robot.orientation() + angleRange;
    float infLimit = robot.orientation() - angleRange;
    if (supLimit > angleTo(robot, x, y) && infLimit < angleTo(robot, x, y)) return true;
    else return false;
}


bool shouldRotateLeft(SSL_DetectionRobot robot, float x, float y) {

    if (robot.orientation() * angleTo(robot, x, y) >= 0) { // both have same signal

        if (robot.orientation() > angleTo(robot, x, y)) return false;
        else return true;
    }

    else {

        float oppositeRobotAngle;


        //if robot poins to positive y
        if (robot.orientation() > 0) {
            oppositeRobotAngle = robot.orientation() - M_PI/2.0;
            if (robot.orientation() >= angleTo(robot, x, y) && angleTo(robot, x, y) >= oppositeRobotAngle) return false;
            return true;
        }

        else {
            oppositeRobotAngle = robot.orientation() + M_PI/2.0;
            if (oppositeRobotAngle >= angleTo(robot, x, y) && angleTo(robot, x, y) >= robot.orientation()) return true;
            return false;
        }
    }
}

void goTo(SSL_DetectionRobot robot, Actuator *actuator, float isYellow, int id, float x, float y) {
    float linearSpeed = 1;
    float angularSpeed = 2;
    float relativeOrientation = angleTo(robot, x, y) - robot.orientation();
    float vx = cos(relativeOrientation) * linearSpeed;
    float vy = sin(relativeOrientation) * linearSpeed;
    float vw = angularSpeed;
    if (!shouldRotateLeft(robot, x, y)) vw = -angularSpeed;

    actuator->sendCommand(isYellow, id, vx, vy, vw, distanceTo(robot, x, y) < 200, 0.0);
}

void pointTo(SSL_DetectionRobot robot, Actuator *actuator, float isYellow, int id, float x, float y, bool spin) {

    float vw = 1.0;
    if (!shouldRotateLeft(robot, x, y)) vw = -vw;

    actuator->sendCommand(isYellow, id, 0, 0, vw, spin, 0.0);
}

bool hasBall(SSL_DetectionRobot robot, SSL_DetectionBall ball) {
    if (distanceTo(robot, ball.x(), ball.y()) < 120) return true;
    else return false;
}
