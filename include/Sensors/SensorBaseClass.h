class SensorBaseClass {
    private: 
        const int _receivePin; // underscore used to differentiate private from public variables
        const int _transmitPin;
        const int _baudRate;

    public:
        SensorBaseClass(int receivePin, int transmitPin, int baudRate) : 
        _receivePin(receivePin), _transmitPin(transmitPin), _baudRate(baudRate) {
        }

        // having a virtual destructor is not necessary, but a good practice for base classes
        virtual ~SensorBaseClass(); 

        int getReceivePin();
        int getTransmitPin();
        int getBaudRate();

        // pure virtual function, must be implemented by derived classes
        virtual void debugPrintData() = 0;
};

