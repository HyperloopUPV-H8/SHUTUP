#include "PCANBasic.h"
#include "TCPServer.hpp"
#include "pcan.hpp"
#include <signal.h>
#include <chrono>
#include <thread>

PCAN* pcan;
TCPServer* tcp;
thread can_thread, tcp_thread;

const int FREQ = 50;

TCPMessage pwm;
TCPMessage tcp_response;

CANMessage write_analog(88, 5);
CANMessage cancel_streams(90, 2);
CANMessage read_ic_once(81, 1);
CANMessage stream_ic(84, 3);
CANMessage can_response;

bool run_threads = true;

using namespace std;

int INDEX_ = 0;
long long total_count = 0;

void read_tcp(){
    auto t1 = chrono::system_clock::now();
    auto t2 = chrono::system_clock::now();
    long long count = 0;

    while(run_threads){
        int result = tcp->ReadMessage(&tcp_response);

        if(result > 0) {
            float airgap  = (float) *((double*) &tcp_response.data[0]);
            float current = (float) *((double*) &tcp_response.data[8]);
            
            write_analog.data[0] = 80;
            *((float*) &write_analog.data[1]) = airgap;
            //pcan->WriteMessageFD(&write_analog);

            write_analog.data[0] = 81;
            *((float*) &write_analog.data[1]) = current;
            //pcan->WriteMessageFD(&write_analog);

            // TIMED INFORMATION
            t2  = chrono::system_clock::now();
            chrono::duration<double> t3 = (t2 - t1);
            double seconds_ellapsed = t3.count();
            if(seconds_ellapsed > 1.0){
                t1 = chrono::system_clock::now();
                printf("TCP STATE -> AIRGAP: %f | CURRENT : %f | Freq: %d \n", airgap, current, count);
                count = 0;
            }
            count+=1;
            total_count += 1;
        }
    }
}


void read_can() {
    auto t1 = chrono::system_clock::now();
    auto t2 = chrono::system_clock::now();
    long long count = 0;

    while (run_threads) {
        TPCANStatus result = pcan->ReadMessageFD(&can_response);
        if(true){
            uint8_t result = *((uint8_t*) &can_response.data[0]);
            double res =  result / 255.0 * 100;
            *((double*) &pwm.data[0]) = res;
            pwm.length = 8;

            // TIMED INFORMATION
            t2 = chrono::system_clock::now();
            chrono::duration<double> t3 = (t2 - t1);
            double seconds_ellapsed = t3.count();
            if(seconds_ellapsed > 1.0){
                //int tcp_res = tcp->WriteMessage(&pwm);
                t1 = chrono::system_clock::now();
                int can_freq = count / seconds_ellapsed;
                printf("CAN STATE -> PWM: %f | Freq: %d \n", res, can_freq);
                count = 0;
            }
        }
        count += 1;
    }
}

void signal_handler(int signnum){
    printf("EXIT %d \n", signnum);
    printf("Total count -> %d\n", total_count);
    run_threads = false;
    cancel_streams.data[0] = 255;
    cancel_streams.data[1] = 255;
    pcan->WriteMessageFD(&cancel_streams);
    sleep(1);
    exit(signnum);
}

int main() { 
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);

    //pcan = new PCAN();
    tcp = new TCPServer(6969);

    //cancel_streams.data[0] = 255;
    //cancel_streams.data[1] = 255;
    //pcan->WriteMessageFD(&cancel_streams);

    //read_ic_once.data[0] = 1;
    //printf("Main -> aiting for PA1\n");
    //pcan->WriteMessageFD(&read_ic_once);
    //float result = *((float*) &can_response.data[0]);
    //printf("Main -> PA1: %f", result);

    //stream_ic.data[0] = 1;
    //*((uint16_t*) &stream_ic.data[1]) = FREQ;
    //pcan->send_and_wait(&stream_ic, &can_response);

    //can_thread = thread(read_can);
    tcp_thread  = thread(read_tcp);

    //can_thread.join();
    tcp_thread.join();
}