/*
 * OpenBalls, v1.0.0
 * (headers)
 *
 * This file is part of OpenBalls.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright (C) 2017 github@suqiernb<suqiernb@qq.com>
 * Copyright (C) 2023 OpenBalls Contributors
 */
 //两种杀GG(推荐第2个)
 

 
#pragma once

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <functional>
#include <tuple>
#include <vector>

// defined macro
#ifndef OPEN_BALLS
#define OPEN_BALLS
#define RUST_TYPE
#define WIDE_TYPE
#define OPEN_BALLS_API
#define OPEN_BALLS_IMPL
#define OPEN_BALLS_VERSION "1.0.0"
#define OPEN_BALLS_VERSION_NUM 1
#endif//OPEN_BALLS

// rust types
RUST_TYPE typedef int8_t i8;
RUST_TYPE typedef int16_t i16;
RUST_TYPE typedef int32_t i32;
RUST_TYPE typedef int64_t i64;
RUST_TYPE typedef uint8_t u8;
RUST_TYPE typedef uint16_t u16;
RUST_TYPE typedef uint32_t u32;
RUST_TYPE typedef uint64_t u64;
RUST_TYPE typedef float f32;
RUST_TYPE typedef double f64;

// wide types
WIDE_TYPE typedef i8 Byte;
WIDE_TYPE typedef i16 Word;
WIDE_TYPE typedef i32 Dword;
WIDE_TYPE typedef i64 Qword;
WIDE_TYPE typedef f32 Float;
WIDE_TYPE typedef f64 Double;
WIDE_TYPE typedef u64 Addr;
WIDE_TYPE typedef void *Ptr;

// block size 4096
#define BLOCK_SIZE 0x1000
#if !defined(BLOCK_SIZE) || (BLOCK_SIZE % 4) != 0
#error "!!! The block size must be a multiple of 4 !!!"
#endif

// maps flags
enum Flags {
    FLAG_NONE = 0,
    FLAG_READ = 1 /*<< 0*/,
    FLAG_WRITE = 1 << 1,
    FLAG_EXEC = 1 << 2,
    FLAG_SHARE = 1 << 3,
    FLAG_PRIVATE = 1 << 4,
};

enum Regions {
    REGION_C_HEAP = 1 /*<< 0*/,
    REGION_JAVA_HEAP = 1 << 1,
    REGION_C_ALLOC = 1 << 2,
    REGION_C_DATA = 1 << 3,
    REGION_C_BSS = 1 << 4,
    REGION_ANONYMOUS = 1 << 5,
    REGION_STACK = 1 << 6,
    REGION_CODE_APP = 1 << 14,
    REGION_CODE_SYS = 1 << 15,
    REGION_JAVA = 1 << 16,
    REGION_BAD = 1 << 17,
    /*REGION_PPSSPP = 1 << 18,*/
    REGION_ASHMEM = 1 << 19,
    REGION_VIDEO = 1 << 20,
    REGION_OTHER = ~(REGION_C_HEAP | REGION_JAVA_HEAP | REGION_C_ALLOC | REGION_C_DATA | \
                REGION_C_BSS | REGION_ANONYMOUS | REGION_STACK | REGION_CODE_APP | \
                REGION_CODE_SYS | REGION_JAVA | REGION_BAD/*|REGION_PPSSPP*/ | \
                REGION_ASHMEM | REGION_VIDEO),
    REGION_ALL = REGION_C_HEAP | REGION_JAVA_HEAP | REGION_C_ALLOC | REGION_C_DATA | \
                REGION_C_BSS | REGION_ANONYMOUS | REGION_STACK | REGION_CODE_APP | \
                REGION_CODE_SYS | REGION_JAVA | REGION_BAD/*|REGION_PPSSPP*/ | \
                REGION_ASHMEM | REGION_VIDEO | REGION_OTHER,
};

// maps
struct Smap {
    Addr start_addr;
    Addr end_addr;
    u8 flags;
    char name[256];

    Smap() { reset(); }

    u32 size() const {
        return end_addr - start_addr;
    }

