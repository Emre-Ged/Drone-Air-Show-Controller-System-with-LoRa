import inet.applications.udpapp.UdpBasicApp;
import inet.node.inet.Router;
import inet.node.internetcloud.InternetCloud;
import flora.LoRaPhy.LoRaMedium;
import flora.LoraNode.LoRaNode;
import flora.LoraNode.LoRaGW;
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth1G;

@license(LGPL);


channel LoRaCable extends ned.DatarateChannel
{
    delay = 0.001s;
    datarate = 250bps;  // Approx LoRa data rate, tweak as needed
}


//----------------------------------------------------------------
// Flat (2D) topology – all @display strings omit z=…
//----------------------------------------------------------------
network DroneNetwork
{
    parameters:
        int numberOfNodes = default(10);
        int numberOfGateways = default(1);
        int networkSizeX = default(500);
        int networkSizeY = default(500);
        int networkSizeZ = default(0);
        @display("bgb=562,417");
    submodules:
        // renamed from loRaNodes → Drone
        Drone1: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='2']");
                //movement[@id='2']");
                //movement[@id='2']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='1']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=140,300;i=device/drone");
        }

        Drone2: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='2']");
                //movement[@id='2']");
                //movement[@id='2']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='2']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=140,300;i=device/drone");
        }
        Drone3: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='3']");
                //movement[@id='3']");
                //movement[@id='3']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='3']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=220,300;i=device/drone");
        }
        Drone4: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='4']");
                //movement[@id='4']");
                //movement[@id='4']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='4']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=220,300;i=device/drone");
        }
        Drone5: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='5']");
                //movement[@id='5']");
                //movement[@id='5']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='5']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=260,300;i=device/drone");
        }
        Drone6: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='6']");
                //movement[@id='6']");
                //movement[@id='6']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='6']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=300,300;i=device/drone");
        }
        Drone7: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='7']");
                //movement[@id='7']");
                //movement[@id='7']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='7']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=340,300;i=device/drone");
        }
        Drone8: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='8']");
                //movement[@id='8']");
                //movement[@id='8']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='8']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=380,300;i=device/drone");
        }
        Drone9: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='9']");
                //movement[@id='9']");
                //movement[@id='9']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='9']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=420,300;i=device/drone");
        }
        Drone10: LoRaNode {

            parameters:
                radio.typename = "LoraRadio";
                //radio.display = "i=device/lora_device";
                mac.typename = "LoraMac";
                //mac.display = "i=device/lora_mac";
                mobility.typename = "TurtleMobility";
                //mobility.display = "i=block/mobility";
                //movement[@id='10']");
                //movement[@id='10']");
                //movement[@id='10']");
                mobility.turtleScript = xmldoc("turtle1.xml", "movements//movement[@id='10']");
                radio.mediumModule = "^.LoRaMedium";  // shared LoRa medium
                //mobility.startOnReception = true;
                @display("p=460,300;i=device/drone");
        }

        loRaGW[numberOfGateways]: LoRaGW {
            @display("p=300,198;is=s");
        }
        LoRaMedium: LoRaMedium {
            @display("p=508,40");
        }
        networkServer: StandardHost {
            parameters:
                @display("p=49,44");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=18,398");
        }
        internetCloud: InternetCloud {
            @display("p=231,44");
        }
        gwRouter[numberOfGateways]: Router {
            @display("p=300,44");
        }
        nsRouter: Router {
            @display("p=137,44");
        }


    connections allowunconnected:

		


        // wired backbone
        networkServer.ethg++ <--> Eth1G <--> nsRouter.ethg++;
        nsRouter.pppg++ <--> Eth1G <--> internetCloud.pppg++;
        for i=0..numberOfGateways-1 {
            internetCloud.pppg++ <--> Eth1G <--> gwRouter[i].pppg++;
            gwRouter[i].ethg++ <--> Eth1G <--> loRaGW[i].ethg++;
        }
}
