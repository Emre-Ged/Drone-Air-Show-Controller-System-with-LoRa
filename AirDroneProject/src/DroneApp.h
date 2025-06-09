#ifndef __DRONEAIRSHOW_DRONEAPP_H
#define __DRONEAIRSHOW_DRONEAPP_H

#include "inet/applications/base/ApplicationBase.h"

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


using namespace omnetpp;
using namespace inet;

namespace droneairshow {

class DroneApp : public ApplicationBase, public UDPSocket::ICallback
{
  protected:
    UDPSocket socket;
    // Parameters:
    double failureRate;         // λ for Poisson failure events
    double orientationChangeRate; // λ for Poisson orientation changes
    L3Address controllerAddr;
    int controllerPort;

    // States
    bool isFailed = false;
    simtime_t lastFailureTime = NaN;
    simtime_t lastOrientationChangeTime = NaN;

    // Self‐messages:
    enum SelfMsgKinds { START, SEND_TELEMETRY, POISSON_FAILURE, POISSON_ORIENTATION };

    int pkTelemetrySent = 0;
    int pkCmdReceived = 0;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    virtual void setupSocket();
    virtual void schedulePoissonEvents();
    virtual void scheduleNextFailure();
    virtual void scheduleNextOrientationChange();

    virtual void processControlCommand(Packet *pk);
    virtual void sendTelemetry();

    virtual L3Address resolveControllerAddress();

  public:
    DroneApp();
    virtual ~DroneApp();
};

} // namespace

#endif // __DRONEAIRSHOW_DRONEAPP_H
