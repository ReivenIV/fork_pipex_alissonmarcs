<div align="center">
	<h1>Pipex</h1>
	<img src="https://raw.githubusercontent.com/alissonmarcs/42-project-badges/main/badges/pipexm.png" alt="Pipex project badge of 42"/>
	<p align="center">A 42 project where we have to imitate shell pipelines and input/output file redirections.</p>
</div>

<div align="center">
	<h2>Final score</h2>
	<img src="https://i.imgur.com/dL7Srhr.png" alt="Project scored with 125/100">
</div>

## How to compile

```
$ git clone https://github.com/alissonmarcs/pipex.git
$ cd pipex
$ make bonus
```
Compiling with `make bonus` you will be able to use any number of commands and here_doc.

## Examples

```
$ ./pipex_bonus Makefile "tr A-Z a-z" nl outfile
```

- `Makefile` will be input for `tr`.
- `tr A-Z a-z` translate all uppercase chars to lower case.
- `nl` enumerate lines.
- `outfile` destination file.


```
$ ./pipex_bonus Makefile "ps aux" nl outfile
```

- `Makefile` will be input for `ps`, but `ps` doesn't receive input, so it will not be used.
- `ps aux` list current running processes.
- `nl` enumerate lines.
- `outfile` destination file.

```
$ ./pipex_bonus .gitignore "tr a-z A-Z" nl outfile
```

- `.gitignore` will be input for `tr`.
- `tr` translate all lowercase chars to uppercase.
- `nl` enumerate lines.
- `outfile` destination file.

```
$ ./pipex_bonus Makefile nl tac "head -25" outfile
```

- `Makefile` will be input file for `nl`.
- `nl` enumerate lines.
- `tac` reverse lines.
- `"head -25"` gets first 25 lines of it's sdtin.
- `outfile` destination file.

```
$ ./pipex_bonus Makefile "tr A-Z a-z" nl tac "cat" "tail -25" outfile
```

- `Makefile` will be input file for `tr`.
- `"tr A-Z a-z"` translate all uppercase chars to lowercase.
- `nl` enumerate lines.
- `tac` reverse lines.
- `cat` change any data, simply get it's stdin and writes to stdout.
- `"tail -25"` get last 25 lines from it's stdin.

```
$ ./pipex_bonus Makefile "ls -la ../../" "tr a-z A-Z" "nl" outfile
```

- `Makefile` will be input file for `ls`, but `ls` doesn't receive input, so it will not be used.
- `"ls -la ../../"` long listing of grandfather folder.
- `tr a-z A-Z` translate all lowercase chars to uppercase.
- `nl` enumerate lines.
- `outfile` destination file.

```
$ ./pipex_bonus here_doc LIMITER "tr a-z A-Z" nl outfile
```

- when `here_doc`, user must type the input for first command.
- `LIMITER` must be typed when user finished to type input data.
- `"tr a-z A-Z"` translate all lowercase chars to uppercase.
- `nl` enumerate lines.
- `outfile` destination file. When `here_doc`, the output file is open in append mode.

```
$ ./pipex_bonus here_doc stop nl tac outfile
```

- `here_doc stop` enable here_doc and delimiter will be "stop".
- `nl` enumerate input lines.
- `tac` reverse input lines.
- `outfile` destination file, open in append mode.