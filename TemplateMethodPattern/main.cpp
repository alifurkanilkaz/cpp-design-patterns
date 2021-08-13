#include <iostream>

class Car
{
public:
    // Template method
    std::string getCarName()
    {
        return this->getVendorName() + " " + this->getModelName();
    };

protected:
    virtual std::string getVendorName() const = 0;
    virtual std::string getModelName() const = 0;
};

class MINICooperConvertible : public Car
{
    protected:
        std::string getVendorName() const
        {
            return "MINI Cooper";
        };
        
        std::string getModelName() const
        {
            return "Convertible";
        }
};

class AstonMartinDB11 : public Car
{
    protected:
        std::string getVendorName() const
        {
            return "Aston Martin";
        };
        
        std::string getModelName() const
        {
            return "DB11";
        }
};

int main() 
{
    std::cout << "Template method pattern demo." << std::endl;

    Car *car1 = new MINICooperConvertible();
    Car *car2 = new AstonMartinDB11();

    std::cout << "Car 1 name -> " + car1->getCarName() << std::endl;
    std::cout << "Car 2 name -> " + car2->getCarName() << std::endl;
    
    return 0;
}
