simple UdpForwardApp
{
    parameters:
        int localPort;
        string destAddresses;
        int destPort;
        @display("i=block/app");
    gates:
        input udpIn;
        output udpOut;
}
