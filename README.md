![# libStageARM](https://raw.githubusercontent.com/Thinkatron/libStageArm/master/libStageArm.png "libStageARm Logo")

# What is it?
  *__libStageARM__* is a C library written to interact with the SMU 3D Stage Arm with using a simple standard serial interface. The goal of this project is to provide an easily customizable, easily implemented interface, with simple-to-use functions available in multiple languages, and a clearly defined serial interface that can be implemented an any other language. This project also provides a simple REST API for web control of the 3D Stage.
# Compatibility
|Language        |Implementation          |Tested|Succesful|
|:--------------:|------------------------|:----:|---------|
|C               |Header and Shared Object|✓     |Success  |
|C++             |Header and Shared Object|✓     |Success  |
|JavaScript      |SWIG Wrapper            |✓     |Success  |
|Java            |SWIG Wrapper            |✓     |Success  |
|Allegro CL      |SWIG Wrapper            |✗     |Unknown  |
|C#              |SWIG Wrapper            |✗     |Unknown  |
|CFFI            |SWIG Wrapper            |✗     |Unknown  |
|CLISP           |SWIG Wrapper            |✗     |Unknown  |
|Chicken         |SWIG Wrapper            |✗     |Unknown  |
|D               |SWIG Wrapper            |✗     |Unknown  |
|Go              |SWIG Wrapper            |✗     |Unknown  |
|Guile           |SWIG Wrapper            |✗     |Unknown  |
|Lua             |SWIG Wrapper            |✗     |Unknown  |
|Modula-3        |SWIG Wrapper            |✗     |Unknown  |
|Mzscheme        |SWIG Wrapper            |✗     |Unknown  |
|OCAML           |SWIG Wrapper            |✗     |Unknown  |
|Octave          |SWIG Wrapper            |✗     |Unknown  |
|Perl            |SWIG Wrapper            |✗     |Unknown  |
|PHP             |SWIG Wrapper            |✗     |Unknown  |
|Python          |SWIG Wrapper            |✗     |Unknown  |
|R               |SWIG Wrapper            |✗     |Unknown  |
|Ruby            |SWIG Wrapper            |✗     |Unknown  |
|Scilab          |SWIG Wrapper            |✗     |Unknown  |
|Tcl             |SWIG Wrapper            |✗     |Unknown  |
|UFFI            |SWIG Wrapper            |✗     |Unknown  |
>If you test a language, please make a pull request.
>If you create a wrapper or implementation in an unlisted language,
>please, feel free to make a pull request with an update to the
>table and your implementation.
>
>Thank you!
# Serial Standard
 Any control command for the 3D Platform will be a single Byte (unsigned char / uChar / uInt_8) along, followed by a command-specific buffer array. All commands are little-endian. The Buffer Size includes the Initial Byte and the Arguments. Every action will respind with 0 for a successful action or a non-zero value for an unsuccessful action. Some actions will have specific responses for certian errors, but will usually just return 1 if they are unsuccessful.
 
 #### Commands
 
|Command          |Initial Byte |Buffer Size |Arguments |
|-----------------|:-----------:|:----------:|----------|
|Begin New Set    |0x00         |1           |N/A       |

#### Error Codes

|Error Code |Meaning                                                              |
|:---------:|---------------------------------------------------------------------|
|0x00       |Success                                                              |
|0x01       |Generic Failure                                                      |
|0x02       |Coordinate out of bounds, no action                                  |
|0x03       |Coordinate out of bounds, reached outer bound X                      |
|0x04       |Coordinate out of bounds, reached outer bound Y                      |
|0x05       |Coordinate out of bounds, reached outer bound Z                      |
|0x06       |Coordinate out of bounds, reached outer bound X & Y                  |
|0x07       |Coordinate out of bounds, reached outer bound Y & Z                  |
|0x08       |Coordinate out of bounds, reached outer bound Z & X                  |
|0x09       |Coordinate out of bounds, reached outer bound X & Y & Z              |
|0x0A       |Coordinate out of bounds, undefined action (Recallibration Suggested)|


# REST API
