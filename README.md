# Project_Orion
	    ____               _           __      ____       _           
	   / __ \_________    (_)__  _____/ /_    / __ \_____(_)___  ____ 
	  / /_/ / ___/ __ \  / / _ \/ ___/ __/   / / / / ___/ / __ \/ __ \
	 / ____/ /  / /_/ / / /  __/ /__/ /_    / /_/ / /  / / /_/ / / / /
	/_/   /_/   \____/_/ /\___/\___/\__/____\____/_/  /_/\____/_/ /_/ 
	                /___/             /_____/                        
Project_Orion is a cross-platform CLI purpose of which, currently, is to display all satellite-related data on a world map. <hr />
## Installation guide
For Windows: Visual Studio 2019 and C++ 14 are recommended  
For Linux: CMake 3.16.3
### <ins> Windows </ins>
<ins>1. Downloading the repository </ins>  

Start by cloning the repository with ```git clone --recursive https://github.com/Mortiss8444/Project_Orion```  

<ins>2. Setting up the project </ins>  

1. Once you have opened the project with Visual Studio, delete project Project_Orion and recreate it
2. Add all scripts to the project
3. Set Project_Orion as startup project
4. In properties (C/C++->General) include the following paths to headers
    1) Dependencies/
	  2) Dependencies/FreeType/include
	  3) Dependencies/GLFW/include
4. In Linker/Input include the following libraries -> glfw3.lib, freetype.lib
5. In Linker/General include path to the libraries
	  1) Dependencies/GLFW/lib-vc2019
	  2) Dependencies/FreeType  
    
<ins>3. Debugging </ins>  
  
1. Add to debug folder Fonts and Shaders folders and also don't forget to add freetype.dll
2. So after pressing a debug button, you should be able to see following:  
![Debug](https://user-images.githubusercontent.com/62875127/135939878-c1260f40-6ec7-484a-b17d-be84cfc0cc40.jpg)  
### <ins> Linux </ins>  
*Note: Since this program was tested only on Ubuntu 20.04.2 and this is unknown how it will behave on other Linux distributions, so following the next steps assumes that you have Ubuntu 20.04.2 or higher*  
1. Just clone the reposetory and execute ```./ProjectOrion``` from build folder
2. If you want to modify code 
	1) Clean build folder
	2) Modify code
	3) Execute ```cmake ..``` and ```cmake --build``` from build folder  
	4) Run  ```./ProjectOrion```  

And also keep in mind that you might need to install development packages for your Linux distribution, for Ubuntu these are ```xorg-dev``` packages which can be downloaded by ```sudo apt install xorg-dev```
