---
title: Practical Shell Examples
categories: blog
---

Using the command line is an essential part of being a good computer scientist. Here I will show you some practical and everyday use cases.

The terminal is where a lot of efficient work is done for computer users. Graphical interfaces are something for people who need a structured and robust way of interacting with a computer. However, using a text based interface will allow for more intricate sequences of commands to get even more work done using the same programs. People will also refer to these programs running "headless" or with out a frontend. Many operating systems are run in this manner to allow for more processing power to be directed to the more important task at hand. I would also like to point out that this entire document was written, compiled and copied to the clipboard all in the terminal. Now, on to the examples.

## Grepping
People who have large collections of PDFs might need to sift through them to find certain patterns of text. This can be time consuming, tedious and error prone if done by hand. In comes `pdfgrep` which allows for paritcular patterns of text to be retrieved from a pdf. The counter part and predecessor `grep` accomplishes the same goal for text based applications, such as reading from a text file or a CSV file output. The following code snippet will find all the files in a current folder (to be referred to as directories from now on) and extract all documents with the corresponding line number to the regular expression (pattern of text).  

```bash
find . -type f -iname '*.pdf' -exec pdfgrep -n "PATTERN" {} \;
```

![pdfgrep example](https://jareddyreson.github.io/assets/using_bash/pdfgrep)

