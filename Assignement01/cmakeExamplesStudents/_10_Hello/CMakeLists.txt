cmake_minimum_required(VERSION 3.20)

# Set project name
# It can be so simple as setting the project name: project(HelloWorld)
# But additional infor can and should be used
project(HelloWorld VERSION 1.0
                  DESCRIPTION "The classical Hello World example"
                  LANGUAGES C)
                  
# Executable "hello" generated from "Hello.c"
add_executable(hello src/Hello.c) 
