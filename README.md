# Project_Orion
	    ____               _           __      ____       _           
	   / __ \_________    (_)__  _____/ /_    / __ \_____(_)___  ____ 
	  / /_/ / ___/ __ \  / / _ \/ ___/ __/   / / / / ___/ / __ \/ __ \
	 / ____/ /  / /_/ / / /  __/ /__/ /_    / /_/ / /  / / /_/ / / / /
	/_/   /_/   \____/_/ /\___/\___/\__/____\____/_/  /_/\____/_/ /_/ 
	                /___/             /_____/                        
Project_Orion is a cross-platform CLI, purpose of which is to analyze a satellite's behaviour on a world map. <hr />
## Installation guide  
**The tech stack:**  
  For Windows: Visual Studio 2019, C++ 14, OpenGL 3.3, CMake 3.16.3      
  For Linux: Nvim, C++ 14, OpenGL 3.3, CMake 3.16.3  
### <ins> Windows </ins>
<ins>1. Downloading the repository: </ins>  

Start by cloning the repository with ```git clone --recursive https://github.com/Mortiss8444/Project_Orion```  

<ins>2. Setting up the project: </ins>  

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
    
<ins>3. Debugging: </ins>  
  
1. Add to debug folder Fonts and Shaders folders and also don't forget to add freetype.dll
2. So after pressing a debug button, you should be able to see following:  
![Debug](https://user-images.githubusercontent.com/62875127/135939878-c1260f40-6ec7-484a-b17d-be84cfc0cc40.jpg)  
### <ins> Linux </ins>  
*Note: Since this program has only been tested on Ubuntu 20.04.2 and it is not known how it will behave on other Linux distributions, the following steps below assume that you have Ubuntu 20.04.2 or higher*  
1. Just clone the reposetory and execute ```./ProjectOrion``` from build folder
2. Or if you want to modify code 
	1) Clean build folder
	2) Modify code
	3) Execute ```cmake ..``` and ```cmake --build .``` from build folder  
	4) Copy&Paste Fonts and Shaders folders as well as map.jpg   
	5) Run  ```./ProjectOrion```  
And also keep in mind that you might need to install development packages for your Linux distribution, for Ubuntu these are ```xorg-dev``` packages which can be downloaded by ```sudo apt install xorg-dev```  
## Main features  
### Message system
While using the program, you might see the three types of outcome messages:  
```[Info]:``` - information about what operation the program is performing  
```[Error]:``` - invalid data has been passed to the program   
```[Usage]:``` - a hint how a command should be written     
### List of commands  
```endsession``` - close both handler thread and GL thread  
```help -c``` - display list of all commands  
```help -s``` - display list of all satellites  
```track <satellite_name>``` - display a satellite on a world map  
![ezgif com-gif-maker (3)](https://user-images.githubusercontent.com/62875127/136285321-c8840d04-4772-40c3-9e5d-caf50a28df65.gif)  
```stop <satellite_name>``` - remove a satellite from a world map  
![ezgif com-gif-maker (4)](https://user-images.githubusercontent.com/62875127/136285349-3df06424-4661-44b9-8fed-481d49108027.gif)  
## Q&A section  
- **Q: Does the program display accuratly a satellite?**  

  - A: Yes, the program uses spherical mercator projection which is commonly used in web applications including Google Maps and gives accurate pixel coordinates, but since our map has smaller South Pole than Google Maps, then negative latitude will look like it's been shifted by 20 degrees relatively to latitude in Google Maps, so it depends only from picture, actual algorithm works properly  
- **Q: How to create a new command?**  

```C++
//your custom command
    class CommandName_Handler : public Parent_Handler {
    private:
        //here is your locals
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
		if(my_condition)
		{
			//what it should do?
		}
		...
	}
    }
```
and in ```command_handler()``` add
```C++
	CommandName_Handler commandName_Handler = new CommandName_Handler;
	...->SetNext(previousCommand_Handler)->SetNext(commandName_Handler)
	//and don't forget to delete
	delete commandName_Handler;
```
- **Q: How many satellites can I track at one time?**

  - A: Currently, 10. But you can increase it until you won't be able to see something on map or even more... It depends only on size of buffer which holds all satellite relat
