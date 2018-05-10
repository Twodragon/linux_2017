cmake_minimum_required(VERSION 2.6)
project(FS C)

set(CMAKE_C_STANDARD 99)

add_executable(FS main_server.c superblock.h inode.h FileSystem.h FileSystem.c superblock.c inode.c block.h block.c
        Network_utils.h Network_utils.c Client.h Client.c Server.h Server.c)
