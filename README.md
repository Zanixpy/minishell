*This project has been created as part of the 42 curriculum by omawele, cakibris.* 

# Minishell

## Description

This project is about creating a simple shell. Yes, your very own little Bash. Through the development of this project, you will gain extensive knowledge about processes and file descriptors. The shell displays a prompt, features a working history, and can search and launch executables. It accurately handles pipes, various redirections (`<`, `>`, `<<`, `>>`), and environment variables. Additionally, it implements several built-in commands including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Instructions

* **Compilation:** Run `make` at the root of the repository. This will compile the source files using `cc` with the mandatory `-Wall`, `-Wextra`, and `-Werror` flags.


* **Execution:** Once compiled, launch the program by executing `./minishell`.


* **Cleanup:** The Makefile includes standard rules to manage files: use `make clean` to remove objects, `make fclean` to remove objects and the executable, and `make re` to recompile.

## Resources

* **Technical References:** Bash Reference Manual, GNU C Library documentation (specifically for processes, file descriptors, and signals).

* **AI Usage:** AI was used to help design the parser logic, after which the logic was reviewed and rewritten with peers to ensure full understanding and clean code. AI was also utilized to brainstorm approaches, always followed by systematic checking, questioning, and testing.