    void parse(const char *map) {
        char _flags[8];
        sscanf(map, "%p-%p %s %*s %*s %*s %s", (Ptr *) &start_addr, (Ptr *) &end_addr, _flags, name);
        flags = FLAG_NONE;
        if (_flags[0] == 'r') flags |= FLAG_READ;
        if (_flags[1] == 'w') flags |= FLAG_WRITE;
        if (_flags[2] == 'x') flags |= FLAG_EXEC;
        if (_flags[3] == 's') flags |= FLAG_SHARE;
        if (_flags[3] == 'p') flags |= FLAG_PRIVATE;
    }

    Regions region() const {
        if (strlen(name) == 0)
            return REGION_ANONYMOUS;
        if (strstr(name, "/dev/asheme/") != nullptr)
            return REGION_ASHMEM;
        if (strstr(name, "/system/fonts/") != nullptr)
            return REGION_BAD;
        if (strstr(name, ".so") != nullptr && (flags & (FLAG_READ | FLAG_EXEC | FLAG_PRIVATE)) == (FLAG_READ | FLAG_EXEC | FLAG_PRIVATE))
            return (strstr(name, "/data/app/") == nullptr && strstr(name, "/data/data/") == nullptr) ? REGION_CODE_SYS : REGION_CODE_APP;
        if (strstr(name, "[anon:libc_malloc") != nullptr || strstr(name, "[anon:scudo:") != nullptr)
            return REGION_C_ALLOC;
        if (strstr(name, "[anon:.bss") != nullptr)
            return REGION_C_BSS;
        if (strstr(name, "/data/app/") != nullptr && strstr(name, ".so") != nullptr)
            return REGION_C_DATA;
        if (strstr(name, "[heap]") != nullptr)
            return REGION_C_HEAP;
        if (strstr(name, "dalvik-allocation") != nullptr || strstr(name, "dalvik-main") != nullptr || \
            strstr(name, "dalvik-large") != nullptr || strstr(name, "dalvik-free") != nullptr)
            return REGION_JAVA_HEAP;
        if (strstr(name, "dalvik-CompilerMetadata") != nullptr || strstr(name, "dalvik-LinearAlloc") != nullptr || \
            strstr(name, "dalvik-indirect") != nullptr || strstr(name, "dalvik-rosalloc") != nullptr || \
            strstr(name, "dalvik-card") != nullptr || strstr(name, "dalvik-mark") != nullptr || \
            (strstr(name, "dalvik-") != nullptr && strstr(name, "space") != nullptr))
            return REGION_JAVA;
        if (strstr(name, "[stack") != nullptr)
            return REGION_STACK;
        if (strstr(name, "/dev/kgsl-3d0") != nullptr)
            return REGION_VIDEO;
        return REGION_OTHER;
    }

    void reset() {
        start_addr = end_addr = 0;
        flags = FLAG_NONE;
        name[0] = '\0';
    }
};

/**
 * 获取进程的ID
 * @param processName 进程名
 * @return 成功返回进程ID, 失败返回 0
 */
OPEN_BALLS_API u32 ballsGetProcessId(const char *processName);

/**
 * 获取指定进程的内存映射
 * @param pid 进程ID
 * @param filter 过滤器
 * <p> /// #return <bool, bool>(是否匹配, 是否继续)
 * <p> std::tuple<bool, bool> filter(const Smap &map)
 * <p> {
 * <p>     return std::make_tuple(true, true);
 * <p> }
 * @return 内存映射表
 */
OPEN_BALLS_API std::vector<Smap> ballsGetMaps(u32 pid, std::function<std::tuple<bool, bool>(const Smap &map)> filter);

/**
 * 获取指定进程的内存映射
 * @param pid 进程ID
 * @param regions 内存范围
 * @return 内存映射表
 */
OPEN_BALLS_API std::vector<Smap> ballsGetMaps(u32 pid, u32 regions = REGION_ALL);

/**
 * 获取指定进程中某个动态库的内存映射
 * @param pid 进程ID
 * @param library 动态库名称
 * @return 内存映射表
 */
OPEN_BALLS_API std::vector<Smap> ballsGetLibraryMaps(u32 pid, const char *library);

