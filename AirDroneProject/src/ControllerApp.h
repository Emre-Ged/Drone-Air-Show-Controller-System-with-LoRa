#ifndef __DRONEAIRSHOW_CONTROLLERAPP_H
#define __DRONEAIRSHOW_CONTROLLERAPP_H

// Generic INET headers for UDP apps
#include "inet/common/INETDefs.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"

// For self‐messages and random number draws
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/TimeTag_m.h"
#include "inet/applications/base/ApplicationBase.h"

using namespace omnetpp;
using namespace inet;

namespace droneairshow {

class ControllerApp : public ApplicationBase, public UDPSocket::ICallback
{
  protected:
    // UDP socket
    UDPSocket socket;

    // Parameters from NED:
    double sendInterval;   // e.g. how often to send commands
    L3AddressGroupResolver groupResolver; // for broadcast or group sending

    // Self-message kinds
    enum SelfMsgKinds { SEND_COMMAND = 1 };

    // Statistical recorders
    simtime_t lastSendTime;
    int pkSent = 0;
    int pkRcvdTelemetry = 0;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    // UDPSocket callback
    virtual void socketDataArrived(UDPSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UDPSocket *socket, Indication *indication) override { }
    virtual void socketClosed(UDPSocket *socket) override { }

    virtual void sendControlCommand();
    virtual void processTelemetryPacket(Packet *pk);

    // Utility: broadcast address
    L3Address getBroadcastAddress();

  public:
    ControllerApp();
    virtual ~ControllerApp();
};

} // namespace

#endif // __DRONEAIRSHOW_CONTROLLERAPP_H
