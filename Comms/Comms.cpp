#include <Comms.h>

Comms::Comms(uint8_t rx, uint8_t tx) : _serial(rx, tx)
{    
    _serial.begin(9600);
}

void Comms::SendMessage(MessageHeader* message)
{   
    byte *p = (byte*)message;
    byte *end = p+message->length;
    while(p < end)
    {
        _serial.write(*p);
        Serial.println(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    if(_serial.available()>0)
    {
        if(!gotLength)
        {
            pRecieve=(byte*)message;
            *pRecieve=_serial.read();
            
            Serial.println(*pRecieve);            
            gotLength=true;
            if(*pRecieve>MaxLength)
            {
                checkFormat();
            }
            endRecieve=pRecieve+(message->length);
            pRecieve++;
        }
        else if(skip)
        {
            _serial.read();
        }
        else
        {
            *pRecieve = _serial.read();
            Serial.println(*pRecieve);            
            pRecieve++;
        }
    }
    if(pRecieve==endRecieve)
    {        
        gotLength=false;        
        return true;
    }
    return false;
}

void Comms::PollMessage() {

    if(ReceiveMessage(&MainMessage))
    {        
        this->DispatchMessage(&MainMessage);
    }
    delay(1000);
}
void checkFormat()
{
    length=_serial.read();
    if((length<7&&length>3)||length==2)
    {
        byte type=_serial.read();
        if(type%2==0&&type<=10&&type>=1)
        {
            
        }
    }
}