/**
 * 读取指定进程中的内存
 * @param pid 进程ID
 * @param address 内存地址
 * @param buffer 数据缓存
 * @param size 缓存大小
 * @return 成功读取的字节数
 */
OPEN_BALLS_API u32 ballsRead(u32 pid, Addr address, Ptr buffer, u32 size);

/**
 * 向指定进程中写入内存
 * @param pid 进程ID
 * @param address 内存地址
 * @param buffer 数据缓存
 * @param size 缓存大小
 * @return 成功写入的字节数
 */
OPEN_BALLS_API u32 ballsWrite(u32 pid, Addr address, const Ptr buffer, u32 size);

/**
 * 读取指定进程中的内存(readv)
 * @param pid 进程ID
 * @param address 内存地址
 * @param buffer 数据缓存
 * @param size 缓存大小
 * @return 成功读取的字节数
 */
OPEN_BALLS_API u32 ballsReadv(u32 pid, Addr address, Ptr buffer, u32 size);

/**
 * 向指定进程中写入内存(writev)
 * @param pid 进程ID
 * @param address 内存地址
 * @param buffer 数据缓存
 * @param size 缓存大小
 * @return 成功写入的字节数
 */
OPEN_BALLS_API u32 ballsWritev(u32 pid, Addr address, const Ptr buffer, u32 size);

/**
 * 搜索指定进程中的内存
 * @param pid 进程ID
 * @param maps 内存映射表
 * @param buffer 数据缓存
 * @param size 缓存大小
 * @param vir 是否使用 readv, 默认 true
 * @return 匹配成功的地址列表
 */
OPEN_BALLS_API std::vector<Addr> ballsSearchValue(u32 pid, const std::vector<Smap> &maps, Ptr buffer, u32 size, bool vir = true);

/**
 * 编辑所有内存地址
 * @param pid 进程ID
 * @param address 地址列表
 * @param offset 偏移量
 * @param buffer 数据缓存
 * @param size  缓存大小
 * @param vir  是否使用 writev, 默认 false
 * @return 写入成功的数量
 */
OPEN_BALLS_API int ballsEditValues(u32 pid, const std::vector<Addr> &address, i32 offset, Ptr buffer, u32 size, bool vir = false);

/**
 * 读取指定进程中的内存
 * @tparam T type
 * @param pid 进程ID
 * @param address 内存地址
 * @param defaultValue 读取失败后的返回内容
 * @return value
 */
template<typename T = i32>
OPEN_BALLS_API T ballsRead(u32 pid, Addr address, T defaultValue = -1) {
    T value = defaultValue;
    if (ballsRead(pid, address, &value, sizeof(value)) == sizeof(value))
        return value;
    return defaultValue;
}

/**
 * 向指定进程中写入内存
 * @tparam T type
 * @param pid 进程ID
 * @param address 内存地址
 * @param value 待写入的值
 * @return 是否写入成功
 */
template<typename T>
OPEN_BALLS_API bool ballsWrite(u32 pid, Addr address, T value) {
    return ballsWrite(pid, address, &value, sizeof(value)) == sizeof(value);
}

/**
 * 读取指定进程中的内存(readv)
 * @tparam T type
 * @param pid 进程ID
 * @param address 内存地址
 * @param defaultValue 读取失败后的返回内容
 * @return value
 */
template<typename T = i32>
OPEN_BALLS_API T ballsReadv(u32 pid, Addr address, T defaultValue = -1) {
    T value = defaultValue;
    if (ballsReadv(pid, address, &value, sizeof(value)) == sizeof(value))
        return value;
    return defaultValue;
}

/**
 * 向指定进程中写入内存(writev)
 * @tparam T type
 * @param pid 进程ID
 * @param address 内存地址
 * @param value 待写入的值
 * @return 是否写入成功
 */
template<typename T>
OPEN_BALLS_API bool ballsWritev(u32 pid, Addr address, T value) {
    return ballsWritev(pid, address, &value, sizeof(value)) == sizeof(value);
}

