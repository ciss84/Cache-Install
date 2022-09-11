#include "ps4.h"
#include "fw_defines.h"
#include "payload_utils.h"
#include "debug.h"
#include "ApplicationCache.h"

void writeCacheDB()
{
size_t len = 0;
unsigned char* fbuf = base64_decode(ApcStr, sizeof(ApcStr), &len);
if (len != 0)
{
int fid = open("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", O_WRONLY | O_CREAT | O_TRUNC, 0777);
write(fid, fbuf, len);
close(fid);
free(fbuf);
sceKernelSleep(3);
printf_notification("Cache 84Ciss - install Complete\n\nBookmark:\nhttps://mugiwara-v2.github.io/cachev9/index.html");
sceKernelSleep(1);
openBrowser("https://mugiwara-v2.github.io/cachev9/index.html");
}else{
printf_notification("ERROR:\nNo 84Ciss - internal cache found");
}
}
int _main(struct thread *td) {
UNUSED(td);
jailbreak();
initKernel();
initLibc();
initSysUtil();
if (!dir_exists("/user/system/webkit/webbrowser/appcache"))
{
mkdir ("/user/system/webkit/webbrowser/appcache", 0777);
}
int usbdir = open("/mnt/usb0/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
if (usbdir == -1)
{
usbdir = open("/mnt/usb1/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
if (usbdir == -1)
{
printf_notification("No 84Ciss - usb found\nUsing 84Ciss - Internal Cache");
writeCacheDB();
return 0;
}else{
close(usbdir);    
if (file_exists("/mnt/usb1/ApplicationCache.db")) 
{ 
printf_notification("Cache 84Ciss - file found on USB1");
copy_file("/mnt/usb1/ApplicationCache.db","/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
printf_notification("Cache 84Ciss - restore Complete.");
}else{
printf_notification("No cache 84Ciss - file found on USB1\nUsing 84Ciss - Internal Cache");
writeCacheDB();
}
}
}else{
close(usbdir);
if (file_exists("/mnt/usb0/ApplicationCache.db")) 
{
printf_notification("Cache 84Ciss - file found on USB0");
copy_file("/mnt/usb0/ApplicationCache.db","/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
printf_notification("Cache 84Ciss - restore Complete.");
}else{
printf_notification("No cache 84Ciss - file found on USB0\nUsing 84Ciss - Internal Cache");
writeCacheDB();
}
}
return 0;
}