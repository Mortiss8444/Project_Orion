#!/bin/bash 
#simple launcher for execution multiple scripts

initializer()
{
	./hello				#execute main script  
	while true; do
    	read -p "> " input  		#processing user's input until 'exit' command won't be executed
    	case $input in
        	exit ) exit;;
    		esac
	done
}
export -f initializer			#now this function is available for terminal

gnome-terminal -- bash -c "initializer; exec bash"	 #run everything above in new window