/**
 * 搜索指定进程中的内存
 * @tparam T type
 * @param pid 进程ID
 * @param maps 内存映射表
 * @param value 待搜索的值
 * @param vir 是否使用 readv, 默认 true
 * @return 匹配成功的地址列表
 */
template<typename T>
OPEN_BALLS_API std::vector<Addr> ballsSearchValue(u32 pid, const std::vector<Smap> &maps, T value, bool vir = true) {
    return ballsSearchValue(pid, maps, &value, sizeof(value), vir);
}

/**
 * 偏移比较指定进程中的内存
 * @tparam T type
 * @param pid 进程ID
 * @param address 地址列表
 * @param offset 偏移量
 * @param value 对比值
 * @param vir 是否使用 readv, 默认 true
 * @return 匹配成功的数量
 */
template<typename T>
OPEN_BALLS_API u32 ballsOffsetCompare(u32 pid, std::vector<Addr> &address, i32 offset, T value, bool vir = true) {
    auto _read = vir ? [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsReadv(pid, addr, buffer, size);
    } : [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsRead(pid, addr, buffer, size);
    };
    if (address.empty())
        return 0;
    for (auto it = address.begin(); it != address.end();) {
        T vl = value;
        if (_read(pid, (*it) + offset, &vl, sizeof(value)) == sizeof(value) && vl != value) {
            address.erase(it);
            continue;
        }
        it++;
    }
    return address.size();
}

/**
 * 偏移比较指定进程中的内存
 * @tparam T type
 * @param pid 进程ID
 * @param address 地址列表
 * @param offset 偏移量
 * @param minValue 最小值
 * @param maxValue 最大值
 * @param vir 是否使用 readv, 默认 true
 * @return 匹配成功的数量
 */
template<class T>
OPEN_BALLS_API u32 ballsOffsetCompare(u32 pid, std::vector<Addr> &address, i32 offset, T minValue, T maxValue, bool vir = true) {
    auto _read = vir ? [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsReadv(pid, addr, buffer, size);
    } : [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsRead(pid, addr, buffer, size);
    };
    if (address.empty())
        return 0;
    for (auto it = address.begin(); it != address.end();) {
        T value = minValue;
        if (_read(pid, (*it) + offset, &value, sizeof(minValue)) == sizeof(minValue) && \
            value < minValue || value > maxValue) {
            address.erase(it);
            continue;
        }
        it++;
    }
    return address.size();
}

/**
 * 编辑所有内存地址
 * @tparam T type
 * @param pid 进程ID
 * @param address 地址列表
 * @param offset 偏移量
 * @param value 写入的数据
 * @param vir 是否使用 writev, 默认 false
 * @return 写入成功的数据
 */
template<class T>
OPEN_BALLS_API int ballsEditValues(u32 pid, const std::vector<Addr> &address, i32 offset, T value, bool vir = false) {
    return ballsEditValues(pid, address, offset, &value, sizeof(value), vir);
}


#ifdef OPEN_BALLS_IMPL

OPEN_BALLS_IMPL u32 ballsGetProcessId(const char *processName) {
    u32 pid = 0;
    char filename[32];
    char cmdline[256];
    DIR *dir = opendir("/proc");
    if (dir == nullptr)
        return pid;
    dirent *entry;
    FILE *fp;
    while ((entry = readdir(dir)) != nullptr) {
        u32 id = atoi(entry->d_name);
        if (id != 0) {
            sprintf(filename, "/proc/%d/cmdline", id);
            if ((fp = fopen(filename, "r")) == nullptr)
                continue;
            fgets(cmdline, sizeof(cmdline), fp);
            fclose(fp);
            if (strcmp(processName, cmdline) == 0) {
                pid = id;
                break;
            }
        }
    }
    closedir(dir);
    return pid;
}

OPEN_BALLS_IMPL std::vector<Smap> ballsGetMaps(u32 pid, std::function<std::tuple<bool, bool>(const Smap &map)> filter) {
    std::vector<Smap> maps;
    char filename[32];
    char line[512];
    sprintf(filename, "/proc/%d/maps", pid);
    FILE *fp = fopen(filename, "r");
    if (fp == nullptr)
        return maps;
    while (fgets(line, sizeof(line), fp)) {
        Smap map;
        map.parse(line);
        auto result = filter(map);
        if (std::get<0>(result))
            maps.push_back(map);
        if (!std::get<1>(result))
            break;
    }
    fclose(fp);
    return maps;
}

