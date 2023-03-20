#include <iostream>
#include <QCoreApplication>
#include <vision/vision.h>
#include <actuator/actuator.h>
#include <chrono>
#include <thread>
#include <math.h>
#include <behaviors/behaviors.h>
int etapa = 1;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Vision *vision = new Vision("224.0.0.1", 10002);
    Actuator *actuator = new Actuator("127.0.0.1", 20011);

    while(true) {
        // Run vision module
        vision->run();

        //vision
        SSL_DetectionRobot robot0 = vision->getRobot(true, 0);
        SSL_DetectionRobot robot1 = vision->getRobot(true, 1);
        SSL_DetectionRobot robot2 = vision->getRobot(true, 2);
        SSL_DetectionRobot robot3 = vision->getRobot(true, 3);

        SSL_DetectionBall ball = vision->getBall();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        // debug
        std::cout << etapa << "--" << hasBall(robot1, ball) << std::endl;

        //actuator
        switch(etapa) {
            case 1:
            //void shoot(SSL_DetectionRobot robot, Actuator *actuator, SSL_DetectionBall ball, bool isYellow, int id, float targetX, float targetY, float kick)
                shoot(robot0, actuator, ball, true, 0, robot1.x(), robot1.y(), 4.0);
                receiveBall(robot1, actuator, ball, true, 1);
                receiveBall(robot2, actuator, ball, true, 2);
                receiveBall(robot3, actuator, ball, true, 3);

                if (hasBall(robot1, ball)) etapa = 2;
                break;

            case 2:
                shoot(robot1, actuator, ball, true, 1, robot2.x(), robot2.y(), 4.0);
                receiveBall(robot0, actuator, ball, true, 0);
                receiveBall(robot2, actuator, ball, true, 2);
                receiveBall(robot3, actuator, ball, true, 3);

                if (hasBall(robot2, ball)) etapa = 3;
                break;

            case 3:
                shoot(robot2, actuator, ball, true, 2, robot3.x(), robot3.y(), 4.0);
                receiveBall(robot0, actuator, ball, true, 0);
                receiveBall(robot1, actuator, ball, true, 1);
                receiveBall(robot3, actuator, ball, true, 3);

                if (hasBall(robot3, ball)) etapa = 4;
                break;

            case 4:
                receiveBall(robot0, actuator, ball, true, 0);
                receiveBall(robot1, actuator, ball, true, 1);
                receiveBall(robot2, actuator, ball, true, 2);

                shoot(robot3, actuator, ball, true, 3, 4500.0, 0.0, 8.0);
        }
    }

    return a.exec();
}
