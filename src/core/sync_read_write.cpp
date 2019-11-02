#include "sync_read_write.h"
#include <fstream>
#include <filesystem>
#include <thread>

sync_read_write::sync_read_write()
        : write_file_name("write"), read_file_name("read") {
}

void sync_read_write::wait_for_write_access() {
    while (std::filesystem::exists(read_file_name)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    create_write_file();
}

void sync_read_write::wait_for_read_access() {
    while (std::filesystem::exists(write_file_name)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    create_read_file();
}

void sync_read_write::close_write_access() {
    create_read_file(); // Force changing the turn to read
    std::filesystem::remove(write_file_name);
}

void sync_read_write::close_read_access() {
    create_write_file(); // Force changing the turn to write
    std::filesystem::remove(read_file_name);
}

void sync_read_write::create_write_file() {
    std::ofstream outfile(write_file_name);
    outfile << "write-protect" << std::endl;
    outfile.close();
}

void sync_read_write::create_read_file() {
    std::ofstream outfile(read_file_name);
    outfile << "read-protect" << std::endl;
    outfile.close();
}