OPEN_BALLS_IMPL std::vector<Smap> ballsGetMaps(u32 pid, u32 regions) {
    return ballsGetMaps(pid, [&regions](const Smap &map) -> std::tuple<bool, bool> {
        return std::make_tuple((map.region() & regions) != 0, true);
    });
}

OPEN_BALLS_IMPL std::vector<Smap> ballsGetLibraryMaps(u32 pid, const char *library) {
    return ballsGetMaps(pid, [&library](const Smap &map) -> std::tuple<bool, bool> {
        return std::make_tuple(strstr(map.name, library) != nullptr, true);
    });
}

OPEN_BALLS_IMPL u32 ballsRead(u32 pid, Addr address, Ptr buffer, u32 size) {
    char filename[32];
    sprintf(filename, "/proc/%d/mem", pid);
    int fd = open(filename, O_RDONLY);
    if (fd < 1) return 0;
    lseek(fd, 0, SEEK_SET);
    u32 ssize = pread64(fd, buffer, size, address);
    close(fd);
    return ssize;
}

OPEN_BALLS_IMPL u32 ballsWrite(u32 pid, Addr address, const Ptr buffer, u32 size) {
    char filename[32];
    sprintf(filename, "/proc/%d/mem", pid);
    int fd = open(filename, O_WRONLY);
    if (fd < 1) return 0;
    lseek(fd, 0, SEEK_SET);
    u32 ssize = pwrite64(fd, buffer, size, address);
    close(fd);
    return ssize;
}

OPEN_BALLS_IMPL u32 ballsReadv(u32 pid, Addr address, Ptr buffer, u32 size) {
    iovec buff, off;
    buff.iov_base = buffer;
    buff.iov_len = size;
    off.iov_base = (Ptr) address;
    off.iov_len = size;
    return syscall(SYS_process_vm_readv, pid, &buff, 1, &off, 1, 0);
}

OPEN_BALLS_IMPL u32 ballsWritev(u32 pid, Addr address, const Ptr buffer, u32 size) {
    iovec buff, off;
    buff.iov_base = buffer;
    buff.iov_len = size;
    off.iov_base = (Ptr) address;
    off.iov_len = size;
    return syscall(SYS_process_vm_writev, pid, &buff, 1, &off, 1, 0);
}

OPEN_BALLS_IMPL std::vector<Addr> ballsSearchValue(u32 pid, const std::vector<Smap> &maps, Ptr buffer, u32 size, bool vir) {
    std::vector<Addr> result;
    u8 block[BLOCK_SIZE];
    auto _read = vir ? [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsReadv(pid, addr, buffer, size);
    } : [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsRead(pid, addr, buffer, size);
    };
    for (const Smap map: maps) {
        Addr tag = map.size() % BLOCK_SIZE == 0 ? map.end_addr : map.end_addr - BLOCK_SIZE;
        for (Addr addr = map.start_addr; addr < tag; addr += BLOCK_SIZE)
            if (_read(pid, addr, block, BLOCK_SIZE) == BLOCK_SIZE)
                for (int i = 0; i < BLOCK_SIZE; i += size)
                    if (memcmp(block + i, buffer, size) == 0)
                        result.push_back(addr + i);
    }
    return result;
}


OPEN_BALLS_IMPL int ballsEditValues(u32 pid, const std::vector<Addr> &address, i32 offset, Ptr buffer, u32 size, bool vir) {
    auto _write = vir ? [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsWritev(pid, addr, buffer, size);
    } : [](u32 pid, Addr addr, Ptr buffer, u32 size) -> u32 {
        return ballsWrite(pid, addr, buffer, size);
    };
    u32 count = 0;
    for (Addr addr: address) {
        if (_write(pid, addr + offset, buffer, size) == size)
            count++;
    }
    return count;
}



#endif//OPEN_BALLS_IMPL


