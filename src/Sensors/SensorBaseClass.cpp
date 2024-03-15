class SensorBaseClass {
    
    private: 
        int _receivePin = 0; // underscore used to differentiate private from public variables
        int _transmitPin = 0;


    public:

        SensorBaseClass(int receivePin, int transmitPin) {
            _receivePin = receivePin;
            _transmitPin = transmitPin;
        }

        void SensorBaseClass::setReceivePin(int receivePin) {
            _receivePin = receivePin;
        }

        void SensorBaseClass::setTransmitPin(int transmitPin) {
            _transmitPin = transmitPin;
        }
};