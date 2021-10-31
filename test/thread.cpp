#include "thread.hpp"
#include <pthread.h>
#include <thread>
#include "test.hpp"

void testProgramsThread(std::vector<std::string>* filePaths, std::string* compilerPath, std::string* machinePath, std::ofstream* outputFile) {
    pthread_t pt[filePaths->size()];
    for (int i = 0; i < filePaths->size(); i++) {
        int finished = 0;
        TestArgs args = { 
            compilerPath,
            &filePaths->at(i),
            machinePath,
            outputFile,
            &finished
        };
        pthread_create(&pt[i], NULL, testProgram, (void*)&args);
        for (size_t i = 0; i < 10; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));                        
            if(finished) {
                printf("Work is done!\n");
                break;
            }
            else
                printf("Waiting ...\n");
        }
        if(!finished) {
            printf("Timed out : please kill remaining msm instance manually...\n");
        }
    }
}   