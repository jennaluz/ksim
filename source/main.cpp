/*
 * source/main.cpp
 *
 *
 */

#include <iostream>
#include <string>   //std::string
#include <vector>   //std::vector   .size()

#include "../header/dispatcher.h"
#include "../header/get_input.h"
#include "../header/tokenize.h"

int main()
{
    Dispatcher_t ksim;
    int ticks = 0;                          //total number of kernel ticks
    std::string buffer = "";                //user commands
    std::vector<std::string> bufferArgv;    //tokenized user commands
    int bufferArgc = 0;                     //amount of user commands

    std::string opcodes[7] {
        "exit",
        "add",
        "step",
        "wait",
        "io-event",
        "query",
        "release"
    };

    while (1) {
        get_input(ticks, buffer);

        tokenize(buffer, bufferArgv, bufferArgc);

        std::string opcode = bufferArgv[0];
        int idxOpcodes = -1;

        for (int i = 0; i < 7; i++) {
            if (opcode == opcodes[i]) {
                idxOpcodes = i;
                break;
            }
        }

        switch (idxOpcodes) {
        case 0:     //exit
            if (bufferArgc > 1) {
                std::cout << "Opcode \"exit\" requires no operands." << std::endl;
                break;
            }

            bufferArgv.clear();
            return 0;
        case 1:     //add
            if (bufferArgc != 2) {
                std::cout << "Opcode \"add\" requires 1 operand." << std::endl;
                break;
            }

            ticks += ksim.add(ticks, bufferArgv[1]);
            break;
        case 2:     //step
            if (bufferArgc > 1) {
                std::cout << "Opcode \"step\" requires no operands." << std::endl;
                break;
            }

            ticks += ksim.step(ticks);
            break;
        case 3:     //wait
            if (bufferArgc != 2) {
                std::cout << "Opcode \"wait\" requires 1 operand." << std::endl;
                break;
            }

            ticks += ksim.wait(ticks, bufferArgv[1]);
            break;
        case 4:     //io-event
            if (bufferArgc != 2) {
                std::cout << "Opcode \"io-event\" requires 1 operand." << std::endl;
                break;
            }

            ticks += ksim.io_event(bufferArgv[1]);
            break;
        case 5:     //query
            if (bufferArgc != 2) {
                std::cout << "Opcode \"query\" requires 1 operand." << std::endl;
                break;
            }

            ticks += ksim.query(bufferArgv[1]);
            break;
        case 6:     //release
            if (bufferArgc > 1) {
                std::cout << "Opcode \"release\" requires no operands." << std::endl;
                break;
            }

            ticks += ksim.release(ticks);
            break;
        default:    //invalid
            std::cout << "\"" << opcode << "\" is an invalid opcode." << std::endl;
        }

        bufferArgv.clear();
    }
}