
# Minishell

## Summary

During the Minishell project at 42 school, I had the opportunity to work alongside my partner Tiago([@TiagoTeo](https://github.com/TiagoTeo)) to build a simplified Unix shell. Our task was to create a fully functional command-line interface that allowed users to execute commands, manage built-in functionalities like "cd," and handle environment variables. It was an exciting and valuable learning experience that deepened my understanding of OS concepts like process management and parsing. Tiago and I collaborated closely, combining our skills to design an efficient and user-friendly shell, making the project both challenging and rewarding.

## Our implementation

### Data Structure

We have implemented a data structure called **`t_list`** (linked list node) to represent each command in a series of commands. Each node contains the following features:

```c
typedef struct s_list
{
	char			**content;
	char			*path;
	int				fd_master[2];
	int				fd[2];
	struct s_list	*next;
	struct s_list	*prev;
	void			(*ft_exec)(struct s_list **list);
}	t_list;
```

Here's what each field represents:

- **`content`**: It stores the content of the command (excluding redirections and quotes).
- **`path`**: It stores the path of the command (e.g., **/usr/bin/ls** , etc.).
- **`fd_master`**: An array of two integers used to save the redirection file descriptors. Initialized as 0 and 1 when there are no file redirections.
- **`fd`**: An array of two integers representing default pipe file descriptors.
- **`next`** and **`prev`**: Pointers to the next and previous nodes in the linked list, respectively.
- **`ft_exec`**: A function pointer pointing to the function responsible for executing the command.


**Example of input I will use to explain:**

I will explain our parsing, redirections and execution with an example command:

```bash
< Makefile grep a > out | < main.c cat
```

### Parsing

**Step 1: Parsing the command**

In the given example, after parsing the command into tokens using the function **`parser()`**, resulting in a char* array containing redirections, commands, pipes, files, arguments, and other relevant tokens we have two commands separated by a pipe symbol "|", with each command represented by a node in the linked list.

[’<’, ‘Makefile’ , ‘grep’ , ‘a’ ,’|’, ‘>’ , ‘out’, ’main.c’ , ‘cat’ ]

**Technical explanation of our parser:(optional reading)**

Our parser is designed to tokenize a given shell command input and store the resulting tokens in a modified format. It processes the input string character by character, considering special characters like quotes, double quotes, angle brackets, and pipes as separators. The parser converts these separators into numeric codes (2 and 3 in this case) and modifies the input string accordingly.

Check our **parser()** function to understand the logic.

For the given example:

```c
Input:                **< Makefile grep a > out | < main.c cat**
Our Parser Output:    **22<2Makefile2grep2a222>22out2232222<22main.c2cat**
```

The final output array represents the parsed and tokenized form of the input command line, allowing further processing or execution of individual commands in the minimal shell environment.

### Redirections

**Step 2: Setting Up File Descriptors**

Initial fd_mater’s file descriptors are set to **`0`** (stdin) and **`1`** (stdout) when there are no file redirections. 

So the `fd_master[0]` and `fd_master[1]` are updated based on the redirection symbols ("<" and ">") found in the command. The file descriptor **`6`** corresponds to the file "Makefile" and **`7`** corresponds to the file "out".

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 3 | 4 |  |  |  |
| 6 | 1 | 3 | 4 |  | < Makefile | change file descriptor in |
| 6 | 1 | 3 | 4 | grep a | grep a | update content |
| 6 | 7 | 3 | 4 | grep a | > out | change file descriptor out |

When, the program find a pipe `‘|’` it means that the command is over and we have the final values for the fd_master variable.

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 5 | 9 |  |  |  |
| 8 | 1 | 5 | 9 |  | < main.c | change file descriptor in |
| 8 | 1 | 5 | 9 | cat | cat | update content |

In this command the file will read from the file descriptor 8 and will write to the file descriptor 1.

### Execution

Each time we execute a node command, we create a fork and the redirections are set up in the child process.

This is the logic applied for the redirections in the execution.

```c
if (fork() == 0)
	{
		if (lst->prev && lst->fd_master[0] < 3)
			dup2(lst->fd[0], 0);
		else if (lst->fd_master[0] > 2)
			dup2(lst->fd_master[0], 0);
		if (lst->next && lst->fd_master[1] < 3)
			dup2(lst->next->fd[1], 1);
		else if (lst->fd_master[1] > 2)
			dup2(lst->fd_master[1], 1);
		lst->ft_exec(&lst);
```

Its quite simple, so i am going to explain for the current example where we have two nodes.

**NODE 1:** For executing the **first node** we will be doing:

`dup(lst→fd_master[1], 1)` 

only because this node has no previous and the fd_master[1] is bigger than 2 and also

`dup2(lst→fd_master[0], 0)`  , because fd_master[0]  is bigger than 2.

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 6 | 7 | 3 | 4 | grep a | > out | change file descriptor out |

So this command it will read from file descriptor 6 and write to file descriptor 7 in his execution.

**NODE 2:** For executing the **second node** we will be doing:

`dup2(lst→fd_master[0], 0)` 

because this node has the fd_master[0] is bigger than 2. So, because we want to write to the default destination which is the file descriptor 1, that’s why in this cause it will happen only one dup().

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 8 | 1 | 5 | 9 | cat | cat | update content |

So this command it will read from file descriptor 8 and write to file descriptor 1 in his execution.

**Other example(USING PIPES):**

```c
cat | ls
```

**NODE 1:** For executing the **first node** we will be doing, accordingly with the logic above:

`dup2(lst->next->fd[1], 1);` 

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 3 | 4 | cat | cat | update content |

So this command will read from the file descriptor 0 and it will write to the file descriptor 6, because the dup made this command point to lst→next→fd[1] instead the default writing file descriptor (stdout).

**NODE 2:** For executing the **second node** we will be doing:

`dup(lst→fd[0], 0)` 

| fd_master[0] | fd_master[1] | fd[0] | fd[1] | Content | Token found |  |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 5 | 6 | ls | ls | update content |

So this command will read from the file descriptor 5 and it will write to the file descriptor 1.

          fd[1]  |——————-| fd[0]

     in/write                      out/read
     6	                           5

<p align="center">
  <img src="https://github.com/duarte3333/Minishell/assets/76222459/756bc082-1386-471e-8d5e-b26e233b18fa" alt="Image Description" "style="width: 90%;">
</p>

**!!This works for any line of commands you can think of!!**

## Features of our shell

1. Display a prompt while waiting for a new command.
2. Have a working history.
3. Find and launch executables using the PATH variable or an absolute path.
4. Handle single and double quotes like in bash.
5. Implement input/output redirections such as <, >, <<, and >>.
6. Implement pipes using the | symbol.
7. Handle environment variables.
8. Handle the special variable $?.
9. Support ctrl-C, ctrl-D, and ctrl-\ signals as in bash.
10. Recreate the built-in commands echo with option -n, cd with only a relative or absolute path, pwd with no flags, export with no flags, unset with no flags, env with no flags or arguments, and exit with no flags.

## Theory

### What is a shell?

**Simple definition:** A shell is a way to talk to the computer using text commands instead of clicking on icons or menus. It's like a window into the computer's brain. There are different types of shells, but they all let to do things like open programs, move files, and change settings by typing in simple commands.

A shell refers to a command-line interface that allows users to interact with an operating system. It provides a way to access and control the various functions of an operating system using text commands rather than a graphical user interface.

<p align="center">
  <img src="https://github.com/duarte3333/Minishell/assets/76222459/5e49623b-4326-4b25-87e1-4962e7092835" alt="Image Description" style="width: 60%;">
</p>

### What is a GNU shell?

GNU shell, also known as Bash (short for "Bourne-again shell"), is a widely used command-line interface and scripting language for Unix-based operating systems. It is the default shell on most Linux distributions and is available on many other Unix-like systems.

### What are the steps to make the our Minishell?

<p align="center">
  <img src="https://github.com/duarte3333/Minishell/assets/76222459/0e15e6a5-4314-482b-ab31-d7fdf32d8418" alt="Image Description" style="width: 80%;">
</p>

1. **Parser:**
The parser is responsible for breaking down the user input into individual tokens. It takes the raw command line and separates it into distinct components like commands, arguments, operators, and redirections. The parsed tokens are then used to construct the command structure for further processing and execution.
2. **Syntax Errors:**
We handled syntax errors in Minishell to provide informative feedback to the user when they enter an invalid command or have incorrect syntax. Proper error handling helps users identify and correct mistakes, making the shell more user-friendly.
3. **Expander:**
The expander module processes certain special characters and expansions in the command, such as environment variable expansion (e.g., **`$VAR`**) and command substitution (e.g., **`$(command)`**). It ensures that these expansions are resolved correctly before executing the command.
4. **Here Doc:**
Here documents (Here doc) are a type of input redirection in which data is provided directly into the standard input of a command from the script itself, using a delimiter to mark the end of the input. We implemented support for here documents, allowing users to provide input inline within the script or command line.
5. **Redirections:**
Redirections in our Minishell allow users to manipulate standard input, output, and error streams for commands. We implemented input redirection (**`<`**), output redirection (**`>`** and **`>>`**). These redirections enable users to work with files and customize command behavior.
6. **Signals:**
Signal handling is essential for maintaining the shell's responsiveness and user experience. We managed signals like **`SIGINT`** (usually triggered by pressing Ctrl+C) and  **`SIGQUIT`** (usually triggered by pressing Ctrl+D). Handling these signals allows users to interrupt or terminate running processes gracefully.
7. **Built-ins:**
Built-in commands are commands that are directly handled by the shell itself rather than invoking external executables. In Minishell, you implemented several built-in commands like **`cd`** for changing directories, **`echo`** with the **`n`** option to suppress newlines, **`pwd`** to print the current working directory, **`export`** to set environment variables, **`unset`** to remove environment variables, **`env`** to display environment variables, and **`exit`** to exit the shell.

### What is the function fork() ?

In C programming, the **`fork()`** function is used to create a new process by duplicating the calling process. The new process is referred to as the child process, while the original process is referred to as the parent process.

When **`fork()`** is called, a new process is created that is a copy of the calling process. Both processes then continue executing from the point where the **`fork()`** function was called. The new process gets its own unique process ID (PID), while the parent process retains its original PID.
<div align="center">
    <table >
     <!-- <tr>
        <td><b>Latest Tweets</b></td>
        <td><b>daily.dev</b></td>
     </tr> -->
     <tr>
       <td><img src="https://user-images.githubusercontent.com/76222459/227656655-9899db40-ae44-4b32-ad7d-51363da4028b.png" width="300" alt="sunil sapkota twitter" > </img></td>
        <td><img src="https://user-images.githubusercontent.com/76222459/227656661-5774de6c-4ecd-47ab-8afc-fad557ac75ad.png" width="300" alt="sunil sapkota's Dev Card"/></td>
     </tr>
    </table>
    </div>

The child process and parent process run independently of each other and have their own memory space, CPU registers, and file descriptors. The child process can modify its own memory space, but any changes made by the child process do not affect the parent process.

### What is a pipe?

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227657406-bbaa54c1-31c8-48b8-b772-3c4bab9d5b94.png" width="400" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

**Definition:** A pipe is a method for </ins>interprocess communication (IPC)</ins> that allows one process to send data to another process. A pipe consists of two ends, a read end and a write end. The write end is used to send data to the pipe, and the read end is used to receive data from the pipe.

**Simple Definition:** A pipe is like a tube that connects two processes or programs. One end of the pipe is used to send data and the other end is used to receive it.

### What is the function readline() ?

**Simple definition:** It is a library function in C that reads input from the user via the command line interface. It allows for more advanced user input handling, including features such as line editing and command history.

```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
int main() 
{
    char* input;
    while ((input = readline("Enter a command: ")) != NULL) {
        add_history(input);
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}
```

This program will repeatedly prompt the user to enter a command, read the input using **`readline`**, add the input to the command history using **`add_history`**, and then print the input to the console using **`printf`**. Finally, it frees the memory used by the input string with **`free`**.

**Readline library**

The readline library is a set of functions for command-line editing, history, and tab completion in a program.

- The **`readline`** function allows a program to read input from the user with advanced editing features.
- The **`rl_clear_history`** function **clears** the command **history**.
- The **`rl_on_new_line`** function informs readline that the **prompt has moved to a new line**.
- The **`rl_replace_line`** function replaces the current line with a new one.
- The **`rl_redisplay`** function redisplay the current line.
- The **`add_history`** function adds a line to the command history.

## Signals

### What is a sigaction?

**`struct sigaction`** is a data structure in C that represents a set of actions to be taken when a particular signal is delivered to a process. It is used with the **`sigaction()`** function to install a new signal handler or modify an existing handler for a specific signal.

The **`struct sigaction`** type contains the following fields:

- **`sa_handler`**: a pointer to the signal handler function, or one of two special values: **`SIG_DFL`** to set the default action for the signal or **`SIG_IGN`** to ignore the signal.
- **`sa_sigaction`**: an alternative signal handler function that provides additional information about the signal and its context.
- **`sa_flags`**: a set of flags that modify the behavior of the signal handler, such as **`SA_RESTART`** to ensure that system calls are automatically restarted after the signal is handled.
- **`sa_mask`**: a set of signals that are blocked while the signal handler is executing.
- **`sa_restorer`**: a pointer to an optional function that is called after the signal handler returns.

The **`sigaction()`** function takes a pointer to a **`struct sigaction`** object and installs or modifies the signal handler for the specified signal.

**Example:** When the program is executed, it installs the **`sigintHandler()`** as the signal handler for **`SIGINT`** (Ctrl+C).

```c
#include <stdio.h>
#include <signal.h>

// Signal handler function for SIGINT
void sigintHandler(int signum) {
    printf("Received SIGINT signal (Ctrl+C). Exiting...\n");
    // Perform cleanup or other necessary tasks before exiting
    // For this example, we'll simply terminate the program.
    exit(0);
}

int main() {
    struct sigaction sa;

    // Set the signal handler function
    sa.sa_handler = sigintHandler;
    // Clear sa_mask (no additional signals will be blocked during the signal handler execution)
    sigemptyset(&sa.sa_mask);
    // Set SA_RESTART flag to automatically restart system calls after the signal handler returns
    sa.sa_flags = SA_RESTART;
    // Install the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    printf("Press Ctrl+C to trigger SIGINT...\n");
    // Infinite loop to keep the program running until Ctrl+C is pressed
    while (1) {
        // Do some work or wait for the signal
    }
    return 0;
}
```

When its pressed Ctrl+C in the terminal, the **`sigintHandler()`** function will be called, and it will print the message "Received SIGINT signal (Ctrl+C). Exiting..." before terminating the program gracefully.

Alternatively:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGINT
void handle_sign(int signum) {
    printf("Received SIGINT signal (Ctrl+C). Exiting...\n");
    // Perform cleanup or other necessary tasks before exiting
    // For this example, we'll simply terminate the program.
    exit(0);
}

int main() {
    // Install the signal handler for SIGINT using signal()
    signal(SIGINT, handle_sign);
    printf("Press Ctrl+C to trigger SIGINT...\n");
    // Infinite loop to keep the program running until Ctrl+C is pressed
    while (1) {
        // Do some work or wait for the signal
    }
    return 0;
}
```

## Documentation

[Short introduction to signals in C](https://www.youtube.com/watch?v=5We_HtLlAbs&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=16&pp=iAQB)

https://github.com/Swoorup/mysh

[minishell](https://harm-smits.github.io/42docs/projects/minishell#getting-started)

https://github.com/maiadegraaf/minishell

[https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

## Command’s that work in our shell exacly like Bash?

```bash
cat /dev/random | head
< Makefile < main.c cat > out > out2
<< ola << oi << lol << final cat
<< EOF cat
cat << EOF
cd  | cd
ls  | cd
cd  | ls
pwd | cat
cat | exit | cat | wc
cat >
exit 300
export | grep ola (ola nao tá no env; e tem de dar print declare -x ola)
export new (variavel nova) ; nao pode tar no env
export new=a (variavel nova) ; ja pode tar no env
export LOL=lala ROR=rara
unset LOL ROR
export "HI =hi"
echo ""''
echo test > file test1
export a=c b=a c=t e dps $a$b$c main.c
----
echo bonjour ; |
echo bonjour | |
|
echo bonjour |;
echo bonjour ; ls
echo bonjour > test\ 1
cd $HOME/Documents
echo "\s" & echo "\s"
echo >
echo -n -n -nnnn -nnnnm
cat /dev/random | head -n 1 | cat -e
unset var1 # with undefined var1
export "" et unset ""
echo test > file test1
$
not_cmd bonjour > salut
env puis export puis env # vars aren't sorted
cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code
cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code
cat Makefile | grep pr | head -n 5 | hello (NA) # check status code
echo bonjour >>> test
echo bonjour > > out
echo 2 >> out1 > out2
echo 2 > out1 >> out2
cat < test # with non-existent test
export var; export var=test
echo bonjour > $test # with test not defined
file_name_in_current_dir
cd ../../../../../.. ; pwd
ctrl-C . 130 sur bin(ex : sleep 10)&line vide
ctrl-\ .131 sur bin
echo "bip | bip ; coyotte > < " "
cat | cat | cat | ls # check outputs order
$bla # with bla not defined
export var ="cat Makefile | grep >"
export "test=ici"=coucou
c$var Makefile # with var=at
$LESS$VAR
/bin/echo bonjour
not_cmd
sleep 5 | exit
echo bonjour > $test w/ t
"exit retour a la ligne"
minishell # binary not in path without "./" before
cat diufosgid # check exit code
exit # should return the last exit code value
exit -10
exit +10
;
echo coucou | ;
echo "$HOME"
echo '$HOME'
export ; env # display is different for both commands
echo $HOME
> log echo coucou
echo hudifg d | | hugdfihd
echo
echo simple
echo -n simple
echo ''
echo ""
echo "\"
echo "\n \n \n"
echo "\n \n \\n"
echo ;;
echo hi";" hihi
echo hi " ; " hihi
cd
cd .
cd ~
cd /
cd no_file
cd a b c d
pwd a
pwd a b c d
export LOL=lala ROR=rara
unset LOL ROR
export "HI= hi"
export "HI =hi"
/bin/ls
# write something the press ctrl+c
# write something then press ctrl+d
# write something then press ctrl+\
echo $?
l^Ds
echo |
| echo
sort | ls # check output order
cat < >
cat < <
cat > >
> a ls > b < Makefile
echo > a Hello World!
> a echo Hello World!
cat < Makefile | grep gcc > output
exit 0 | exit 1
exit 1 | exit 0
```
