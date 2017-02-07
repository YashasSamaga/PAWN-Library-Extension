/*****************************************************************************************************************
PAWN Library Extension

errno macro
errno.inc
******************************************************************************************************************/
#if defined _PLE_ERRNO_INC
	#endinput
#else
	#define _PLE_ERRNO_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#if !defined errno
	#define errno:: errno_
#endif

stock public const errno::E2BIG = -1;				//Argument list too long
stock public const errno::EACCES = -1;			//Permission denied
stock public const errno::EADDRINUSE = -1;		//Address in use
stock public const errno::EADDRNOTAVAIL = -1;		//Address not available
stock public const errno::EAFNOSUPPORT = -1;		//Address family not supported
stock public const errno::EAGAIN = -1;			//Resource unavailable, try again
stock public const errno::EALREADY = -1;			//Connection already in progress
stock public const errno::EBADF = -1;				//Bad file descriptor
stock public const errno::EBADMSG = -1;			//Bad message
stock public const errno::EBUSY = -1;				//Device or resource busy
stock public const errno::ECANCELED = -1;			//Operation canceled
stock public const errno::ECHILD = -1;			//No child processes
stock public const errno::ECONNABORTED = -1;		//Connection aborted
stock public const errno::ECONNREFUSED = -1;		//Connection refused
stock public const errno::ECONNRESET = -1;		//Connection reset
stock public const errno::EDEADLK = -1;			//Resource deadlock would occur
stock public const errno::EDESTADDRREQ = -1;		//Destination address required
stock public const errno::EDOM = -1; 				//Mathematics argument out of domain of function
stock public const errno::EEXIST = -1;			//File exists
stock public const errno::EFAULT = -1;			//Bad address
stock public const errno::EFBIG = -1;				//File too large
stock public const errno::EHOSTUNREACH = -1;		//Host is unreachable
stock public const errno::EIDRM = -1;				//Identifier removed
stock public const errno::EILSEQ = -1;			//Illegal byte sequence
stock public const errno::EINPROGRESS = -1;		//Operation in progress
stock public const errno::EINTR = -1;				//Interrupted function
stock public const errno::EINVAL = -1;			//Invalid argument
stock public const errno::EIO = -1;				//I/O error
stock public const errno::EISCONN = -1;			//Socket is connected
stock public const errno::EISDIR = -1;			//Is a directory
stock public const errno::ELOOP = -1; 			//Too many levels of symbolic links
stock public const errno::EMFILE = -1;			//File descriptor value too large
stock public const errno::EMLINK = -1;			//Too many links
stock public const errno::EMSGSIZE = -1;			//Message too large
stock public const errno::ENAMETOOLONG = -1;		//Filename too long
stock public const errno::ENETDOWN = -1;			//Network is down
stock public const errno::ENETRESET = -1;			//Connection aborted by network
stock public const errno::ENETUNREACH = -1;		//Network unreachable
stock public const errno::ENFILE = -1;			//Too many files open in system
stock public const errno::ENOBUFS = -1;			//No buffer space available
stock public const errno::ENODATA = -1;			//No message is available on the STREAM head read queue
stock public const errno::ENODEV = -1;			//No such device
stock public const errno::ENOENT = -1;			//No such file or directory
stock public const errno::ENOEXEC = -1;			//Executable file format error
stock public const errno::ENOLCK = -1;			//No locks available
stock public const errno::ENOLINK = -1;			//Link has been severed
stock public const errno::ENOMEM = -1;			//Not enough space
stock public const errno::ENOMSG = -1;			//No message of the desired type
stock public const errno::ENOPROTOOPT = -1;		//Protocol not available
stock public const errno::ENOSPC = -1;			//No space left on device
stock public const errno::ENOSR = -1;				//No STREAM resources
stock public const errno::ENOSTR = -1;			//Not a STREAM
stock public const errno::ENOSYS = -1;			//Function not supported
stock public const errno::ENOTCONN = -1;			//The socket is not connected
stock public const errno::ENOTDIR = -1;			//Not a directory
stock public const errno::ENOTEMPTY = -1;			//Directory not empty
stock public const errno::ENOTRECOVERABLE = -1;	//State not recoverable
stock public const errno::ENOTSOCK = -1;			//Not a socket
stock public const errno::ENOTSUP = -1;			//Not supported
stock public const errno::ENOTTY = -1;			//Inappropriate I/O control operation
stock public const errno::ENXIO = -1;				//No such device or address
stock public const errno::EOPNOTSUPP = -1;		//Operation not supported on socket
stock public const errno::EOVERFLOW = -1;			//Value too large to be stored in data type
stock public const errno::EOWNERDEAD = -1;		//Previous owner died
stock public const errno::EPERM = -1;				//Operation not permitted
stock public const errno::EPIPE = -1;				//Broken pipe
stock public const errno::EPROTO = -1;			//Protocol error
stock public const errno::EPROTONOSUPPORT = -1;	//Protocol not supported
stock public const errno::EPROTOTYPE = -1;		//Protocol wrong type for socket
stock public const errno::ERANGE = -1; 			//Result too large
stock public const errno::EROFS = -1;				//Read-only file system
stock public const errno::ESPIPE = -1;			//Invalid seek
stock public const errno::ESRCH = -1;				//No such process
stock public const errno::ETIME = -1;				//Stream ioctl() timeout
stock public const errno::ETIMEDOUT = -1;			//Connection timed out
stock public const errno::ETXTBSY = -1;			//Text file busy
stock public const errno::EWOULDBLOCK = -1;		//Operation would block
stock public const errno::EXDEV = -1;				//Cross-device link

native errno::errno();
native errno::clearerrno();
