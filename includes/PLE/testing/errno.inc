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
native errno();
native clearerrno();
/*****************************************************************************************************************/
stock public const E2BIG = -1;				//Argument list too long
stock public const EACCES = -1;				//Permission denied
stock public const EADDRINUSE = -1;			//Address in use
stock public const EADDRNOTAVAIL = -1;		//Address not available
stock public const EAFNOSUPPORT = -1;		//Address family not supported
stock public const EAGAIN = -1;				//Resource unavailable, try again
stock public const EALREADY = -1;			//Connection already in progress
stock public const EBADF = -1;				//Bad file descriptor
stock public const EBADMSG = -1;			//Bad message
stock public const EBUSY = -1;				//Device or resource busy
stock public const ECANCELED = -1;			//Operation canceled
stock public const ECHILD = -1;				//No child processes
stock public const ECONNABORTED = -1;		//Connection aborted
stock public const ECONNREFUSED = -1;		//Connection refused
stock public const ECONNRESET = -1;			//Connection reset
stock public const EDEADLK = -1;			//Resource deadlock would occur
stock public const EDESTADDRREQ = -1;		//Destination address required
stock public const EDOM = -1; 				//Mathematics argument out of domain of function
stock public const EEXIST = -1;				//File exists
stock public const EFAULT = -1;				//Bad address
stock public const EFBIG = -1;				//File too large
stock public const EHOSTUNREACH = -1;		//Host is unreachable
stock public const EIDRM = -1;				//Identifier removed
stock public const EILSEQ = -1;				//Illegal byte sequence
stock public const EINPROGRESS = -1;		//Operation in progress
stock public const EINTR = -1;				//Interrupted function
stock public const EINVAL = -1;				//Invalid argument
stock public const EIO = -1;				//I/O error
stock public const EISCONN = -1;			//Socket is connected
stock public const EISDIR = -1;				//Is a directory
stock public const ELOOP = -1; 				//Too many levels of symbolic links
stock public const EMFILE = -1;				//File descriptor value too large
stock public const EMLINK = -1;				//Too many links
stock public const EMSGSIZE = -1;			//Message too large
stock public const ENAMETOOLONG = -1;		//Filename too long
stock public const ENETDOWN = -1;			//Network is down
stock public const ENETRESET = -1;			//Connection aborted by network
stock public const ENETUNREACH = -1;		//Network unreachable
stock public const ENFILE = -1;				//Too many files open in system
stock public const ENOBUFS = -1;			//No buffer space available
stock public const ENODATA = -1;			//No message is available on the STREAM head read queue
stock public const ENODEV = -1;				//No such device
stock public const ENOENT = -1;				//No such file or directory
stock public const ENOEXEC = -1;			//Executable file format error
stock public const ENOLCK = -1;				//No locks available
stock public const ENOLINK = -1;			//Link has been severed
stock public const ENOMEM = -1;				//Not enough space
stock public const ENOMSG = -1;				//No message of the desired type
stock public const ENOPROTOOPT = -1;		//Protocol not available
stock public const ENOSPC = -1;				//No space left on device
stock public const ENOSR = -1;				//No STREAM resources
stock public const ENOSTR = -1;				//Not a STREAM
stock public const ENOSYS = -1;				//Function not supported
stock public const ENOTCONN = -1;			//The socket is not connected
stock public const ENOTDIR = -1;			//Not a directory
stock public const ENOTEMPTY = -1;			//Directory not empty
stock public const ENOTRECOVERABLE = -1;	//State not recoverable
stock public const ENOTSOCK = -1;			//Not a socket
stock public const ENOTSUP = -1;			//Not supported
stock public const ENOTTY = -1;				//Inappropriate I/O control operation
stock public const ENXIO = -1;				//No such device or address
stock public const EOPNOTSUPP = -1;			//Operation not supported on socket
stock public const EOVERFLOW = -1;			//Value too large to be stored in data type
stock public const EOWNERDEAD = -1;			//Previous owner died
stock public const EPERM = -1;				//Operation not permitted
stock public const EPIPE = -1;				//Broken pipe
stock public const EPROTO = -1;				//Protocol error
stock public const EPROTONOSUPPORT = -1;	//Protocol not supported
stock public const EPROTOTYPE = -1;			//Protocol wrong type for socket
stock public const ERANGE = -1; 			//Result too large
stock public const EROFS = -1;				//Read-only file system
stock public const ESPIPE = -1;				//Invalid seek
stock public const ESRCH = -1;				//No such process
stock public const ETIME = -1;				//Stream ioctl() timeout
stock public const ETIMEDOUT = -1;			//Connection timed out
stock public const ETXTBSY = -1;			//Text file busy
stock public const EWOULDBLOCK = -1;		//Operation would block
stock public const EXDEV = -1;				//Cross-device link

