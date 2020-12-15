#include <iostream>
#include <sstream>

class TV {
    public:
        TV() {};
        virtual ~TV() {};
        virtual std::string getDescription() = 0; 
        virtual int getPrice() = 0;
}; 

class Board1TV : public TV {
    public:
        Board1TV() {};
        ~Board1TV() {};
        
        std::string getDescription() 
        {
            return "Board 1 TV";
        };

        int getPrice() 
        {
            return 500;
        };
};

class TVDecorator : public TV {
    public:
        TVDecorator(TV* tv) 
        {
            this->m_TV = tv;
        };
        
        virtual ~TVDecorator() 
        {
            if (this->m_TV)
            {
                delete this->m_TV;
            }
        };

        virtual std::string getDescription() = 0; 
        virtual int getPrice() = 0;
    protected:
        TV *m_TV; 
};

class AddYouTube : public TVDecorator {
    public: 
        AddYouTube(TV* tv):TVDecorator(tv) {};

        std::string getDescription() 
        {
            return this->m_TV->getDescription() + ", with YouTube";
        }
        
        int getPrice() 
        {
            return this->m_TV->getPrice() + 100;
        };
};

class AddNetflix : public TVDecorator {
    public: 
        AddNetflix(TV* tv):TVDecorator(tv) {};

        std::string getDescription() 
        {
            return this->m_TV->getDescription() + ", with Netflix";
        }

        int getPrice() 
        {
            return this->m_TV->getPrice() + 80;
        };
};

int main() {
    TV *tv = new Board1TV();
    tv = new AddYouTube(tv);
    tv = new AddNetflix(tv);

    std::cout << "My TV Description -> " + tv->getDescription() << std::endl;
    
    std::ostringstream ss;
    ss << tv->getPrice(); 
    std::cout << "My TV Price -> " + ss.str() << std::endl;
    
    delete tv;

    return 0;
};
