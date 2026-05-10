// _write
// _read
// _sbrk
// _close
// _fstat
// _isatty
// _lseek
// _exit

#include <cerrno>
#include <cstddef>
#include <sys/stat.h>
#include <sys/types.h>

enum class SyscallNum : long {
    Read = 0,
    Write = 3,
    Sbrk = 12,
    Close = 57,
    Fstat = 80,
    Isatty = 89,
    Lseek = 62,
    Exit = 93,
};

extern "C" long __syscall3(long num, long arg0, long arg1, long arg2);

static int ret_to_errno(long ret) {
    if (ret < 0) {
        errno = static_cast<int>(-ret);
        return -1;
    }

    return static_cast<int>(ret);
}

extern "C" int _write(int fd, const void* buf, size_t nbyte) {
    long ret = __syscall3(
        static_cast<long>(SyscallNum::Write),
        static_cast<long>(fd),
        reinterpret_cast<long>(buf),
        static_cast<long>(nbyte));

    return ret_to_errno(ret);
}

extern "C" int _read(int fd, void* buf, size_t count) {
    long ret = __syscall3(
        static_cast<long>(SyscallNum::Read),
        static_cast<long>(fd),
        reinterpret_cast<long>(buf),
        static_cast<long>(count));

    return ret_to_errno(ret);
}