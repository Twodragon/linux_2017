cmake_minimum_required(VERSION 3.10)
project(FS_Client C)

set(CMAKE_C_STANDARD 99)

add_executable(FS_Client main_client.c Client.h Client.c Network_utils.h Network_utils.c)