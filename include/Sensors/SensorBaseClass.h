class SensorBaseClass {
    private: 
        int _receivePin; // underscore used to differentiate private from public variables
        int _transmitPin;

    public:
        SensorBaseClass(int receivePin, int transmitPin);
        ~SensorBaseClass(); // NO IMPLEMENTATION destructor function, called when object is destroyed 

        void setReceivePin(int receivePin);
        void setTransmitPin(int transmitPin);
};

