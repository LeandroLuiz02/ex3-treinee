#include "actuator.h"

Actuator::Actuator(QString actuatorAddress, quint16 actuatorPort) {
    _actuatorAddress = actuatorAddress;
    _actuatorPort = actuatorPort;
    _actuatorSocket = new QUdpSocket();

    connectToNetwork();
}

void Actuator::connectToNetwork() {
    if(_actuatorSocket->isOpen()) {
        _actuatorSocket->close();
    }

    _actuatorSocket->connectToHost(_actuatorAddress, _actuatorPort, QIODevice::WriteOnly, QAbstractSocket::IPv4Protocol);
}

void Actuator::sendCommand(bool isYellow, int id, float vx, float vy, float vw, bool spin, float kick) {
    // Create grSimPacket
    grSim_Packet packet;

    // Set macro informations
    packet.mutable_commands()->set_isteamyellow(isYellow);
    packet.mutable_commands()->set_timestamp(0.0);

    // Create robot command message
    grSim_Robot_Command *command = packet.mutable_commands()->add_robot_commands();

    // Setting commands
    // Set robot id
    command->set_id(id);

    // Set velocity
    command->set_wheelsspeed(false);
    command->set_veltangent(vx);
    command->set_velnormal(vy);
    command->set_velangular(vw);

    // Set kick speed
    command->set_kickspeedx(kick);
    command->set_kickspeedz(0.0);

    // Set spinner
    command->set_spinner(spin);

    // Send data to simulator
    std::string buffer;
    packet.SerializeToString(&buffer);

    // Write buffer in network
    _actuatorSocket->write(buffer.c_str(), buffer.length());
}
