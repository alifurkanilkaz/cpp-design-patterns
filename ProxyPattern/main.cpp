#include <iostream>

typedef std::string MAC;

class IMACProvider {
    public:
        virtual MAC getMAC() = 0;
};

class MACProvider : public IMACProvider {
    public:
        /*
        * Gets MAC from the shell.
        */
        MAC getMAC() {
            std::cout << "Fething MAC from the shell..." << std::endl;
            return "XX:XX:XX:XX:XX:XX";
        }
};

class MACProviderProxy : public IMACProvider{
    public:
        MACProviderProxy() 
            : m_MAC("")
        {}

        MAC getMAC() {
           if(m_MAC.empty()) {
               IMACProvider *macProvider = new MACProvider();
               m_MAC = macProvider->getMAC();
               delete macProvider;     
           }

            return m_MAC;
        }
    private:
        MAC m_MAC;
};


int main() {
    IMACProvider *macProvider = new MACProviderProxy();
    
    std::cout << "Get MAC -> " + macProvider->getMAC() << std::endl;
    std::cout << "Get MAC -> " + macProvider->getMAC() << std::endl;
    std::cout << "Get MAC -> " + macProvider->getMAC() << std::endl;

    delete macProvider;

    return 0;
}
