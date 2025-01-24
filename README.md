# when

when is a comand line utility for reacting to things with commands

basic usage is as follows:

```bash
when -d Downloads/whatever.crdownload -- mv Downloads/whatever Documents/whatever
```

## Arguments
* `-n`
 * negate the following flag
* `-d`
 * if file is deleted
* `-e`
 * if file is created
* `-s <size>`
 * if file or dir exceeds a specific size
* `-z`
 * if the file is empty or the dir contains no files
