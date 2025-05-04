#include <omnetpp.h>
#include <cstdio>
#include <memory>
using namespace omnetpp;

class Drone : public cSimpleModule {
private:
    bool failed = false;

protected:
    virtual void handleMessage(cMessage *msg) override {
        const char *name = msg->getName();
        if (strcmp(name,"CMD")==0 && !failed) {
            //uniform delay ([0,0.1]s) repaet
            sendDelayed(new cMessage("ACK"), uniform(0,0.1), "out");
        }
        else if (strcmp(name,"FAIL")==0) {
            failed = true;//go ofline
        }
        delete msg;
    }
};

Define_Module(Drone);
