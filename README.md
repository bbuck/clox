# C Lox

## What is clox?

The book [Crafting Interpreters by Bob Nystrom](http://www.craftinginterpreters.com)
details the creation of a toy programming language called "Lox." The
[full grammar for this toy language](http://www.craftinginterpreters.com/appendix-i.html)
can be found in the book's appendix.

This project represents my traversal through this book's Part III. My work
through Part II can be found in my
[LoxSharp repository](https://github.com/bbuck/LoxSharp), and there you may find
comments that this part was meant to be in Go, and in fact it was. But for the
sake of getting more practice with C I opted to just stick with C (which is what
the book uses for this part). Although you will definitely find that my code
style and naming differ from the book.

This project represents the bytecode VM side of Lox where LoxSharp represents
the Abstract Syntax Tree-based tree-walking implementation.

**DISCLAIMER: This is not a serious project, this is not a serious language.
This should not be used as a scripting language in a production application.**

## Building and Running

You will need [Bazel](https://bazel.build) in order to build this project
unless you want to do it by hand or configure your own Makefile (why would
you?).

Once you have Bazel, building is dead simple:

```
$ bazel build //:clox
```

That's it. Once that builds, you can then easily access the executable in
`bazel-bin/clox` and do whatever you need with that executable.

### Where is the Makefile?

I don't really like Makefiles all that much. I mean don't get me wrong, they are
very useful. And if I had not learned how to use Bazel I would definitely be
using one. But, I do know about Bazel and I like the way it works better, so
that's what I'm using.

## Contributions

Due to the nature of this as a guided project along side a book, at this time I
will not be accepting any contributions. But feel free to file issues and point
out any glaring errors you might have found in the source code as I would love
to learn and address the issues.

## Deviations

At the end of certain chapters the author provides "Challenges," some of these
challenges include adding in some feature to the language that either hasn't
been implemented by that point or will not be addressed directly by the book. So
here are the deviations I made and solutions I took to achieve them.

1. **Chapter 14**
   1. **Challenge 1:** I implement a run-length-esque encoding for line numbers as a way to store
      them more "efficiently." It's not really "more efficient" when there are ~3-5 or so operations
      on the same line (or worse if they're all on different lines) but assuming the spread of
      operations to lines skews in favor of a larger number of operations per line then this should
      work out well enough.
