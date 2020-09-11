1. Command to get the inode number
ls -i 

2. To see the file data structure in fs.h follow the below path
cd /usr/src/linux-headers-4.15.0-112/include/linux

Access file by command:
    less fs.h

Here check the below data struct (related to file) in fs.h:
    a) inode structure : by using the /struct inode \{
    b) file structure  : by using the /struct inode \{
    c) file_operations structure: by using the /struct file_operations \{

Data structure related to process:
    less sched.h
    a) struct task_struct  : instead of PCB
     to search : struct task_struct \{
        This structure contains: a) pointer to stack.                  
                                 b) scheduling policy.
                                 c) pid and gid.
                                 d) children and sibling.
                                 e) cpu usuage
                                 f) signals and its handler.
                                 g) soft and hard irq.

3. Monitor the cpu usuage every 3 sec:
    top
     Here VIRT -> Virtual memory size consumed by process currently.(in KB)
           RES  -> Resident size i.e the actual physical memory consumed by process currently.(in KB)
           SHR  -> sharable memory i.e How much of actual size of memory the memory is shared.(in KB) 

4. To see the pid of current bash shell
    echo $$ 
   and parent process id
    echo $PPID 

5.Various files and directories in /proc/pid directory. The proc directory is also called as window to running linux kernel. 

    Some of them are:
    
    a) cmdline : Command line passed to current shell.
    b) environ : all environment variables.
    c) limits  : contains the soft and hard limits.
    d)  maps   : contains the memory mapped regions.
    e)  sched  : scheduling related information.
    f) stack   : stack related information.
    g)  stat   : process status read by program.
    h)  status : process status read by program in human readable format.
    i)  cwd    : softlink to current working directory
    j)  exe    : softlink to executable file.
    k)  root   :  softlink to root working directory for current process.
    l)  fd     : directory that contains the symbolic link to file descriptor that current process has opened.
    m) task    : directory that contains the directory for each thread.

5. To  see all the details about the proc directory.  
   man proc
  NOTE: No file for the swapper in /proc directory and swapper is the process with pid = 0
   Init/Systemd process : pid =1 , invoked at end of booting process.
    Page Daemon/kthreadd: pid = 2, support for paging in virtual memory system.
 
6. Various ID's used in Process Identification:

    NOTE : To print the real and effective user and group id use below command:
                  id 

    NOTE : To see the password file:
		ls /etc/shadow
	    We can change password using the passwd command.
             To check the path of passwd program: which passwd
    
    NOTE:    To get the real ,effective and saved id of user: getresuid()   SEE PROGRAM 2_get_real_effective_and_user_ids.c
              To get the real ,effective and saved id of group: getresgid()
              root has id = 0
               cat /etc/passwd | grep vermas    -> for verify of id's
               cat /etc/group    -> to check the group id 
               
    NOTE:    To change the group name 
                check the user name currently:    tail -l /etc/group
                   groupmod -n newname oldname   -> change the oldname to newname
                    groupmod -g newid groupname   -> change the newid of specified groupname.
                  sudo useradd -G shobhit bhatiya  -> add a new user bhatiya to existing group shobhit

  
   a) Process ID and Parend Process ID : Get by getpid() and getppid() function.
     To check the max pid limit : /proc/sys/kernel/pid_max   i.e 32768
    
    See program also. Here check the parent by echo $$

      Parent id can also be found by 4th field of below file:
       /proc/PID/stat , where PID is pid of process.
     
     State of process can be found by 3rd field of below file:
      /proc/PID/stat , where PID is pid of process.
   
   b) Real User ID and Real Group ID: tells the ownership of process

   c) Effective User ID and Effective Group ID(euid and egid): tells the permissions while access of resources.
     These can be changed by:
                             I)  system calls : i.e setuid and setgid
                             II) setting the bit i.e SUID and SGID while executing the program.
     

   d) Saved User ID and Saved Group ID (suid and sgid): Switch temporary from root when non root work is required.
	 ls -l /usr/bin/passwd : shows that its SUID bit set by s in owner permissions.
          
            if the non root user set the SUID bit then the euid change to suid.  -> See program 3_setresuid_understand.c
             To find the other programs with SUID bit set : find /usr/bin -perm /4000 
           To change the s bit of a.out : 
                    sudo chown root:shobhit a.out -> change the owner from vermas to root.
                    sudo chmod +s a.out -> setting the s bit of a.out
        
    e) File System User and Group ID : Used to find the permissions when doing file operations.
    f) Supplementary group ID  : Additional group id to which a process belongs.
                To find out use the file path : /etc/group 

        Here the new process gets this id from parent while the login shell get this Id from /etc/group file. 

7. States of process
    
        /*
 * The task state array is a strange "bitmap" of
 * reasons to sleep. Thus "running" is zero, and
 * you can test for combinations of others with
 * simple bit tests.
 */
static const char * const task_state_array[] = {

	/* states in TASK_REPORT: */
	"R (running)",		/* 0x00 */
	"S (sleeping)",		/* 0x01 */
	"D (disk sleep)",	/* 0x02 */
	"T (stopped)",		/* 0x04 */
	"t (tracing stop)",	/* 0x08 */
	"X (dead)",		/* 0x10 */
	"Z (zombie)",		/* 0x20 */
	"P (parked)",		/* 0x40 */

	/* states beyond TASK_REPORT: */
	"I (idle)",		/* 0x80 */
};

This structure is defined in source code in /fs/proc/array.c

     
   
