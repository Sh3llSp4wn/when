# when

`when` is a highly portable comand line utility for reacting to filesystem conditions. This means no polling or OS or GNU specific features needed.

A basic usage example is as follows:

```bash
# move a chrome download somewhere else
when -d Downloads/whatever.crdownload && mv Downloads/whatever Documents/whatever
# OR
when -e Downloads/whatever && mv Downloads/whatever Documents/

# compress a log file after it reaches 10K
when -s 10000 /var/log/some_log && xz -S "$(date +%d%m%y_%H%M).xz" /var/log/some_log
```

## Arguments
* `-n`
 * negate the condition
* `-d`
 * if file is deleted
* `-e`
 * if file is created
* `-s <size>`
 * if file or dir exceeds a specific size
* `-z`
 * if the file is empty or the dir contains no files

## Return Value
* 0 
 * Condition was met
* > 0
 * Condition was unmet and wait was cancled for some reason (example: timeout)
* < 0
 * An error occured in parsing arguments

## Development notes
This project only requires a small number of posix capibilities and has no dependencies

Needed functions are as follows
* `fprintf`
 * TODO: make this a build option
* `stat`
* `nanosleep`
* `memset`
* `getopt`
* `opendir`
* `readdir`
* `closedir`

None of the above functions use anything outise of the POSIX08 capibilites expected from each function.

This project also does not enforce POSIXLY_CORRECT style arguments, but it is recomended to format the arguments this way

Good: `when -ds 100 test.txt`
Less Good: `when -d test.txt -s 100`

`main()` requires `argc` and `argv` to be set by the c library in use, and does not use `envp`

## Licence 
This project is BSD licenced
