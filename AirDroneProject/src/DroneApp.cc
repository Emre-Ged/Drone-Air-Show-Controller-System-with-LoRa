#include "DroneApp.h"
// Generic INET headers for UDP apps
#include "inet/common/INETDefs.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/applications/udp/UDPSocket.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/udp/UDPSocket.h"

// For self‐messages and random number draws
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/TimeTag_m.h"

namespace droneairshow {

Define_Module(DroneApp);

DroneApp::DroneApp() { }

DroneApp::~DroneApp() { }

void DroneApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        failureRate = par("failureRate").doubleValue();
        orientationChangeRate = par("orientationChangeRate").doubleValue();
        controllerPort = par("controllerPort").intValue();
        // controllerAddr can be a parameter; we’ll use a string in omnetpp.ini
        const char *ctrlAddrStr = par("controllerAddress").stringValue();
        controllerAddr = L3AddressResolver().resolve(ctrlAddrStr);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        setupSocket();
        // Schedule first Poisson‐distributed events
        schedulePoissonEvents();
    }
}

void DroneApp::setupSocket()
{
    // Bind to an ephemeral port or a fixed port
    socket.setOutputGate(gate("udpOut"));
    socket.bind(par("localPort").intValue());
    socket.setCallback(this);
}

void DroneApp::schedulePoissonEvents()
{
    // Draw next failure and orientation change times:
    scheduleNextFailure();
    scheduleNextOrientationChange();
}

void DroneApp::scheduleNextFailure()
{
    if (failureRate > 0) {
        // Exponential inter-arrival = exponentialRV(lambda)
        double interval = exponential(1.0 / failureRate);
        cMessage *msg = new cMessage("failureEvent", POISSON_FAILURE);
        scheduleAt(simTime() + interval, msg);
    }
}

void DroneApp::scheduleNextOrientationChange()
{
    if (orientationChangeRate > 0) {
        double interval = exponential(1.0 / orientationChangeRate);
        cMessage *msg = new cMessage("orientationEvent", POISSON_ORIENTATION);
        scheduleAt(simTime() + interval, msg);
    }
}

void DroneApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        switch (msg->getKind()) {
            case POISSON_FAILURE:
                // Simulate failure
                isFailed = true;
                lastFailureTime = simTime();
                EV << "Drone " << getParentModule()->getName() << " FAILED at t=" << simTime() << "\n";
                // After failure, we may choose to stop sending telemetry;
                // we could also schedule a “repair” event if desired, but not in original proposal.
                // Do not send telemetry while failed.
                // Schedule next failure anyway if you want multiple failures:
                scheduleNextFailure();
                break;

            case POISSON_ORIENTATION:
                // Simulate an orientation change
                lastOrientationChangeTime = simTime();
                EV << "Drone " << getParentModule()->getName() << " ORIENTATION CHANGE at t=" << simTime() << "\n";
                // In a realistic sim, you’d update position or mobility here.
                // For simplicity, we just record the event.
                scheduleNextOrientationChange();
                break;

            case SEND_TELEMETRY:
                // Timer to send telemetry (triggered after receiving a command)
                if (!isFailed) {
                    sendTelemetry();
                }
                break;

            default:
                break;
        }
        delete msg;
    }
    else if (auto pk = dynamic_cast<Packet *>(msg)) {
        // Received a UDP packet (should be CONTROL_COMMAND from controller)
        processControlCommand(pk);
        delete pk;
    }
    else {
        delete msg;
    }
}

void DroneApp::processControlCommand(Packet *pk)
{
    // Received a control command ⇒ schedule an immediate (or slight‐delay) telemetry reply
    pkCmdReceived++;
    recordScalar("ControlCmdsReceived", pkCmdReceived);

    if (!isFailed) {
        // Send telemetry after a tiny processing delay (e.g., 10ms)
        cMessage *selfMsg = new cMessage("sendTelemetry", SEND_TELEMETRY);
        scheduleAt(simTime() + SimTime(10, SIMTIME_MS), selfMsg);
    }
    // If the drone is failed, drop the command (no reply).
}

void DroneApp::sendTelemetry()
{
    // Build a telemetry UDP packet and send back to controller
    Packet *packet = new Packet("Telemetry");
    auto payload = makeShared<BytesChunk>();
    payload->setBytes(std::vector<uint8_t>(20, 0));
    packet->insertAtBack(payload);

    // Use the controller’s address and port
    socket.sendTo(packet, controllerAddr, controllerPort);
    pkTelemetrySent++;
}

void DroneApp::finish()
{
    recordScalar("TelemetrySent", pkTelemetrySent);
    recordScalar("CmdsReceived", pkCmdReceived);
    recordScalar("Failures", lastFailureTime.isUnspecified() ? 0 : 1);
    // If you want to record more (like total orientation events), add counters for them.
}

void DroneApp::refreshDisplay() const
{
    char buf[64];
    if (isFailed)
        sprintf(buf, "FAILED");
    else
        sprintf(buf, "OK, sentTel: %d", pkTelemetrySent);
    getDisplayString().setTagArg("t", 0, buf);
}

} // namespace
