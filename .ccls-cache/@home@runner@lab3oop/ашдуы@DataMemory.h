#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <map>
#include <string>

class DataMemory {
private:
    std::map<std::string, int> dataStorage;
    std::map<int, bool> addressLocks;
public:
    void storeData(const std::string& identifier, int data);
    int retrieveData(const std::string& identifier);
    bool isAddressLocked(int address);
    void setAddressLock(int address, bool locked);
};

#endif // DATAMEMORY_H