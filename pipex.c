#include "pipex.h"

size_t ft_strlen(char *str)
{
    size_t i;
    while (str[i] != '\0')
        i++;
    return (i);
}

char    *testPath(char **paths, char *cmd)
{
    int i;
    char *tmp;

    while(paths[i] != NULL)
    {
        tmp = ft_strjoin(paths[i], cmd);
        if (access(tmp, F_OK) == 0)
            break;
        i++;
    }
    return tmp;
}

int main (int ac, char* av[], char *envp[])
{
    int id;
    int fd[2];
    char *array[] =
    {
        "//usr/bin/ping",
        "google.com",
        "-c",
        "3",
        NULL
    };
    
    char *array2[] =
    {
        "//usr/bin/cat",
        av[4],
        NULL
    };

        char *array3[] =
    {
        "//usr/bin/grep",
        av[3],
        av[1],
        NULL
    };


    char grepres[1000];
    pipe(fd);
    id = fork();
    if(id == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execve("//usr/bin/grep", array3, NULL);
    }
    else 
    {
        wait(NULL);
        close(fd[1]);
        int nbyte = read(fd[0], grepres, 1000);
        close(fd[0]);
        int file = open(av[4], O_WRONLY | O_CREAT, 0777);
        printf("GREP RESULT IS %s\n", grepres);
        write(file, &grepres, nbyte);
        printf("lol jsuis apres le grep\n");
        execve("//usr/bin/cat", array2, NULL);
    }
      printf("lol jsuis apres le cat et le grep mdr\n");
    return 0;
}