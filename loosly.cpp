#include <iostream>
#include <random> 
#include <string>
using namespace std;

class ICloudCommunicator {
public:
    virtual int pushMessage(string message) = 0; 
};
class IOTCloudCommunicator: public ICloudCommunicator{
    public:
          int  pushMessage(string message){
              //Interact with internet and push the message to MessageQueue
            //if communiction succesfull return value from ramge {200 -400} status code otherwise returns errocode (400 - 500)
              std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distr(200, 500);
                return distr(gen);
            
          }

};
class IBNFSpeedSensor {
public:
    virtual int getCurrentSpeed() = 0; 
};
class BNFSpeedSensor:public IBNFSpeedSensor{
        public:
            int   getCurrentSpeed(){
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distr(1, 100);
                return distr(gen);
            }
};

class SpeedMonitor{
    private : 
    int _speedThreshold;
    IBNFSpeedSensor* _speedSensor;        
    ICloudCommunicator* _cloudComm;
  
      public:
      SpeedMonitor(int speedThreshold, IBNFSpeedSensor* speedSensor, ICloudCommunicator* cloudComm)
        : _speedThreshold{speedThreshold}, _speedSensor{speedSensor}, _cloudComm{cloudComm} {}
          void monitor(){
            if(_speedThreshold  < 1 || _speedThreshold > 100){
              cout<<"_speedThreshold value must be in the ramge {1-100} "<<_speedThreshold<<endl;
            }
              
            BNFSpeedSensor speedSensorInstance;
            IOTCloudCommunicator cloudCommuniccator;
            int currentSpeedInKmph=speedSensorInstance.getCurrentSpeed();
            
            cout<<"Current Speed In Kmph "<<currentSpeedInKmph<<endl;
            if(currentSpeedInKmph > _speedThreshold){
                  double mph = currentSpeedInKmph * 0.621371;
                  string message="Current Speed in Miles "+ to_string(mph);
                 int statusCode= cloudCommuniccator.pushMessage(message);
                  if(statusCode > 400){
                      //Log Message to Console
                       cout<<"Error In Communication Unable to Contact Server "<<message<< endl;
                  }
                 
            }
              
          }
};

void release(){
  BNFSpeedSensor _sensor;
  IOTCloudCommunicator _cloud;
  SpeedMonitor instance {10,&_sensor, &_cloud};
  instance.monitor();
    
}
class MockIBNFSpeedSensor:public IBNFSpeedSensor{
    public:
    int currentspeed=0;
    int   getCurrentSpeed(){
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distr(1, 100);
                return distr(gen);
            }
    
};
class MockICloudCommunicator:public ICloudCommunicator{
    public:
    int   pushMessage(string message){
        std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distr(200, 500);
                return distr(gen);
            }
    
};
void test(){
    
    MockIBNFSpeedSensor _speedSensor;        
    MockICloudCommunicator _cloudComm;
    SpeedMonitor instance {10,&_speedSensor, &_cloudComm};
  instance.monitor();
    
}
int main(){
    test();	
}
