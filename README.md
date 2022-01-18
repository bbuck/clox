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

### Testing

Testing is a bit more of a beast, and maybe this affects builds (I hope not, but I'm too lazy to
verify at this very moment). You will need to have the [criterion testing framework]()
installed at `/usr/local/lib/libcriterion.dylib` and `/usr/local/include/criterion/criterion.h`
in order to run tests. Once that is set up, then ideally you just run the tests:

```
$ bazel test //test:{chunk_test,value_test,...}
```

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
   1. **Challenge 2:** I implemented `kOpConstant16` that supports reading two `uint8_t` values from
      the code list and join them into a 16-bit value. The `kOpConstant*` variants are chosen
      intelligently by using `ChunkWriteConstant` now. If you write a 256th constant (256 > uint8_t
      max value) then the number is split into two 8-bit values and pushed into the code along with
      the new `kOpConstant16` opcode in a big-endian format.
   1. **Testing:** Not really a _challenge_ per se but there was note about testing the
      implementation and tests are good things. I wanted to experiment with testing in C so I went
      ahead and rolled my own test suite. Is it great? No. Is it what you should do in your project?
      No. But it works, so there is that.

### Saved for later

I'd really like to take on **Chapter 14, Challenge 3**'s "Hardcore Mode" (implementing my own
allocation tools) but for the time being I'm going to pass on it for the sake of moving on with the
chapters as I feel like this particular challenge is pretty large and my experience with C is fairly
limited. But saving it for later to allow me to come back and take a stab at it.
