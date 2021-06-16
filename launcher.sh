#!/bin/bash 
#simple launcher for execution multiple scripts

executor()
{
	./initializer				#execute main script  
	while true; do
    	read -p "> " input  		#processing user's input until 'exit' command won't be executed
    	case $input in
        	exit ) exit;;
    		esac
	done
	complete "put" in
}
export -f executor			#now this function is available for terminal

gnome-terminal -- bash -c "executor; exec bash"	 #run everything above in new window
