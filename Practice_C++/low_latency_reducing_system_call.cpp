#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/mman.h>

using namespace std;

int main()
{
    const char* file_path = "market_data_sample.txt";
    int fd = open(file_path, O_RDONLY);

    if(fd == -1)
    {
        perror("Error in opening file");
        return 1;
    }

    off_t fileSize = lseek(fd, 0, SEEK_END);

    void* map = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if(map == MAP_FAILED)
    {
        perror("Error Mapping FIle");
        close(fd);
        return 1;
    }

    char* data = static_cast<char*>(map);

    cout << "Accessing the memory-mapped file byte-by-byte:" << endl;
    for (size_t i = 0; i < fileSize; ++i) {
        cout << data[i];
    }
    cout << endl;

    if(munmap(map, fileSize) == -1)
    {
        perror("Error unmapping file");
    }

    close(fd);

    return 0;

}