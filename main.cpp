
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define READ 0
#define WRITE 1
struct ProcessInfo {
    int input, output;
};


pid_t
popen2(const std::string modulName, const char *command, int *infp, int *outfp) {
    int p_stdin[2], p_stdout[2];
    pid_t pid;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0)
        return -1;

    pid = fork();

    if (pid < 0)
        return pid;
    else if (pid == 0) {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], READ);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);

        execl(modulName.c_str(), "sh", "-c", command, NULL);
        perror("execl");
        exit(1);
    }

    if (infp == NULL)
        close(p_stdin[WRITE]);
    else
        *infp = p_stdin[WRITE];

    if (outfp == NULL)
        close(p_stdout[READ]);
    else
        *outfp = p_stdout[READ];

    return pid;
}

std::string CalculateProcess(std::string ModuleName, std::string data) {
    int infp, outfp;
    char buf[128]="";

    if (popen2(ModuleName, "sort", &infp, &outfp) <= 0) {
        std::cout << "Unable to exec sort\n";
        exit(1);
    }
    write(infp, data.c_str(), data.size());
    close(infp);
    std::cout << "Translate data: " << data << std::endl;
    read(outfp, buf, 128);

    std::cout << "Data read: " << buf << std::endl;

    return std::string(buf);
}

int main() {
    CalculateProcess("../S/cmake-build-debug/S", CalculateProcess("../P/cmake-build-debug/P",
                                                                  CalculateProcess(
                                                                          "../A/cmake-build-debug/A",
                                                                          CalculateProcess(
                                                                                  "../M/cmake-build-debug/M",
                                                                                  "1 2 4 5 12 "))));
    return 0;
}