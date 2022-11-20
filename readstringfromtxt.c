#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/****************************
   find_pid_by_name : 通过进程名字获取其他进程的pid,成功，返回0；失败，返回-1
   @ProcName : 进程名称
   @foundpid : 进程PID
****************************/
int find_pid_by_name( char* ProcName, int* foundpid)
{
        DIR             *dir;
        struct dirent   *d;
        int             pid, i;
        char            *s;
        int pnlen;

        i = 0;
        foundpid[0] = 0;
        pnlen = strlen(ProcName);

        dir = opendir("/proc");							//Open the /proc directory
        if (!dir)
        {
                printf("cannot open /proc");
                return -1;
        }

        while ((d = readdir(dir)) != NULL) 				//Walk through the directory
		{

                char exe [PATH_MAX+1];
                char path[PATH_MAX+1];
                int len;
                int namelen;

                if ((pid = atoi(d->d_name)) == 0)      	//See if this is a process
					continue;

                snprintf(exe, sizeof(exe), "/proc/%s/exe", d->d_name);
                if ((len = readlink(exe, path, PATH_MAX)) < 0)
                        continue;

				path[len] = '\0';
                s = strrchr(path, '/');					//Find ProcName
                if(s == NULL) 
					continue;
				
                s++;
                namelen = strlen(s);
                if(namelen < pnlen)     continue;

                if(!strncmp(ProcName, s, pnlen)) 		//to avoid subname like search proc tao but proc taolinke matched
				{
                        if(s[pnlen] == ' ' || s[pnlen] == '\0')
						{
                                foundpid[i] = pid;
                                i++;
                        }
                }
        }

        foundpid[i] = 0;
        closedir(dir);

        return  i;
}

void main()
{
/*	FILE *fp;
	float a;
	 if ((fp = fopen("example.txt", "rb")) == NULL)
	 {
	  exit(0);
	 }
	 fseek(fp, 0, SEEK_END);
	 int fileLen = ftell(fp);
	 char *tmp = (char *) malloc(sizeof(char) * fileLen);
	 fseek(fp, 0, SEEK_SET);
	 fread(tmp, fileLen, sizeof(char), fp);
	 a=atof(tmp);
	 printf("%s  sd:%f\n",tmp,a);
	 fclose(fp);
	 */
	int pid;
	while(1)
	{
		
		find_pid_by_name("test",&pid);
		sleep(1);
		printf("app pid:%d \n",pid);
	}
}
