#include <iostream>

/**
 * Implemented this deisng pattern to prevent implementing the following classes;
 * MqttLightDevice, WebSocketLightDevice, MqttDoorBellDevice, WebSocketDoorBellDevice
*/


class IConnection
{
    public:
        virtual int sendMessage(std::string message) = 0;
};

class MqttConnection : public IConnection
{
    public:
        int init() 
        {
            std::cout << "Init mqtt connection." << std::endl;
        }

        int start() 
        {
            std::cout << "Start mqtt connection." << std::endl;
        }

        int sendMessage(std::string message)
        {
            std::cout << "Mqtt message send. Message -> " + message << std::endl;
        }
};

class WebSocketConnection : public IConnection
{
    public:
        int connect()
        {
            std::cout << "Web Socked connection done." << std::endl;
        }
        int sendMessage(std::string message)
        {
            std::cout << "Web Socket message send. Message -> " + message << std::endl;
        }
};

class Device 
{
    protected:
        std::string m_name;
        IConnection *m_connection;

    public:
        Device(std::string device_name, IConnection *connection) 
        {
            m_name = device_name;
            m_connection = connection;
        };
        ~Device()
        {
            if (m_connection)
            {
                delete m_connection;
            }
        }
        std::string getName()
        {
            return m_name;
        };
};

class Light : public Device
{
    public:
      Light(std::string device_name, IConnection *connection) 
        : Device(device_name, connection) 
        {
        };

        void on()
        {
            std::cout << "Send message from " + getName() << std::endl;
            m_connection->sendMessage("I am turned on.");
        }

        void off()
        {
            std::cout << "Send message from " + getName() << std::endl;
            m_connection->sendMessage("I am turned off.");
        }
};

class DoorBell : public Device
{
    public:
      DoorBell(std::string device_name, IConnection *connection) 
        : Device(device_name, connection) 
        {
        };

        void ring()
        {
            std::cout << "Send message from " + getName() << std::endl;
            m_connection->sendMessage("I am ringing.");
        }
};

int main() 
{
    // Prepare mqtt connection.
    MqttConnection *mqttConnection = new MqttConnection();
    mqttConnection->init();
    mqttConnection->start();

    // Prepare web socket connection.
    WebSocketConnection *webSocketConnection = new WebSocketConnection;
    webSocketConnection->connect();
    
    // Create mqtt light device.
    Light *myLight1 = new Light("My Light 1", mqttConnection);
    // Create web socket light device.
    Light *myLight2 = new Light("My Light 2", webSocketConnection); 
    // Create mqtt door bel device
    DoorBell *myDoorBell1 = new DoorBell("My Door Bell 1", mqttConnection);

    myLight1->on();
    myLight2->off();
    myDoorBell1->ring();

    return 0;
}