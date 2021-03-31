#include <iostream>

typedef std::string JSONMessage;
typedef std::string XMLMessage;
typedef std::string TextMessage;

class IMessageParser {
    public:
        virtual ~IMessageParser() {};
        virtual void parseMessage(std::string message) = 0;
};

class JSONMessageParser: public IMessageParser {
    public: 
        void parseMessage(JSONMessage message) {
            std::cout << message + " is parsed as JSON." << std::endl;
        }
};

class XMLMessageParser: public IMessageParser {
    public: 
        void parseMessage(XMLMessage message) {
            std::cout << message + " is parsed as XML." << std::endl;
        }
};

/*
*   This is a message parsing interface that is NOT compatible with the IMessageParser interface.
*/
class IAppMessageParser {
    public:
        virtual void parse(std::string msg) = 0;
};

class TextMessageParser: public IAppMessageParser {
    public:
        void parse(TextMessage msg) {
            std::cout << msg + " -> text parsed." << std::endl;
        }
};

/*
* Let's make compatible the IAppMessageParser and the IMessageParser interfaces. 
*/

class AppMessageParserAdapter: public IMessageParser {
    public:
        AppMessageParserAdapter(IAppMessageParser *appMessageParser) {
            this->m_appMessageParser = appMessageParser;
        }

        ~AppMessageParserAdapter() {
            if (m_appMessageParser) 
            {
                delete m_appMessageParser;
            }
        }
        
        void parseMessage(XMLMessage message) {
            if (m_appMessageParser) 
            {
                m_appMessageParser->parse(message);
            }
        }   
    private:
        IAppMessageParser *m_appMessageParser;      
};


int main() {
    IMessageParser *myJSONParser = new JSONMessageParser();
    IMessageParser *myXMLParser = new XMLMessageParser(); 
    IMessageParser *myTextParser = new AppMessageParserAdapter(new TextMessageParser());

    myJSONParser->parseMessage("Sample JSON Message");
    myXMLParser->parseMessage("Sample XML Message");
    myTextParser->parseMessage("Sample Text Message");

    delete myJSONParser;
    delete myXMLParser;
    delete myTextParser;

    return 0;
};
