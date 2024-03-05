
# Example for building a C project and Doxygen documentation

## Decription
The project is documented with Doxygen, in the usual way.  
CMake allows to build the documentation, when instructed to do so.

## Running the example
* Remove the build folder, if it exists
* Create the makefile with the proper option set 
* Make the docs and check the output 
* In Linux, type the following:

```console
	$rm -rdf build
	$cmake -S . -B build -DGENERATE_DOC=ON 
	$cd build/
	$make LibDemoDoc	 
```
Files are placed in "build/docs"



