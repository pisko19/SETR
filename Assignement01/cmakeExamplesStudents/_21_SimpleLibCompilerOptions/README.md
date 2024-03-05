
# Example of setting compiler options

## Decription
One project that has a user library. The main target is set to use "-Wall -Werror" compiler options.  
The compiler options are set on the library CMakeLists.txt.  
Other commands to consider are: target_compile_options, target_compile_definitions, target_compile_features and target_link_options. 
See e.g. https://jeremimucha.com/2021/02/cmake-fundamentals-part5/ 

## Running the example
* Remove the build folder, if it exists
* Create the makefile, make the project and test it
* In Linux, type the following:

```console
	$rm -rdf build
	$cmake -S . -B build -DWARN_GENERATE_ERR=ON
	$cd build/
	$make
	$./libdemo 	
```
* Or use cmake-gui and set the WARN_GENERATE_ERR variable interactively

