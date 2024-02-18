 //to compile, execute 'g++ -I/usr/include/libserial testing_serial.cpp -lserial -o testing_serial' in the shell 

#include </usr/include/libserial/SerialPort.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

constexpr const char* const SERIAL_PORT_2 = "/dev/ttyACM0" ;
void soloWrite(char addr, char cmd, int data){
 
    char initiator = 0xFF;
    char address = addr;
    char command = cmd;
   
    char* bytes = reinterpret_cast<char*>(&hexValue);
 
    char data0 = bytes[0];
    char data1 = bytes[1];
    char data2 = bytes[2];
    char data3 = bytes[3];
    
    char crc = 0x00;
    char ending = 0xFE;
        
    char data_byte[] = {initiator, initiator, address, command, data0, data1, data2, data3, crc, ending};
    
    serial_port.WriteByte(data_byte[0]);
    serial_port.DrainWriteBuffer();
     
    serial_port.WriteByte(data_byte[1]); 
    serial_port.DrainWriteBuffer() ;
        
    serial_port.WriteByte(data_byte[2]);
    serial_port.DrainWriteBuffer() ;
     
    serial_port.WriteByte(data_byte[3]);
    serial_port.DrainWriteBuffer() ;    

    serial_port.WriteByte(data_byte[4]);
    serial_port.DrainWriteBuffer() ;
        
    serial_port.WriteByte(data_byte[5]);
    serial_port.DrainWriteBuffer() ;
        
    serial_port.WriteByte(data_byte[6]);
    serial_port.DrainWriteBuffer() ;
        
    serial_port.WriteByte(data_byte[7]);
    serial_port.DrainWriteBuffer() ;
             
    serial_port.WriteByte(data_byte[8]);
    serial_port.DrainWriteBuffer() ;
     
    serial_port.WriteByte(data_byte[9]);
    serial_port.DrainWriteBuffer() ;
 
}

boolean initSolo(){
   using namespace LibSerial;
    SerialPort serial_port;
 
    try
    {
        serial_port.Open(SERIAL_PORT_2) ;
    }
    catch (const OpenFailed&)
    {
        std::cerr << "The serial port did not open correctly." << std::endl ;
        return EXIT_FAILURE ;
    }
 
    serial_port.FlushIOBuffers();
    serial_port.FlushInputBuffer();
    serial_port.FlushOutputBuffer();

    serial_port.SetBaudRate(BaudRate::BAUD_115200) ;
    serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8) ;
    serial_port.SetFlowControl(FlowControl::FLOW_CONTROL_NONE) ;
    serial_port.SetParity(Parity::PARITY_NONE) ; 
    serial_port.SetStopBits(StopBits::STOP_BITS_1) ;

    std::ofstream outputFile("serial_log.txt");

    std::this_thread::sleep_for(std::chrono::seconds(1));
 
}
int main()
{   
    

    initSolo();
    soloWrite();

    std::string reading;
 
    serial_port.Read(reading, 10, 5000);

    std::stringstream ss;
    ss << reading;
    std::cout << ss.str() << std::endl;
    
    outputFile << ss.str();
    outputFile.close();
    serial_port.Close();
 
    return EXIT_SUCCESS ;
}
