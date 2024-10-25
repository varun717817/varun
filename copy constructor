// Online C++ compiler to run C++ program online
#include <iostream>
class B{
    int _state;
    public:
     void setState(int state ){
         this->_state=state;
     }
     int getState(){ return this->_state;}
};
class A{
    B bInstance;
    public :
    A(int state){
        this->bInstance.setState(state);
    }
    int getState(){
        return this->bInstance.getState();
    }
    void setState(int newValue){ this->bInstance.setState(newValue);}
};
int main() {
    // Write C++ code here
    A aInstance{ 100};
    std::cout <<aInstance.getState()<<std::endl;
    
    A newInstance(aInstance);//Copy Constructor
    std::cout <<newInstance.getState()<<std::endl;
    newInstance.setState(500);
    std::cout <<"aInstance"<<aInstance.getState()<<std::endl;
    std::cout <<"newInstance"<<newInstance.getState()<<std::endl;
    return 0;
}
