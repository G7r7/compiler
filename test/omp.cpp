#include <omp.h>
#include <iostream>
#include "omp.hpp"  
#include "test.hpp"
#include <thread>
#include <chrono> 

void testProgramsOmp(std::vector<std::string>* filePaths, std::string* compilerPath, std::string* machinePath, std::ofstream* outputFile) {
    for (int i = 0; i < filePaths->size(); i++) {
        double start = 0; 
        double end = 0;
        int finished = 0;
        TestArgs args = { 
            compilerPath,
            &filePaths->at(i),
            machinePath,
            outputFile,
            &finished
        };
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                {
                    start = omp_get_wtime();
                    testProgram(&args);
                    end = omp_get_wtime(); 
                }
                #pragma omp section
                {
                    for (size_t i = 0; i < 10; i++)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));                        
                        if(end != 0) {
                            printf("Work took %f seconds\n", end - start);
                            break;
                        }
                        else
                            printf("Waiting ...\n");
                    }
                    if(end == 0) {
                        outputFile->close();
                        printf("Timed out : please kill remaining msm instance manually...\n");
                    }
                }
            
            }
        }
    }
}