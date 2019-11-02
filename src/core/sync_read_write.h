#ifndef HUMANITYGENERATIONSIMULATION_SYNC_READ_WRITE_H
#define HUMANITYGENERATIONSIMULATION_SYNC_READ_WRITE_H

#include <iostream>
#include <filesystem>

class sync_read_write {
public:
    sync_read_write();
    void wait_for_write_access();
    void close_write_access();
    void wait_for_read_access();
    void close_read_access();

private:
    void create_write_file();
    void create_read_file();

    std::filesystem::path read_file_name;
    std::filesystem::path write_file_name;
};


#endif //HUMANITYGENERATIONSIMULATION_SYNC_READ_WRITE_H
