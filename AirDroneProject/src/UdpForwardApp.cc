#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/INETDefs.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

using namespace inet;

class UdpForwardApp : public ApplicationBase, public UdpSocket::ICallback
{
  protected:
    UdpSocket socket;
    int localPort = -1;
    int destPort = -1;
    std::vector<L3Address> destAddresses;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override {}

    // Lifecycle support
    virtual void handleStartOperation(LifecycleOperation *operation) override {}
    virtual void handleStopOperation(LifecycleOperation *operation) override {}
    virtual void handleCrashOperation(LifecycleOperation *operation) override {}

    // UdpSocket::ICallback required methods
    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override {}
    virtual void socketClosed(UdpSocket *socket) override {}
};

Define_Module(UdpForwardApp);

void UdpForwardApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        localPort = par("localPort");
        destPort = par("destPort");

        const char *destAddrs = par("destAddresses");
        cStringTokenizer tokenizer(destAddrs);
        while (tokenizer.hasMoreTokens()) {
            const char *token = tokenizer.nextToken();
            destAddresses.push_back(L3AddressResolver().resolve(token));
        }
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);
        socket.setCallback(this);
    }
}

void UdpForwardApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
        delete msg;
    else
        throw cRuntimeError("Unexpected message: should be handled by socket callback");
}

void UdpForwardApp::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    for (auto& addr : destAddresses) {
        auto copy = packet->dup();
        socket->sendTo(copy, addr, destPort);
    }
    delete packet;
}
