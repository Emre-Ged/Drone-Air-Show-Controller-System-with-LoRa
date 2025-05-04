#include <omnetpp.h>
#include <cstdio>
#include <memory>
//may need to add shared pointer in future, OMNETT working or not idk -ALP
using namespace omnetpp;

class Controller : public cSimpleModule {
private:
    cMessage *sendCmdEvt;
    cMessage *failureEvt;
    double cmdInterval;
    double failureRate;  // λ failures per sim-second

protected:
    virtual void initialize() override {
        cmdInterval = par("cmdInterval").doubleValue();   // e.g. 1.0s
        failureRate = par("failureRate").doubleValue();   // e.g. 0.1/s
        sendCmdEvt  = new cMessage("sendCmd");
        failureEvt  = new cMessage("droneFailure");
        scheduleAt(simTime() + cmdInterval, sendCmdEvt);
        scheduleAt(simTime() + exponential(1.0/failureRate), failureEvt);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == sendCmdEvt) {
            // broadcast CMD to all drones
            for (int i = 0; i < 10; i++)
                send(new cMessage("CMD"), "out", i);
            scheduleAt(simTime() + cmdInterval, sendCmdEvt);
        }
        else if (msg == failureEvt) {
            // random drone failure
            int idx = intuniform(0, 9);
            auto *f = new cMessage("FAIL");
            sendDirect(f,
                       getParentModule()->getSubmodule("drone", idx),
                       "in");
            scheduleAt(simTime() + exponential(1.0/failureRate), failureEvt);
        }
        else {
            // incoming ACK
            delete msg;
        }
    }

    virtual void finish() override {
        cancelAndDelete(sendCmdEvt);
        cancelAndDelete(failureEvt);
    }
};

Define_Module(Controller);
