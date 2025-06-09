#include "ControllerApp.h"
// Generic INET headers for UDP apps
#include "inet/common/INETDefs.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"


// For self‐messages and random number draws
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/TimeTag_m.h"

namespace droneairshow {

Define_Module(ControllerApp);

ControllerApp::ControllerApp() { }

ControllerApp::~ControllerApp() { }

void ControllerApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        // Read parameters from omnetpp.ini or NED:
        sendInterval = par("sendInterval").doubleValue();
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        // Create and bind UDP socket
        socket.setOutputGate(gate("udpOut"));
        socket.bind(par("localPort").intValue());
        groupResolver.initialize(par("destAddresses")); // destAddresses could be "255.255.255.255" for broadcast

        // Schedule the first CONTROL_COMMAND
        if (sendInterval > 0) {
            cMessage *selfMsg = new cMessage("sendCmd", SEND_COMMAND);
            scheduleAt(simTime() + sendInterval, selfMsg);
        }
    }
}

void ControllerApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (msg->getKind() == SEND_COMMAND) {
            sendControlCommand();
            // Reschedule next
            cMessage *selfMsg = new cMessage("sendCmd", SEND_COMMAND);
            scheduleAt(simTime() + sendInterval, selfMsg);
        }
        delete msg;
    }
    else if (auto pk = dynamic_cast<Packet *>(msg)) {
        // It’s a UDP packet from a drone
        processTelemetryPacket(pk);
        delete pk;
    }
    else {
        delete msg;
    }
}

void ControllerApp::sendControlCommand()
{
    // Build a UDP packet with a short payload “CONTROL”
    const char *msgName = "ControlCmd";
    Packet *packet = new Packet(msgName);
    // You can add a payload or header; for simplicity, just send an empty packet with a control tag
    // e.g., with a ByteCountTag to set packet size to 20 bytes
    const auto& payload = makeShared<BytesChunk>();
    payload->setBytes(std::vector<uint8_t>(20, 0)); // 20‐byte dummy payload
    packet->insertAtBack(payload);

    // Resolve broadcast (or group) address: e.g. 10.0.0.255 or multicast group; here we do broadcast over LoRa
    L3Address dest = groupResolver.resolveOne(0);
    socket.sendTo(packet, dest, par("destPort").intValue());
    pkSent++;
}

void ControllerApp::processTelemetryPacket(Packet *pk)
{
    // A telemetry packet arrived; record it
    pkRcvdTelemetry++;
    recordScalar("TelemetryReceived", pkRcvdTelemetry);
    // You can parse contents if needed
}

void ControllerApp::finish()
{
    recordScalar("CommandsSent", pkSent);
    recordScalar("TelemetryReceived", pkRcvdTelemetry);
}

void ControllerApp::refreshDisplay() const
{
    char buf[64];
    sprintf(buf, "sent: %d, rcvdTel: %d", pkSent, pkRcvdTelemetry);
    getDisplayString().setTagArg("t", 0, buf);
}

} // namespace
