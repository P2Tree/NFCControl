# Readme.md

## Brief

- this project is a `C PROJECT`;
- edite in `keil 5` software;
- compile with `keil 5 inner compiler`;
- download to `STM32F303` micro controler;
- download with `J-Link emulator` over a `JTAG` interface;

## Function

- this project is used to control a NFC module to read NFC cards;
- when designated NFC card closed to NFC module, the light in NFC module will flash once slowly.
- when undesignated NFC card closed to NFC module, the light in NFC module will flash twice quickly.
- if no card or different types card closed to NFC module, there is no action.
- micro controler is responsible for controling the NFC module when system running.
- NFC card supported is S50 NFC card.

## Structure

- in `user` dirc is main file and supported files, inclueding c files and h files.
- in `src` dirc is basic c files of STM32 used to compile.
- in `inc` dirc and `Headers` is basic h files.
- in `doc` dirc is some supporting files and help files.
- in `debug` dirc is debug files.
- others is project files.

## Note

I will not fix the bug any more, so if you like you can fork it and fix bugs. This project is V1.0 version. I only used it in my small undertake project.

And i tell the truth, im not satisfied with my NFC module. There is so many bugs in it and i can do nothing about it, because the NFC module is not open sourced.

## Link

You can link me with email: dicksonliuming@gmail.com

My GITHUB is: PWESiberiaBear
