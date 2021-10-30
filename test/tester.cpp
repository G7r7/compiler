#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "token.hpp"
#include "node.hpp"
#include "usage.hpp"
#include <algorithm>
#include <filesystem>
#include <omp.h>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <signal.h>
#include "test.hpp"

int main(int argc, char const *argv[])
{
    std::fstream inputFile;
    std::fstream outputFile;
    node tree;

    try
    {
        std::vector<token> tokens = getTokens(argc, argv);
        tree = constructCommandTree(&tokens, tokenProgramName);

        std::vector<std::string> options = getOptions();
        std::string machinePath;
        std::string compilerPath;
        std::string testsPath;

        for (size_t i = 0; i < tree.children.size(); i++) {
            node optionFlag = tree.children[i];
            if(optionFlag.value == "-c") {
                compilerPath = optionFlag.children[0].value;
                options.erase(std::remove(options.begin(), options.end(), "-c"), options.end());
            } else if (optionFlag.value == "-m") {
                machinePath = optionFlag.children[0].value;
                options.erase(std::remove(options.begin(), options.end(), "-m"), options.end());
            } else if (optionFlag.value == "-t") {
                testsPath = optionFlag.children[0].value;
                options.erase(std::remove(options.begin(), options.end(), "-t"), options.end());
            } else {
                throw "Unknown option " + optionFlag.value;
            }
        }

        if(options.size()) {
            throw (std::string)"Missing required parameter";
        }

        std::cout << "Program : " << tree.value << std::endl;
        std::cout << "machine path: " << machinePath << std::endl;
        std::cout << "compiler path: " << compilerPath << std::endl;
        std::cout << "tests folder path: " << testsPath << std::endl;

        outputFile.open("log.txt", std::ios_base::app);

        std::vector<std::string> filePaths;
        for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(testsPath)) {
            if(dirEntry.path().extension().compare(".cmm") == 0) {
                filePaths.push_back(dirEntry.path().string());
            }
        }

        pthread_t pt[filePaths.size()];
        for (int i = 0; i < filePaths.size(); i++) {
            int finished = 0;
            printf("Before...\n");
            TestArgs args = { 
                &compilerPath,
                &filePaths[i],
                &machinePath,
                &outputFile,
                &finished
            };
            pthread_create(&pt[i], NULL, testProgram, (void*)&args);
            printf("I'm the timer...\n");
            for (size_t i = 0; i < 10; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));                        
                if(finished) {
                    printf("Work is done!\n");
                    break;
                }
                else
                    printf("I'm still waiting ...\n");
            }
            if(!finished) {
                printf("I'm still waiting and it's time out...\n");
                pthread_kill(pt[i], 10);
            }
        }

        // for (int i = 0; i < filePaths.size(); i++) {
        //     double start = 0; 
        //     double end = 0;
        //     #pragma omp parallel
        //     {
        //         #pragma omp sections nowait
        //         {
        //             #pragma omp section
        //             {
        //                 #pragma omp atomic write
        //                 pt = pthread_self();
        //                 #pragma omp atomic write
        //                 start = omp_get_wtime(); 
        //                 std::cout << filePaths[i] << std::endl;
        //                 std::string compileCommand = compilerPath + " " + filePaths[i] + " " + filePaths[i] + ".out";
        //                 exec(compileCommand.c_str());
        //                 std::string testCommand = machinePath + " " + filePaths[i] + ".out";
        //                 std::string commandResult = exec(testCommand.c_str());
        //                 #pragma omp critical
        //                 outputFile << filePaths[i] << " : " << commandResult << std::endl; 
        //                 #pragma omp atomic write
        //                 end = omp_get_wtime(); 
        //             }
        //             #pragma omp section
        //             {
        //                 printf("I'm the timer...\n");
        //                 for (size_t i = 0; i < 10; i++)
        //                 {
        //                     std::this_thread::sleep_for(std::chrono::milliseconds(100));                        
        //                     if(end != 0) {
        //                         printf("Work is done!\n");
        //                         break;
        //                     }
        //                     else
        //                         printf("I'm still waiting ...\n");
        //                 }
        //                 if(end == 0) {
        //                     printf("I'm still waiting and it's time out...\n");
        //                     pthread_cancel(pt);
        //                 }
        //             }
        //         }
        //     }
        //     printf("Work took %f seconds\n", end - start);
        // }
    }
    catch(std::string msg)
    {
        std::cerr << msg << std::endl;
        std::cerr << usage() << std::endl;
        exit(0);
    }

    // file.open(argv[1]); // Opening output file
    // if(!ofp.is_open()){
    //     perror("Can't open output file");
    //     return EXIT_FAILURE;
    // }

    return 0;
}
